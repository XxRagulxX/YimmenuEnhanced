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
	class GridItemSidebarList : public GridItem
	{
	public:
		GridItemSidebarList(float entryHeight, std::vector<std::string> entries, size_t activeIndex) :
		    GridItem(entryHeight * static_cast<float>(entries.size())),
		    m_EntryHeight(entryHeight),
		    m_Entries(std::move(entries)),
		    m_ActiveIndex(activeIndex)
		{
		}

		void Draw() override;
		void DrawText() override;
		void OnClick(float cursorX, float cursorY) override;

		size_t GetActiveIndex() const
		{
			return m_ActiveIndex;
		}

	private:
		float m_EntryHeight;
		std::vector<std::string> m_Entries;
		size_t m_ActiveIndex;
	};
}
