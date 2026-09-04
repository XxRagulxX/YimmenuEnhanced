#include "Rendering/FreecamGrid.hpp"

#include "Rendering/GridItemCommandFloat.hpp"
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

	FreecamGrid::FreecamGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void FreecamGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freecam"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "freecamspeed"_J),
		    "freecam"_J));
	}
}
