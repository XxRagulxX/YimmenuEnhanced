#pragma once
#include "GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	// A title bar: solid accent-colour background with a white label -
	// MenuGrid's own top breadcrumb bar ("YimMenu > Vehicle > Spawner"),
	// matching Stand's real address bar (always shown in its one accent
	// colour, since it's always showing "where you are"). NOT used for
	// in-list section labels any more (a content Grid's own "Globals"/
	// "Tools"/... group headings) - Stand's own screenshots show those
	// as plain text with no background bar at all (see e.g. "Settings"
	// midway down its Vehicle > Spawner list), so those use GridItemText
	// instead now. Purely decorative for now - no collapse/drag
	// behaviour yet (that needs the input pass).
	//
	// Typed GRIDITEM_PRIMARYTEXT and named to match stand-reference's own
	// src/Menu/GridItemPrimaryText.hpp/.cpp (Stand's real address bar
	// widget, looked up by MenuGrid::doUpdateAddress() by exactly this
	// type) - this project's own GridItemHeader is unrelated: real
	// Stand's GridItemHeader (src/Menu/GridItemHeader.hpp) is a pure
	// abstract base (`draw() override = 0`) with no text/label content of
	// its own at all, so it has nothing in common with this widget beyond
	// the name.
	class GridItemPrimaryText : public GridItem
	{
	public:
		GridItemPrimaryText(int16_t width, int16_t height, std::string title) :
		    GridItem(GRIDITEM_PRIMARYTEXT, width, height),
		    m_Title(std::move(title))
		{
		}

		void draw() override;
		void drawText() override;

		// Lets MenuGrid update the breadcrumb text every frame (e.g.
		// "YimMenu > Vehicle > Spawner") without rebuilding this item -
		// same "don't rebuild the widget itself per frame" rule as the
		// rest of this Grid/GridItem system.
		void SetTitle(std::string title)
		{
			m_Title = std::move(title);
		}

	private:
		std::string m_Title;
	};
}
