#pragma once
#include <DirectXMath.h>

#include <cstdint>

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

	// Layout, matching stand-reference's Renderer defaults exactly -
	// int16_t, same as Stand's own addressbar_height/tabs_width/
	// tabs_height/command_width/command_height fields (and GridItem's
	// own x/y/width/height, ported the same way - see GridItem.hpp).
	// addressbar_height is the header/breadcrumb bar; tabs_width/
	// tabs_height are the left-hand submenu list ("sidebar" everywhere
	// else in this system); command_width/command_height are the main
	// content list's own column width and each row's height.
	constexpr int16_t kHeaderHeight = 24;
	constexpr int16_t kSidebarWidth = 112;
	constexpr int16_t kSidebarEntryHeight = 32;
	constexpr int16_t kContentWidth = 450;
	constexpr int16_t kContentItemHeight = 32;

	// Stand's own command_text/tabs_text/addressbar_text scale (they're
	// all defined identically: float(15.0 * TEXT_HEIGHT_PX * 2.0), with
	// TEXT_HEIGHT_PX = 0.021875 - see stand-reference's src/Rendering/
	// dx_common.hpp and the TextSettings members in Renderer.hpp/Menu/
	// MenuGrid.hpp). Stand's embedded SpriteFont (the same "Be Vietnam
	// Pro" blob this project embeds - see font_bevietnamprolight.hpp) is
	// baked much larger than any row here is meant to show it at, so
	// every text draw needs this scale applied - drawing it at the
	// font's native size (scale 1.0, what this project did before) is
	// why text looked comically oversized for its row. GridRenderer
	// applies this once, uniformly, in DrawText()/MeasureText() rather
	// than per-widget, same as Stand applies command_text.scale/tabs_
	// text.scale/addressbar_text.scale identically across the same three
	// widget kinds.
	constexpr float kTextScale = 0.65625f;
	constexpr float kSmallTextScale = kTextScale * (12.f / 15.f);

	constexpr float kTextOffsetX = -2.f;
	constexpr float kTextOffsetY = 2.f;

	// Stand's own virtual HUD canvas dimensions (see GridRenderer::
	// PosH2C/SizeH2C's own doc comment for what "H-space" means) - shared
	// here since both GridRenderer.cpp (H-space <-> client-pixel
	// conversion) and MenuGrid.cpp (working out how much of a content
	// Grid's own list is actually visible, for scrolling - see
	// Grid::ScrollBy()/ScrollToShow()) need the same numbers.
	constexpr float kHudWidth = 1920.f;
	constexpr float kHudHeight = 1080.f;

	// Bottom margin (H-space) a content Grid's own visible scroll window
	// stops short of the HUD canvas's bottom edge by - same idea as
	// kHeaderX/kHeaderY's own 20px margins elsewhere in this system, just
	// for the opposite edge.
	constexpr int16_t kContentBottomMargin = 20;

	constexpr int16_t kScrollbarWidth = 4;
	constexpr int16_t kScrollbarGap = 4;
}
