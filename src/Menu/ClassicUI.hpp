#pragma once
#include <DirectXMath.h>

#include <cstdint>
#include <string>

namespace YimMenu::ClassicUI
{
	// Minimal immediate-mode widget kit for the classic Category/Submenu/
	// Items.hpp tree - see Menu/UIManager.hpp's own class comment for why
	// this tree still exists at all (it's Lua's own menu-building API and
	// data model). Ported from real ImGui calls onto GridRenderer's
	// screen-space draw primitives (DrawRectFilledScreen/DrawTextScreen/
	// DrawLineScreen - real client pixels, not H-space) specifically so a
	// raw mouse position (GetCursorPos() + ScreenToClient()) hit-tests
	// against these rows with no coordinate conversion needed - unlike
	// the Grid menu's own H-space family, which deliberately has no such
	// conversion at all (see GridRenderer.cpp's own PosH2C comment) since
	// that menu is keyboard-only. This tree is mouse-driven instead,
	// same as it always was under ImGui - see Menu/GUI.cpp's own
	// ToggleMouse() for where the cursor actually gets turned back on for
	// it.
	//
	// Deliberately not a general-purpose UI framework: no window stack,
	// no ID stack, no clipping, no keyboard navigation - a single fixed
	// on-screen panel with one top-to-bottom flowing layout cursor,
	// covering exactly what this tree's own Draw() methods need
	// (Text/Button/Toggle/steppers/a cycling list/a plain click-to-edit
	// text field) and nothing else. Full interactive polish the original
	// ImGui version had (drag sliders, a real colour-picker popup,
	// hotkey-capture popups, tooltips, a real tab bar/accordion) is
	// explicitly out of scope for this pass - this tree is unreachable
	// dead weight until a Lua script actually populates it (nothing
	// native builds into it any more), and a proper Lua-facing UI is
	// being deferred to its own future pass rather than built twice.
	//
	// Two-pass, same contract every other always-on overlay in this
	// system follows (see Notifications.hpp's own class comment): every
	// widget call below draws its own rect part immediately (valid any
	// time GridRenderer's rect PrimitiveBatch is open) but only queues
	// its text part rather than drawing it - GridRenderer::DrawImpl's
	// two passes are separate D3D12 pipeline states/batches that can't
	// be interleaved, so all of this tree's text has to wait for the
	// second pass. Classic.cpp's own RenderClassicTheme() (the tree walk
	// - rects + queuing) must run in the first pass; DrawQueuedText()
	// below (flushing the queue) in the second, same
	// Draw()-before-DrawText() ordering contract as everywhere else.
	//
	// Plain namespace-scope functions rather than a static-only class
	// (there's no instance, no polymorphism, just file-local state in
	// ClassicUI.cpp's own anonymous namespace) - deliberately, since a
	// class named the same as its own enclosing namespace would make
	// every call site outside this namespace need to write
	// ClassicUI::ClassicUI::Whatever() to name it.

	// Called once per frame, before any widget calls below - resets
	// the layout cursor to (x, y) and captures this frame's mouse
	// state. width is the panel's own content width, used by
	// full-width widgets (Separator, row backgrounds).
	void BeginFrame(float x, float y, float width);

	void Text(const std::string& text);
	void TextDisabled(const std::string& text);

	// label, left-aligned, drawn in a full-width row - returns true
	// the one frame it's clicked (left button released while the
	// cursor is over this row).
	bool Button(const std::string& label);

	// label + an on/off swatch on the same row - returns the new
	// value (already flipped) the frame it's clicked, same "returns
	// the new value" shape GridItemToggle's own onClick uses.
	bool Toggle(const std::string& label, bool value);

	// label: "- value +" stepper row, step applied on each +/-
	// click - returns the (possibly unchanged) value.
	int IntStepper(const std::string& label, int value, int step = 1);
	float FloatStepper(const std::string& label, float value, float step = 0.1f);

	// label: "< current >" row, cycling through options[0..count) -
	// returns the (possibly unchanged) index.
	int Cycle(const std::string& label, const char* const* options, int count, int current);

	// label + a plain colour swatch, non-interactive (no picker
	// popup - see the class comment above) - just shows the
	// command's current value.
	void ColorSwatch(const std::string& label, const DirectX::XMFLOAT4& colour);

	// Click-to-edit text field, same interaction shape as Grid's own
	// GridItemTextInput (click to start, Enter commits, Escape
	// discards) - id must be unique among fields drawn this frame
	// (tracks which field is being edited; never shown). Returns the
	// committed value (unchanged until Enter).
	std::string TextField(const std::string& id, const std::string& label, std::string value);

	void Separator();
	void Spacing();

	float GetCursorY();
	void SetCursorY(float y);

	// Flushes every text draw queued by this frame's widget calls -
	// see the class comment above. Call once, from GridRenderer's own
	// text pass, after RenderClassicTheme() has run in the rect pass.
	void DrawQueuedText();

	// WndProc hook - forwards WM_CHAR/WM_KEYDOWN to whichever
	// TextField is currently being edited. Call from
	// GridRenderer::WndProcImpl.
	void OnChar(wchar_t c);
	void OnKeyDown(unsigned int vkCode);
}
