#include "Rendering/TeleportGrid.hpp"

#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemConditional.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/TeleportSavedGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		TeleportSavedGrid g_SavedContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	TeleportGrid::TeleportGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void TeleportGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Misc (MenuTeleport.cpp's miscGroup) - tptowaypoint is gated on
		// autotptowaypoint being *off* (negate).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Misc", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "tptowaypoint"_J),
		    "autotptowaypoint"_J,
		    true));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "autotptowaypoint"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "tptoobjective"_J));

		// Teleport's other category (the hand-rolled "Saved" locations
		// UI) - now has its own content Grid.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Saved", &g_SavedContent));
	}
}
