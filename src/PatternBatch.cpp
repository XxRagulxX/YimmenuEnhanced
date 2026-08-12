#include "PatternBatch.hpp"

#include <algorithm>
#include <thread>
#include <utility>
#include <vector>

#include "LogHelper.hpp"

namespace YimMenu
{
	PatternBatch::PatternBatch(
	    std::unordered_map<std::string, std::uintptr_t>* cache) :
	    m_Cache(cache)
	{
	}

	void PatternBatch::Add(
	    std::string name,
	    soup::Range range,
	    soup::Pattern pattern,
	    PatternCallback callback)
	{
		AddImpl(
		    std::move(name),
		    std::move(range),
		    std::move(pattern),
		    std::move(callback),
		    {});
	}

	void PatternBatch::AddOptional(
	    std::string name,
	    soup::Range range,
	    soup::Pattern pattern,
	    PatternCallback callback,
	    PatternFailCallback failCallback)
	{
		AddImpl(
		    std::move(name),
		    std::move(range),
		    std::move(pattern),
		    std::move(callback),
		    std::move(failCallback));
	}

	void PatternBatch::AddImpl(
	    std::string name,
	    soup::Range range,
	    soup::Pattern pattern,
	    PatternCallback callback,
	    PatternFailCallback failCallback)
	{
		std::lock_guard lock(m_Mutex);

		m_Entries.emplace(
		    std::move(name),
		    std::move(range),
		    std::move(pattern),
		    std::move(callback),
		    std::move(failCallback));
	}

	void PatternBatch::ClearState()
	{
		std::lock_guard lock(m_Mutex);

		m_ErrorMessage.clear();
		m_HasFailed = false;
		m_CacheUtilisation.store(0, std::memory_order_relaxed);
	}

	bool PatternBatch::ProcessEntry(Entry& entry)
	{
		soup::Pointer result;
		bool fromCache = false;

		// Try the cached offset first.
		//
		// The cache is never trusted blindly. The cached address must still
		// be inside the scan range and the pattern must still match there.
		if (m_Cache)
		{
			std::lock_guard lock(m_Mutex);

			const auto cached = m_Cache->find(entry.m_Name);

			if (cached != m_Cache->end())
			{
				result =
				    entry.m_Range.base.as<std::uintptr_t>()
				    + cached->second;

				if (result.isInRange(entry.m_Range)
				    && entry.m_Pattern.matches(result.as<std::uint8_t*>()))
				{
					fromCache = true;

					m_CacheUtilisation.fetch_add(
					    1,
					    std::memory_order_relaxed);
				}
				else
				{
					result = nullptr;
				}
			}
		}

		// Cache miss or stale cache.
		// Perform a full pattern scan.
		if (!result)
		{
			result = entry.m_Range.scan(entry.m_Pattern);
		}

		if (result)
		{
			LOG(INFO)
			    << "Found pattern ["
			    << entry.m_Name
			    << "] : ["
			    << HEX(result.as<std::uintptr_t>())
			    << "]";

			// Execute the pointer initialization callback.
			//
			// Do not hold m_Mutex while executing callbacks.
			if (entry.m_Callback)
			{
				entry.m_Callback(result);
			}

			// Update the cache only when the pattern was actually scanned.
			if (!fromCache && m_Cache)
			{
				const auto offset =
				    result.as<std::uintptr_t>()
				    - entry.m_Range.base.as<std::uintptr_t>();

				std::lock_guard lock(m_Mutex);

				(*m_Cache)[entry.m_Name] = offset;
			}

			return true;
		}

		LOG(WARNING)
		    << "Failed to find pattern ["
		    << entry.m_Name
		    << "]";

		// Optional patterns are allowed to fail.
		if (entry.m_FailCallback)
		{
			entry.m_FailCallback(*this);
			return true;
		}

		// Record the failure.
		{
			std::lock_guard lock(m_Mutex);

			m_HasFailed = true;

			if (m_ErrorMessage.empty())
			{
				m_ErrorMessage =
				    "Failed to find pattern(s): "
				    + entry.m_Name;
			}
			else
			{
				m_ErrorMessage += ", ";
				m_ErrorMessage += entry.m_Name;
			}
		}

		return false;
	}

	void PatternBatch::Worker()
	{
		while (true)
		{
			Entry entry{
			    "",
			    soup::Range{},
			    soup::Pattern{},
			    {},
			    {}};

			{
				std::lock_guard lock(m_Mutex);

				if (m_Entries.empty())
				{
					return;
				}

				entry = std::move(m_Entries.front());
				m_Entries.pop();
			}

			// Pattern scanning happens outside the mutex so workers
			// can scan in parallel.
			ProcessEntry(entry);
		}
	}

	bool PatternBatch::Run()
	{
		ClearState();

		std::size_t entryCount = 0;

		{
			std::lock_guard lock(m_Mutex);
			entryCount = m_Entries.size();
		}

		if (entryCount == 0)
		{
			return true;
		}

		auto threadCount =
		    static_cast<std::size_t>(std::thread::hardware_concurrency());

		if (threadCount == 0)
		{
			threadCount = 1;
		}

		threadCount = std::min(threadCount, entryCount);

		std::vector<std::thread> workers;
		workers.reserve(threadCount);

		for (std::size_t i = 0; i < threadCount; ++i)
		{
			workers.emplace_back([this] {
				Worker();
			});
		}

		for (auto& worker : workers)
		{
			if (worker.joinable())
			{
				worker.join();
			}
		}

		return !HasFailed();
	}

	bool PatternBatch::HasFailed() const noexcept
	{
		std::lock_guard lock(m_Mutex);
		return m_HasFailed;
	}
}