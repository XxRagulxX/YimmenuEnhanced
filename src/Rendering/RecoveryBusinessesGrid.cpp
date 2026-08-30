#include "RecoveryBusinessesGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
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

	// Origin (135, 47) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	RecoveryBusinessesGrid::RecoveryBusinessesGrid() :
	    Grid(135, 47, 3)
	{
	}

	void RecoveryBusinessesGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Business Safe (businessSafe) - a ListCommandItem (now that
		// GridItemCommandList exists) plus a plain CommandItem button,
		// both unconditional.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Business Safe", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "businesssafe"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "claimsafeearnings"_J));

		// Business Overlay (businessOverlay) - only the one unconditional
		// toggle; showwarehouse/showhangar/showbusinesses/shownightclub
		// are all ConditionalItems gated on it, skipped like every other
		// ConditionalItem here.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Business Overlay", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "businessoverlay"_J));

		// Business Manager (businessManager) - every item here is
		// unconditional, six plain CommandItem buttons plus two
		// BoolCommandItems.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Business Manager", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "resupplybusiness"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "hangerresupply"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "warehouseresupply"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "nightclubpopularity"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "salvageyardpopularity"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "moneyfrontheatremove"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "removeresupplycooldown"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "enforceeasiestmission"_J));

		LOGF(INFO, "[GridRenderer] RecoveryBusinessesGrid populated with {} items", items_draft.size());
	}
}
