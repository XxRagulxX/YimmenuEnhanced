#pragma once

#include <string_view>

namespace YimMenu
{
	class BaseHook
	{
	private:
		const std::string_view m_Name;

	protected:
		bool m_Enabled;

	public:
		explicit BaseHook(std::string_view name);
		virtual ~BaseHook() = default;

		BaseHook(const BaseHook&) = delete;
		BaseHook(BaseHook&&) noexcept = delete;
		BaseHook& operator=(const BaseHook&) = delete;
		BaseHook& operator=(BaseHook&&) noexcept = delete;

		[[nodiscard]]
		const std::string_view Name() const noexcept
		{
			return m_Name;
		}

		[[nodiscard]]
		bool IsEnabled() const noexcept
		{
			return m_Enabled;
		}

		virtual bool Enable() = 0;
		virtual bool Disable() = 0;

	public:
		// --------------------------------------------------
		// Hook function -> hook instance lookup
		//
		// BaseHook does NOT own hooks.
		// Hooking owns the actual DetourHook objects.
		// --------------------------------------------------

		template<auto HookFunc>
		struct HookHelper
		{
			inline static BaseHook* m_Hook = nullptr;
		};

		template<auto HookFunc>
		static void Add(BaseHook* hook)
		{
			HookHelper<HookFunc>::m_Hook = hook;
		}

		template<auto HookFunc>
		static void Remove(BaseHook* hook)
		{
			if (HookHelper<HookFunc>::m_Hook == hook)
			{
				HookHelper<HookFunc>::m_Hook = nullptr;
			}
		}

		template<auto HookFunc, typename T>
		[[nodiscard]]
		static T* Get()
		{
			return reinterpret_cast<T*>(HookHelper<HookFunc>::m_Hook);
		}
	};
}