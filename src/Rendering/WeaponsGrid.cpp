#include "WeaponsGrid.hpp"

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

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	WeaponsGrid::WeaponsGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void WeaponsGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Tools (weaponsToolsGroup) - all plain CommandItem buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Tools", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "giveallweapons"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "givemaxammo"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "opengunlocker"_J));

		// Gun Van (weaponsGunVanGroup) - all three items are
		// unconditional (two ListCommandItems, now that
		// GridItemCommandList exists, plus a plain CommandItem button).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Gun Van", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "gunvan_weapon"_J));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "gunvan_slot"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "gunvan_apply"_J));

		// Aimbot (weaponsAimbotGroup) - only the one unconditional
		// toggle; aimbotaimforhead/aimbottargetdrivers/
		// aimbotreleasedeadped are all ConditionalItems gated on aimbot
		// being on, skipped like every other ConditionalItem here.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Aimbot", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "aimbot"_J));

		LOGF(INFO, "[GridRenderer] WeaponsGrid populated with {} items", items_draft.size());
	}
}
