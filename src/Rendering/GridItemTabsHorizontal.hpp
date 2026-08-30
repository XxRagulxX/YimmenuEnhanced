#pragma once
#include "GridItem.hpp"

#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	// A row of tab labels with one highlighted as active, mirroring
	// stand-reference's src/Menu/GridItemTabsHorizontal.*. Clicking a tab
	// switches which one is active; GetActiveIndex() lets the owning
	// Grid read the current selection to decide what content to draw.
	//
	// Not currently used anywhere: MenuGrid used this for
	// submenu-category navigation in an earlier version, but Stand's own
	// menu doesn't use a tab strip there at all (see MenuNavigation.hpp/
	// GridItemFolder.hpp for what replaced it) - kept as a working,
	// self-contained widget in case something else genuinely needs a tab
	// row later, same as stand-reference itself still carries the type.
	class GridItemTabsHorizontal : public GridItem
	{
	public:
		GridItemTabsHorizontal(float height, std::vector<std::string> tabs, size_t activeIndex) :
		    GridItem(GRIDITEM_TABS, static_cast<int16_t>(GetTotalWidth(tabs)), static_cast<int16_t>(height)),
		    m_Tabs(std::move(tabs)),
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

	private:
		// Sum of every tab's rendered width + gaps - computed up front
		// (GridItem now needs its width at construction, unlike before
		// this port) rather than lazily after positioning.
		static float GetTotalWidth(const std::vector<std::string>& tabs);

		std::vector<std::string> m_Tabs;
		size_t m_ActiveIndex;
	};
}
