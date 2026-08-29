#pragma once
#include "GridItem.hpp"

#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	// A row of tab labels with one highlighted as active, mirroring
	// stand-reference's src/Menu/GridItemTabsHorizontal.*. Clicking a tab
	// switches which one is active - not yet wired to actually swap the
	// grid's contents (that's follow-up work once a real menu page uses
	// this instead of TestGrid).
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

	private:
		std::vector<std::string> m_Tabs;
		size_t m_ActiveIndex;
	};
}
