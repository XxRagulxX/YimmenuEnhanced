#include "VehicleSpawnGrid.hpp"

#include "GridItemCommandToggle.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"

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
	VehicleSpawnGrid::VehicleSpawnGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void VehicleSpawnGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// New Vehicle > Settings - both unconditional.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "New Vehicle", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spawninsideveh"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spawnvehmaxed"_J));

		// Personal Vehicle > Settings - both unconditional.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Personal Vehicle", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spawninsidepv"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spawnclonepv"_J));

		LOGF(INFO, "[GridRenderer] VehicleSpawnGrid populated with {} items", items_draft.size());
	}
}
