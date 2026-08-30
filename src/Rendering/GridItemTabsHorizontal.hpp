#pragma once
#include "GridItem.hpp"

#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	// A row of tab labels with one highlighted as active, mirroring
	// stand-reference's src/Menu/GridItemTabsHorizontal.*. Clicking a tab
	// switches which one is active; GetActiveIndex() lets the owning Grid
	// (MenuGrid) read the current selection to decide what content to draw.
	class GridItemTabsHorizontal : public GridItem
	{
	public:
		GridItemTabsHorizontal(float height, std::vector<std::string> tabs, size_t activeIndex) :
		    GridItem(height),
		    m_Tabs(std::move(tabs)),
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

		// Sum of every tab's rendered width + gaps - the actual bounds
		// Draw() paints, unlike m_Width (unused by this widget's own
		// Draw/DrawText/OnClick, which lay out from m_X using natural
		// per-label widths). Callers that position this item manually
		// (MenuGrid) should pass this to SetPosition()'s width parameter
		// so GridItem::Contains() hit-tests the right region.
		float GetTotalWidth() const;

	private:
		std::vector<std::string> m_Tabs;
		size_t m_ActiveIndex;
	};
}
