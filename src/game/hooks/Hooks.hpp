#pragma once
#include <d3d11.h>

class CNetworkPlayerMgr;
class CNetGamePlayer;

namespace YimMenu::Hooks
{
	namespace SwapChain
	{
		constexpr auto VMTPresentIdx       = 8;
		constexpr auto VMTResizeBuffersIdx = 13;
		constexpr auto VMTSize             = 19;
		extern HRESULT Present(IDXGISwapChain* that, UINT syncInterval, UINT flags);
		extern HRESULT ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	}

	namespace Info
	{
		extern void AssignPhysicalIndex(CNetworkPlayerMgr* mgr, CNetGamePlayer* player, std::uint8_t index);
	}

	namespace Script
	{
		extern bool RunScriptThreads(int ops_to_execute);
	}

	namespace Window
	{
		extern LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	}
}