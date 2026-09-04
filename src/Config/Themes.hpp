#pragma once

namespace YimMenu
{
	// Only one theme renderer remains (Classic) - it now exists purely to
	// serve Lua's own menu API (see Menu/UIManager.hpp's class comment),
	// so the RenderModernTheme()/RenderModernVTheme()/RenderModularTheme()
	// alternatives that used to exist alongside it were removed rather
	// than kept as unreachable dead code. Two-pass, same contract every
	// other always-on overlay in this system follows - see
	// Menu/ClassicUI.hpp's own class comment for why.
	extern void RenderClassicTheme();
	extern void RenderClassicThemeText();
}
