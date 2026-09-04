#include "Rendering/SuperRunGrid.hpp"

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

	SuperRunGrid::SuperRunGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void SuperRunGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "superrun"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "moverateoverride"_J),
		    "superrun"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "runsprintswimmultiplier"_J),
		    "superrun"_J));
	}
}
