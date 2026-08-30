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
	// Typed GRIDITEM_PRIMARYTEXT, matching Stand's own address bar
	// (GridItemPrimaryText) - Stand's real MenuGrid::doUpdateAddress()
	// looks it up by exactly this type.
	class GridItemHeader : public GridItem
	{
	public:
		GridItemHeader(int16_t width, int16_t height, std::string title) :
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
