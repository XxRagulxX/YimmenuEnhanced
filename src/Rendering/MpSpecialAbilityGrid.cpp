#include "Rendering/MpSpecialAbilityGrid.hpp"

#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/Theme.hpp"
#include "Util/Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	MpSpecialAbilityGrid::MpSpecialAbilityGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void MpSpecialAbilityGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mpspecialability"_J, "Enable in MP"));

		if (watchCondition("mpspecialability"_J))
			items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "selspecialability"_J, "Special Ability"));
	}
}
