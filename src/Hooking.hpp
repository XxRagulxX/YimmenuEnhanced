#pragma once

#include <memory>
#include <utility>
#include <vector>

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

		// Future Stand ownership
		std::vector<std::unique_ptr<DetourHook<>>> m_Hooks;

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

		template<typename T, typename... Args>
		T* AddHook(Args&&... args);

		//--------------------------------------------------
		// Stand-compatible lifecycle API
		//--------------------------------------------------

		void BatchCreate(const std::vector<DetourHook<>*>& hooks);
		void BatchEnable(const std::vector<DetourHook<>*>& hooks);
		void BatchDisable(const std::vector<DetourHook<>*>& hooks);
		void BatchRemove(const std::vector<DetourHook<>*>& hooks);

		std::vector<DetourHook<>*> GetMinimalHooks();
		std::vector<DetourHook<>*> GetPassiveHooks();
		std::vector<DetourHook<>*> GetMainHooks();
		std::vector<DetourHook<>*> GetAllHooks();

	private:
		static Hooking& GetInstance()
		{
			static Hooking instance;
			return instance;
		}
	};

	template<typename T, typename... Args>
	T* YimMenu::Hooking::AddHook(Args&&... args)
	{
		auto hook = std::make_unique<T>(std::forward<Args>(args)...);

		T* ptr = hook.get();

		m_Hooks.emplace_back(std::move(hook));

		return ptr;
	}
}