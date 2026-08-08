#pragma once
#include "BaseHook.hpp"
#include "PointerCalculator.hpp"

#include <MinHook.h>
#include <string_view>
#include <AsyncLogger/Logger.hpp>

namespace YimMenu
{
	enum DetourHookFlags : uint8_t
	{
		DH_NONE = 0,
		DH_MANDATORY = 1 << 0,
		DH_NOFOLLOWJUMPS = 1 << 1,
		DH_LONGJUMP = 1 << 2,
#ifdef YIMMENU_DEBUG
		DH_FORCEFAIL = 1 << 7,
#endif
	};
	class DetourHook : public BaseHook
	{
	private:
		void* m_TargetFunc = nullptr;
		void* m_DetourFunc = nullptr;
		void* m_OriginalFunc = nullptr;

		// Stand architecture additions
		void* m_EffectiveTarget = nullptr;

		uint8_t m_Flags = DH_NONE;

	public:
		virtual ~DetourHook();

		DetourHook(const DetourHook&) = delete;
		DetourHook& operator=(const DetourHook&) = delete;

		DetourHook(DetourHook&&) = delete;
		DetourHook& operator=(DetourHook&&) = delete;

		DetourHook(std::string_view name, void* target, void* detour);

		bool Enable();
		bool Disable();

		bool EnableNow();
		bool DisableNow();

		//======================================================
		// Stand compatibility wrappers
		//======================================================

		void init(void* detour, void* target, uint8_t flags = DH_NONE) noexcept
		{
			m_DetourFunc = detour;
			m_TargetFunc = target;
			m_Flags = flags;
		}

		void setTarget(void* target) noexcept
		{
			m_TargetFunc = target;
		}

		template<typename U>
		[[nodiscard]]
		U Original() const noexcept
		{
			return reinterpret_cast<U>(m_OriginalFunc);
		}

		template<typename U>
		[[nodiscard]]
		U getOriginal() const noexcept
		{
			return Original<U>();
		}

		//======================================================
		// Stand compatibility wrappers
		//======================================================

		[[nodiscard]]
		bool isValid() const noexcept
		{
			return m_TargetFunc != nullptr && m_DetourFunc != nullptr;
		}

		[[nodiscard]]
		bool isHooked() const noexcept
		{
			return m_OriginalFunc != nullptr;
		}

		[[nodiscard]]
		bool isMandatory() const noexcept
		{
			return (m_Flags & DH_MANDATORY) != 0;
		}

		[[nodiscard]]
		bool canFollowJumps() const noexcept
		{
			return (m_Flags & DH_NOFOLLOWJUMPS) == 0;
		}

		[[nodiscard]]
		bool isLongjump() const noexcept
		{
			return (m_Flags & DH_LONGJUMP) != 0;
		}

		//Future Implementation

		bool CreateHook();

		void EnableHook();
		void EnableHookQueued();

		void DisableHook();
		void DisableHookQueued();

		void RemoveHook();

	private:
		void OptimizeHook();
	};

	inline DetourHook::DetourHook(std::string_view name, void* target, void* detour):
		BaseHook(name),
	    m_TargetFunc(target),
	    m_DetourFunc(detour),
	    m_OriginalFunc(nullptr)
	{
		OptimizeHook();

		m_EffectiveTarget = m_TargetFunc;

		if (const auto result = MH_CreateHook(
		        m_TargetFunc,
		        m_DetourFunc,
		        &m_OriginalFunc);
		    result != MH_OK)
		{
			LOGF(FATAL,
			    "Failed to create hook {}",
			    name);

			throw std::runtime_error("Failed to create hook!");
		}

		LOGF(INFO, "Created hook {}", name);

	}

	inline DetourHook::~DetourHook()
	{
		RemoveHook();
	}

	inline bool DetourHook::Enable()
	{
		if (m_Enabled)
			return false;

		if (const auto result = MH_QueueEnableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to queue hook to be enabled.");

			return false;
		}

		m_Enabled = true;
		return true;
	}

	inline bool DetourHook::Disable()
	{
		if (!m_Enabled)
			return false;

		if (const auto result = MH_QueueDisableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to queue hook to be disable.");

			return false;
		}

		m_Enabled = false;
		return true;
	}

	inline bool DetourHook::EnableNow()
	{
		if (m_Enabled)
			return false;

		if (const auto result = MH_EnableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to enable hook right now.");

			return false;
		}

		m_Enabled = true;
		return true;
	}

	inline bool DetourHook::DisableNow()
	{
		if (!m_Enabled)
			return false;

		if (const auto result = MH_DisableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to disable hook right now.");

			return false;
		}

		m_Enabled = false;
		return true;
	}

	inline void DetourHook::OptimizeHook()
	{
		auto ptr = PointerCalculator(m_TargetFunc);
		while (ptr.As<std::uint8_t&>() == 0xE9)
		{
			ptr = ptr.Add(1).Rip();
		}
		m_TargetFunc = ptr.As<void*>();
	}

	inline bool DetourHook::CreateHook()
	{
		if (m_OriginalFunc)
			return true;

		const auto result = MH_CreateHook(
		    m_TargetFunc,
		    m_DetourFunc,
		    &m_OriginalFunc);

		if (result != MH_OK)
		{
			LOGF(FATAL,
			    "Failed to create hook {} (MH Error {})",
			    Name(),
			    static_cast<int>(result));

			return false;
		}

		LOGF(INFO, "Created hook {}", Name());

		return true;
	}

	inline void DetourHook::EnableHook()
	{
		EnableNow();
	}

	inline void DetourHook::EnableHookQueued()
	{
		Enable();
	}

	inline void DetourHook::DisableHook()
	{
		DisableNow();
	}

	inline void DetourHook::DisableHookQueued()
	{
		Disable();
	}

	inline void DetourHook::RemoveHook()
	{
		if (m_OriginalFunc)
		{
			MH_RemoveHook(m_TargetFunc);
			m_OriginalFunc = nullptr;
		}
	}
}