#pragma once
#include <cstdint>

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
	// Positioned directly below the sidebar - real Stand's own "Below
	// Tabs" placement (confirmed against origin/stand-reference's own
	// MenuGrid.cpp: ALIGN_BOTTOM_RIGHT forces info_text_force_alignment_to
	// to tabs_left and switches the actual text alignment to
	// ALIGN_BOTTOM_LEFT, i.e. anchored under the tab strip's own bottom
	// edge, using command_width - the wider, full-menu width - for the
	// box itself) - not real Stand's own DEFAULT (ALIGN_TOP_RIGHT, beside
	// content), which doesn't fit this project's own fixed 1920x1080
	// H-space layout: content already runs from the sidebar's own right
	// edge out to x=1888 of 1920 (only 32px short of the edge), leaving
	// nowhere to float a panel beside it.
	//
	// x/width span the WHOLE menu (sidebar + spacer + content, matching
	// MenuGrid::GetHeaderBarRect()'s own x/width - the header bar spans
	// exactly this already) - an earlier pass here narrowed the box to
	// just the sidebar's own ~112-wide column, which fixed one problem
	// (running over content's own text) by creating an uglier one: any
	// description longer than a couple of characters wrapped one word
	// per line. bottomY is the lower of the sidebar's own bottom edge and
	// the CURRENTLY SHOWING content list's own (viewport-clipped) bottom
	// edge - MenuGrid::GetSidebarRect()'s height alone isn't enough here,
	// since the sidebar's fixed 9 entries are shorter than most
	// categories' own content list, and a category with many rows (e.g.
	// Vehicle) would otherwise still run this panel straight over still-
	// visible rows. See MenuGrid::GetContentBottomY()'s own comment.
	class DescriptionPanel
	{
	public:
		static void Draw(int16_t x, int16_t bottomY, int16_t width);
		static void DrawText(int16_t x, int16_t bottomY, int16_t width);
	};
}
