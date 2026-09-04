#pragma once

namespace YimMenu::Rendering
{
	// Global "is some on-screen text field currently capturing keyboard
	// input" flag - the DirectXTK-era equivalent of ImGui's own
	// GetIO().WantTextInput. Every text-editing widget in this project
	// (Grid's own GridItemTextInput/GridItemSelectList/GridItemHexRow,
	// and the classic pipeline's own text field - see Menu/ClassicUI.hpp)
	// flips this on while actively editing and off again on commit/
	// cancel/blur, so GUI::IsUsingKeyboard() (hotkey suppression while
	// typing) and GridRenderer::WndProcImpl (skip Grid's own Up/Down
	// navigation while a *different* text field elsewhere has focus) have
	// one shared source of truth instead of each needing to know about
	// every widget type directly.
	class InputCapture
	{
	public:
		static bool IsTextInputActive()
		{
			return s_Active;
		}

		static void SetTextInputActive(bool active)
		{
			s_Active = active;
		}

	private:
		static inline bool s_Active = false;
	};
}
