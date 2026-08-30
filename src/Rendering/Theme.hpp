#pragma once
#include <DirectXMath.h>

namespace YimMenu::Rendering::Theme
{
	// Stand's own default (unthemed) look - see stand-reference's src/
	// Rendering/Renderer.hpp, the Renderer class's own default member
	// values (focusRectColour/bgRectColour/bgTextColour and friends,
	// tabs_width/tabs_height/command_width/command_height/
	// addressbar_height). Earlier comments in this system called
	// magenta a "placeholder standing in for Stand's real (theme-loaded)
	// accent" - that was wrong. Stand loads a theme.json at runtime, but
	// these ARE the values it falls back to without one, and they're
	// exactly the neon-pink-on-black look real, unthemed Stand actually
	// has (compare any stock screenshot) - not a stand-in for something
	// else.

	// The one accent colour: whatever's currently active, on, selected,
	// or otherwise the thing that matters right now - a sidebar/tab's
	// active entry, a toggle's ON state, a button's fill. Stand's own
	// focusRectColour.
	constexpr DirectX::XMFLOAT4 kAccent{1.f, 0.f, 1.f, 1.f};

	// The translucent panel background every non-active row uses -
	// toggle/folder rows, inactive sidebar/tab entries, a stepper/list's
	// value box. Stand's own bgRectColour.
	constexpr DirectX::XMFLOAT4 kPanelBackground{0.f, 0.f, 0.f, 0.3019f};

	// White text/foreground, used everywhere. Stand's own
	// bgTextColour/focusTextColour (identical in both states there).
	constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};

	// NOT part of Stand's own palette - its Renderer only exposes one
	// accent (focusRectColour) and one panel colour (bgRectColour), with
	// no dedicated "off"/"unknown" look of its own. These are this
	// project's own additions for states that palette has nothing to
	// say about: a toggle's OFF state, a command hash that didn't
	// resolve to anything registered, this system's own "not yet
	// migrated" placeholder text.
	constexpr DirectX::XMFLOAT4 kToggleOff{0.35f, 0.35f, 0.35f, 1.f};
	constexpr DirectX::XMFLOAT4 kError{0.6f, 0.2f, 0.2f, 1.f};
	constexpr DirectX::XMFLOAT4 kPlaceholderText{0.7f, 0.7f, 0.7f, 1.f};

	// Layout, matching stand-reference's Renderer defaults exactly:
	// addressbar_height (the header/breadcrumb bar), tabs_width/
	// tabs_height (the left-hand submenu list - "sidebar" everywhere
	// else in this system), command_width/command_height (the main
	// content list's own column width and each row's height).
	constexpr float kHeaderHeight = 24.f;
	constexpr float kSidebarWidth = 112.f;
	constexpr float kSidebarEntryHeight = 32.f;
	constexpr float kContentWidth = 450.f;
	constexpr float kContentItemHeight = 32.f;
}
