#pragma once
#include <cstddef>
#include <cstdint>

namespace YimMenu::Rendering
{
	class Grid;
	class GridItem;

	// Keyboard-navigation cursor state. This project's own addition -
	// see GridItem.hpp's class comment for why: Stand's own keyboard
	// navigation moves a cursor through its Command tree (a per-
	// CommandList m_cursor plus a root_cursor for its tab strip), a
	// whole system this project doesn't have. This is the flattened
	// equivalent that fits what this project does have instead - one
	// sidebar (MenuGrid's own GridItemSidebarList) and one active
	// content Grid (MenuNavigation::Current()) at a time:
	//
	// - Sidebar: GridItemSidebarList owns its own active index
	//   directly (GetActiveIndex()/MoveActive()) - MenuFocus only
	//   tracks whether the sidebar or the content Grid currently has
	//   focus, not which sidebar entry.
	// - Content: MenuFocus itself tracks an index into whatever the
	//   current content Grid's own getFocusableItems() returns,
	//   resetting to 0 whenever that Grid changes underneath it (a
	//   sidebar switch, or a GridItemFolder Push()/Backspace Pop()) -
	//   detected lazily, by comparing against the Grid pointer last
	//   seen, rather than needing every call site that can change
	//   MenuNavigation's current Grid to remember to reset this too.
	class MenuFocus
	{
	public:
		enum class Region : uint8_t
		{
			Sidebar,
			Content
		};

		static Region GetRegion();
		static void SetRegion(Region region);

		// The content item keyboard focus currently sits on, within
		// currentContent (always MenuNavigation::Current() in
		// practice) - nullptr if currentContent has no focusable items
		// at all. Also where the "did the content Grid change since
		// last time" reset happens (see the class comment above), so
		// this has to run before MoveContent() can trust s_ContentIndex.
		static GridItem* GetFocusedItem(Grid* currentContent);

		// Moves the content focus index by delta (+1/-1), clamped (not
		// wrapped) to currentContent's own focusable item count.
		static void MoveContent(Grid* currentContent, int delta);

	private:
		static Region s_Region;
		static Grid* s_LastContent;
		static size_t s_ContentIndex;
	};
}
