#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>

#include <soup/Pattern.hpp>
#include <soup/Range.hpp>

namespace YimMenu
{
	class PatternBatch
	{
	public:
		using PatternCallback = std::function<void(soup::Pointer)>;
		using PatternFailCallback = std::function<void(PatternBatch&)>;

		struct Entry
		{
			std::string m_Name;
			soup::Range m_Range;
			soup::Pattern m_Pattern;
			PatternCallback m_Callback;
			PatternFailCallback m_FailCallback;

			Entry(
			    std::string name,
			    soup::Range range,
			    soup::Pattern pattern,
			    PatternCallback callback,
			    PatternFailCallback failCallback = {}) :
			    m_Name(std::move(name)),
			    m_Range(std::move(range)),
			    m_Pattern(std::move(pattern)),
			    m_Callback(std::move(callback)),
			    m_FailCallback(std::move(failCallback))
			{
			}
		};

	public:
		PatternBatch() = default;

		explicit PatternBatch(
		    std::unordered_map<std::string, std::uintptr_t>* cache);

		PatternBatch(const PatternBatch&) = delete;
		PatternBatch& operator=(const PatternBatch&) = delete;

		void Add(
		    std::string name,
		    soup::Range range,
		    soup::Pattern pattern,
		    PatternCallback callback);

		void AddOptional(
		    std::string name,
		    soup::Range range,
		    soup::Pattern pattern,
		    PatternCallback callback,
		    PatternFailCallback failCallback = {});

		[[nodiscard]]
		bool Run();

		[[nodiscard]]
		bool HasFailed() const noexcept;

		[[nodiscard]]
		const std::string& GetErrorMessage() const noexcept
		{
			return m_ErrorMessage;
		}

		[[nodiscard]]
		std::uint16_t GetCacheUtilisation() const noexcept
		{
			return m_CacheUtilisation.load(std::memory_order_relaxed);
		}

	private:
		void AddImpl(
		    std::string name,
		    soup::Range range,
		    soup::Pattern pattern,
		    PatternCallback callback,
		    PatternFailCallback failCallback);

		bool ProcessEntry(Entry& entry);

		void Worker();

		void ClearState();

	private:
		std::unordered_map<std::string, std::uintptr_t>* m_Cache = nullptr;

		std::queue<Entry> m_Entries;

		mutable std::mutex m_Mutex;

		std::atomic<std::uint16_t> m_CacheUtilisation{0};

		std::string m_ErrorMessage;

		bool m_HasFailed = false;
	};
}