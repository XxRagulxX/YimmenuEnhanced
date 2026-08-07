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
	template<typename T = int*>
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

		DetourHook(const DetourHook&) = delete;
		DetourHook& operator=(const DetourHook&) = delete;

		DetourHook(DetourHook&&) = delete;
		DetourHook& operator=(DetourHook&&) = delete;

		DetourHook(const std::string_view name, void* target, T detour);
		virtual ~DetourHook();

		bool Enable();
		bool Disable();

		bool EnableNow();
		bool DisableNow();

		template<typename U = T>
		[[nodiscard]]
		U Original() const noexcept;

		//======================================================
		// Stand compatibility wrappers
		//======================================================

		void Init(void* detour, void* target, uint8_t flags = DH_NONE) noexcept
		{
			m_DetourFunc = detour;
			m_TargetFunc = target;
			m_Flags = flags;
		}

		void SetTarget(void* target) noexcept
		{
			m_TargetFunc = target;
		}

		template<typename U = T>
		[[nodiscard]]
		U getOriginal() const noexcept
		{
			return Original<U>();
		}

		//======================================================
		// Stand compatibility wrappers
		//======================================================

		[[nodiscard]]
		bool IsValid() const noexcept
		{
			return m_TargetFunc != nullptr && m_DetourFunc != nullptr;
		}

		[[nodiscard]]
		bool IsHooked() const noexcept
		{
			return m_OriginalFunc != nullptr;
		}

		[[nodiscard]]
		bool IsMandatory() const noexcept
		{
			return (m_Flags & DH_MANDATORY) != 0;
		}

		[[nodiscard]]
		bool CanFollowJumps() const noexcept
		{
			return (m_Flags & DH_NOFOLLOWJUMPS) == 0;
		}

		[[nodiscard]]
		bool IsLongJump() const noexcept
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

	template<typename T>
	inline DetourHook<T>::DetourHook(const std::string_view name, void* target, T detour) :
	    BaseHook(name),
	    m_TargetFunc(target),
	    m_DetourFunc(reinterpret_cast<void*>(detour)),
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
	template<typename T>
	inline DetourHook<T>::~DetourHook()
	{
		RemoveHook();
	}

	template<typename T>
	inline bool DetourHook<T>::Enable()
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

	template<typename T>
	inline bool DetourHook<T>::Disable()
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

	template<typename T>
	inline bool DetourHook<T>::EnableNow()
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

	template<typename T>
	inline bool DetourHook<T>::DisableNow()
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

	template<typename T>
	template<typename U>
	inline U DetourHook<T>::Original() const noexcept
	{
		return reinterpret_cast<U>(m_OriginalFunc);
	}

	template<typename T>
	inline void DetourHook<T>::OptimizeHook()
	{
		auto ptr = PointerCalculator(m_TargetFunc);
		while (ptr.As<std::uint8_t&>() == 0xE9)
		{
			ptr = ptr.Add(1).Rip();
		}
		m_TargetFunc = ptr.As<void*>();
	}

	template<typename T>
	inline bool DetourHook<T>::CreateHook()
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

	template<typename T>
	inline void DetourHook<T>::EnableHook()
	{
		EnableNow();
	}

	template<typename T>
	inline void DetourHook<T>::EnableHookQueued()
	{
		Enable();
	}

	template<typename T>
	inline void DetourHook<T>::DisableHook()
	{
		DisableNow();
	}

	template<typename T>
	inline void DetourHook<T>::DisableHookQueued()
	{
		Disable();
	}

	template<typename T>
	inline void DetourHook<T>::RemoveHook()
	{
		if (m_OriginalFunc)
		{
			MH_RemoveHook(m_TargetFunc);
			m_OriginalFunc = nullptr;
		}
	}
}