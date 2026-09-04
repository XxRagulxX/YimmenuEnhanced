#include "Core/DetourHook.hpp"
#include "Menu/GUI.hpp"
#include "Menu/UIManager.hpp"
#include "Core/Hooks.hpp"
#include "Core/Hooking.hpp"

namespace YimMenu::Hooks
{
	UINT RawInput::GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
	{
		auto result = Hooking::Get<RawInput::GetRawInputData>()->Original<decltype(&RawInput::GetRawInputData)>()(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);

		// Real Stand feel: the DirectXTK12/Grid menu never wants mouse
		// capture (it's keyboard-only - see GUI::ToggleMouse()'s own
		// comment), so this only swallows clicks while the classic
		// pipeline actually has real (Lua-added) content on screen
		// needing mouse interaction - same condition GUI::ToggleMouse()
		// uses to decide whether the cursor itself should even be shown.
		if (result > 0 && pData && uiCommand == RID_INPUT && GUI::IsOpen() && UIManager::HasAnyContent())
		{
			auto& raw = *(RAWINPUT*)pData;
			if (raw.header.dwType == RIM_TYPEMOUSE && raw.data.mouse.usButtonFlags)
			{
				// Zero out button flags to prevent game from seeing clicks while menu is open
				raw.data.mouse.usButtonFlags = 0;
			}
		}

		return result;
	}
}
