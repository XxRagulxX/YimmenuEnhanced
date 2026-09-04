#include "Rendering/LevitationGrid.hpp"

#include "Rendering/GridItemCommandFloat.hpp"
#include "Rendering/GridItemCommandInt.hpp"
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

	LevitationGrid::LevitationGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void LevitationGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "levitate"_J));

		for (auto hash : {"levitateignorepitch"_J,
		         "keepmomentum"_J,
		         "levitateapplypitch"_J,
		         "levitaterotate"_J,
		         "levitatebuttoninstructions"_J})
		{
			items_draft.push_back(std::make_unique<GridItemConditional>(
			    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, hash),
			    "levitate"_J));
		}

		for (auto hash : {"levitatespeed"_J,
		         "levitatesprintmultiplier"_J,
		         "levitateaccel"_J,
		         "levitatepassivemin"_J,
		         "levitatepassivemax"_J,
		         "levitateassistup"_J,
		         "levitateassistdown"_J,
		         "levitateassistsnap"_J})
		{
			items_draft.push_back(std::make_unique<GridItemConditional>(
			    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, hash),
			    "levitate"_J));
		}

		for (auto hash : {"levitatepassivespeed"_J, "levitateassistdeadzone"_J})
		{
			items_draft.push_back(std::make_unique<GridItemConditional>(
			    std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, hash),
			    "levitate"_J));
		}
	}
}
