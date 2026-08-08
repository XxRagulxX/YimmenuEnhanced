#include "DetourHook.hpp"
#include "Renderer.hpp"
#include "Hooks.hpp"

namespace YimMenu::Hooks
{
	HRESULT SwapChain::Present(IDXGISwapChain* that, UINT syncInterval, UINT flags)
	{
		if (g_Running && !Renderer::IsResizing())
		{
			Renderer::DX12OnPresent();
		}
		return BaseHook::Get<SwapChain::Present, DetourHook>()->Original<decltype(&SwapChain::Present)>()(that, syncInterval, flags);
	}

	HRESULT SwapChain::ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			Renderer::DX12PreResize();
			const auto result =
			    BaseHook::Get<SwapChain::ResizeBuffers, DetourHook>()->Original<decltype(&SwapChain::ResizeBuffers)>()(that, bufferCount, width, height, newFormat, swapChainFlags);
			Renderer::DX12PostResize();
			return result;
		}
		return BaseHook::Get<SwapChain::ResizeBuffers, DetourHook>()->Original<decltype(&SwapChain::ResizeBuffers)>()(that, bufferCount, width, height, newFormat, swapChainFlags);
	}
}