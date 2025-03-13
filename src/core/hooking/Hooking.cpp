#include "Hooking.hpp"

#include "BaseHook.hpp"
#include "DetourHook.hpp"
#include "VMTHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	Hooking::Hooking()
	{
		BaseHook::Add<Window::WndProc>(new DetourHook("WndProc", Pointers.WndProc, Window::WndProc));

		auto swapchain_vft = *reinterpret_cast<void***>(*Pointers.SwapChain);
		BaseHook::Add<SwapChain::Present>(new DetourHook("Present", swapchain_vft[SwapChain::VMTPresentIdx], SwapChain::Present));
		BaseHook::Add<SwapChain::ResizeBuffers>(new DetourHook("ResizeBuffers", swapchain_vft[SwapChain::VMTResizeBuffersIdx], SwapChain::ResizeBuffers));
	}

	Hooking::~Hooking()
	{
		DestroyImpl();
	}

	bool Hooking::Init()
	{
		return GetInstance().InitImpl();
	}

	void Hooking::Destroy()
	{
		GetInstance().DestroyImpl();
	}

	bool Hooking::InitImpl()
	{
		BaseHook::EnableAll();
		m_MinHook.ApplyQueued();

		return true;
	}

	void Hooking::DestroyImpl()
	{
		BaseHook::DisableAll();
		m_MinHook.ApplyQueued();

		for (auto it : BaseHook::Hooks())
		{
			delete it;
		}
		BaseHook::Hooks().clear();
	}
}