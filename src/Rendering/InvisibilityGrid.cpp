#include "Rendering/InvisibilityGrid.hpp"

#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemConditional.hpp"
#include "Rendering/Theme.hpp"
#include "Util/Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Same origin every content Grid uses (see MenuGrid.cpp's own
	// comment for why) - this one's just reached via a GridItemFolder
	// row instead of the sidebar.
	InvisibilityGrid::InvisibilityGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void InvisibilityGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "invis"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "localvis"_J),
		    "invis"_J));
	}
}
