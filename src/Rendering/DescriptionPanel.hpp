#pragma once

namespace YimMenu::Rendering
{
	// Shows the currently keyboard-focused content item's own
	// GetDescription() (help text), if it has one - this project's
	// equivalent of real Stand's own CommandPhysical::populateCorner()
	// (confirmed against origin/stand-reference), simplified to just
	// the one line every focused command actually has here
	// (YimMenu::Command::GetDescription()/Stand::CommandPhysical::
	// help_text - see GridItem::GetDescription()'s own comment), not
	// the syntax/range/toggle-correlation lines real Stand's own corner
	// also shows - none of that machinery exists on either of this
	// project's own two command systems yet.
	//
	// A free-standing global (not a GridItem, not owned by any Grid),
	// same shape as MenuPopup/MenuCommandBox - drawn by GridRenderer
	// alongside those every frame the menu is open, reading focus fresh
	// via MenuFocus::GetFocusedItem(MenuNavigation::Current()) rather
	// than needing anything pushed to it, and drawing nothing at all
	// when nothing's focused or the focused item has no description.
	//
	// Positioned to the LEFT of the sidebar (see the .cpp's own layout
	// comment for why) - the only region of this system's own fixed
	// 1920x1080 H-space layout that's genuinely free regardless of
	// content width or scroll state, unlike real Stand's own default
	// "beside content" placement (ALIGN_TOP_RIGHT), which doesn't fit
	// this project's own numbers.
	class DescriptionPanel
	{
	public:
		static void Draw();
		static void DrawText();
	};
}
