#include "DetourHook.hpp"
#include "Renderer.hpp"
#include "Hooks.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		if (g_Running)
			Renderer::WndProc(hwnd, umsg, wparam, lparam);

		return Hooking::Get<Window::WndProc>()->Original<WNDPROC>()(hwnd, umsg, wparam, lparam);
	}
}