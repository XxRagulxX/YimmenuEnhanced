#pragma once
#include "GridItem.hpp"

#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	// A vertical list of labels with one highlighted as active - the
	// sidebar equivalent of GridItemTabsHorizontal (submenu names: Self,
	// Vehicle, Teleport, ... instead of a horizontal tab row). Clicking an
	// entry switches which one is active; GetActiveIndex() lets the owning
	// Grid (MenuGrid) read the current selection to decide what content to
	// draw.
	//
	// Typed GRIDITEM_TABS, matching Stand's own GridItemTabsVertical -
	// this plays the exact same "submenu list" role Stand's own tabs_pos
	// = LEFT vertical tab strip does.
	class GridItemSidebarList : public GridItem
	{
	public:
		GridItemSidebarList(int16_t width, float entryHeight, std::vector<std::string> entries, size_t activeIndex) :
		    GridItem(GRIDITEM_TABS, width, static_cast<int16_t>(entryHeight * static_cast<float>(entries.size()))),
		    m_EntryHeight(entryHeight),
		    m_Entries(std::move(entries)),
		    m_ActiveIndex(activeIndex)
		{
		}

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

		size_t GetActiveIndex() const
		{
			return m_ActiveIndex;
		}

		// Keyboard-navigation equivalent of onClick() - moves the active
		// entry by delta (+1/-1), clamped (not wrapped) to the entry
		// list's bounds. MenuGrid::HandleKey() calls this for Up/Down
		// while MenuFocus::Region::Sidebar has focus - see MenuFocus.hpp.
		void MoveActive(int delta);

	private:
		float m_EntryHeight;
		std::vector<std::string> m_Entries;
		size_t m_ActiveIndex;
	};
}
