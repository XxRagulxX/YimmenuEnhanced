#include "Core/DetourHook.hpp"
#include "Rendering/Renderer.hpp"
#include "Core/Hooks.hpp"
#include "Core/Hooking.hpp"

namespace YimMenu::Hooks
{
	LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		if (g_Running)
			Renderer::WndProc(hwnd, umsg, wparam, lparam);

		return Hooking::Get<Window::WndProc>()->Original<WNDPROC>()(hwnd, umsg, wparam, lparam);
	}
}