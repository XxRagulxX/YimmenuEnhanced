#include "Core/DetourHook.hpp"
#include "Menu/GUI.hpp"
#include "Core/Hooks.hpp"
#include "Core/Hooking.hpp"

namespace YimMenu::Hooks
{
	UINT RawInput::GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
	{
		auto result = Hooking::Get<RawInput::GetRawInputData>()->Original<decltype(&RawInput::GetRawInputData)>()(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);

		// The Grid menu (this project's only native menu now) supports
		// real mouse interaction, same as Stand's own does - GetRawInputData
		// is the actual choke point for what the game itself sees (window
		// messages pass through to the game's own WndProc unconditionally
		// regardless of what GridRenderer::WndProcImpl does with them -
		// see Window.cpp - so raw input is the only place this can act).
		// Movement deltas are left alone (the game's own camera/aim stays
		// live while the menu is open, same "doesn't take over input"
		// feel as everything else in this system - see GUI::RunScriptImpl's
		// own comment) - only the click flags are zeroed, so clicking a
		// menu row doesn't also fire whatever's equipped.
		if (result > 0 && pData && uiCommand == RID_INPUT && GUI::IsOpen())
		{
			auto& raw = *(RAWINPUT*)pData;
			if (raw.header.dwType == RIM_TYPEMOUSE && raw.data.mouse.usButtonFlags)
			{
				raw.data.mouse.usButtonFlags = 0;
			}
		}

		return result;
	}
}
