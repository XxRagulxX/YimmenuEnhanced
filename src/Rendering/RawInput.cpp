#include "Core/DetourHook.hpp"
#include "Menu/GUI.hpp"
#include "Core/Hooks.hpp"
#include "Core/Hooking.hpp"

#include <imgui.h>

namespace YimMenu::Hooks
{
	UINT RawInput::GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
	{
		auto result = Hooking::Get<RawInput::GetRawInputData>()->Original<decltype(&RawInput::GetRawInputData)>()(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);

		if (result > 0 && pData && uiCommand == RID_INPUT && ImGui::GetIO().WantCaptureMouse)
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
