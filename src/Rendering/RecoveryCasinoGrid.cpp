#include "Rendering/RecoveryCasinoGrid.hpp"

#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	RecoveryCasinoGrid::RecoveryCasinoGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void RecoveryCasinoGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Slot Machines (casinoSlots)
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Slot Machines", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "casinomanipulaterigslotmachines"_J));
	}
}
