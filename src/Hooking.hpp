#pragma once

#include <memory>
#include <string_view>
#include <vector>
#include <algorithm>
#include "BaseHook.hpp"
#include "DetourHook.hpp"
#include "MinHook.hpp"

namespace YimMenu
{
	class Hooking
	{
	private:
		Hooking();

		MinHook m_MinHook;

		// Central ownership of all hooks.
		std::vector<std::unique_ptr<DetourHook>> m_Hooks;

		// Creates and owns a hook.
		DetourHook* AddHook(
		    std::string_view name,
		    void* target,
		    void* detour);

	public:
		virtual ~Hooking();

		Hooking(const Hooking&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(const Hooking&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		static bool Init();
		static void Destroy();

	private:
		bool InitImpl();
		void DestroyImpl();

		//--------------------------------------------------
		// Stand-compatible lifecycle API
		//--------------------------------------------------

		std::vector<DetourHook*> GetMinimalHooks();
		std::vector<DetourHook*> GetPassiveHooks();
		std::vector<DetourHook*> GetMainHooks();
		std::vector<DetourHook*> GetAllHooks();

		void BatchCreate(const std::vector<DetourHook*>& hooks);
		void BatchEnable(const std::vector<DetourHook*>& hooks);
		void BatchDisable(const std::vector<DetourHook*>& hooks);
		void BatchRemove(const std::vector<DetourHook*>& hooks);

	private:
		static Hooking& GetInstance()
		{
			static Hooking instance;
			return instance;
		}
	};
}