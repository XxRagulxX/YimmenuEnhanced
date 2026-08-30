#include "TeleportGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"
#include "PlaceholderGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Origin (135, 47) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	TeleportGrid::TeleportGrid() :
	    Grid(135, 47, 3)
	{
	}

	void TeleportGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Misc (MenuTeleport.cpp's miscGroup) - autotptowaypoint is an
		// unconditional BoolCommandItem, so it maps directly onto
		// GridItemCommandToggle. tptowaypoint is skipped: it's a
		// ConditionalItem only shown while autotptowaypoint is off, and
		// this system has no conditional-visibility widget yet.
		// tptoobjective is an unconditional CommandItem button.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Misc", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "autotptowaypoint"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "tptoobjective"_J));

		// Teleport's other category (the hand-rolled "Saved" locations
		// UI) - still placeholder-only, see TeleportGrid.hpp for why.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Saved", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] TeleportGrid populated with {} items", items_draft.size());
	}
}
