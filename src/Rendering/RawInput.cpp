#include "Core/DetourHook.hpp"
#include "Core/Hooks.hpp"
#include "Core/Hooking.hpp"

namespace YimMenu::Hooks
{
	// No longer swallows anything - the Grid menu (this project's only
	// native menu now, see Menu/UIManager.hpp's own class comment) is
	// keyboard-only by design and never wanted mouse capture; the
	// classic pipeline that used to need it doesn't draw anything for
	// there to be mouse capture over any more either. Kept installed as
	// a plain pass-through rather than unregistering the hook outright.
	UINT RawInput::GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
	{
		return Hooking::Get<RawInput::GetRawInputData>()->Original<decltype(&RawInput::GetRawInputData)>()(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
	}
}
