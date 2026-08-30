#include "RecoveryGrid.hpp"

#include "GridItemCommandFloat.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemConditional.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"
#include "RecoveryBusinessesGrid.hpp"
#include "RecoveryCasinoGrid.hpp"
#include "RecoveryHeistsGrid.hpp"
#include "RecoveryUnlocksGrid.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		RecoveryBusinessesGrid g_BusinessesContent{};
		RecoveryHeistsGrid g_HeistsContent{};
		RecoveryCasinoGrid g_CasinoContent{};
		RecoveryUnlocksGrid g_UnlocksContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	RecoveryGrid::RecoveryGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void RecoveryGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// General (MenuRecovery.cpp's generalGroup) - rpmultiplierinput is
		// gated on overriderpmultiplier directly, now that
		// GridItemCommandFloat/GridItemConditional both exist.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "General", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playallmissionssolo"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "unlockgtaplus"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "overriderpmultiplier"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "rpmultiplierinput"_J),
		    "overriderpmultiplier"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freechangeappearance"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "nochangeappearancecooldown"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "allowgenderchange"_J));

		// Recovery's other categories (Businesses/Heists/Casino/Unlocks,
		// plus BuildDailyActivitiesMenu()/BuildStatEditorMenu()/
		// BuildTransactionsMenu()). Businesses/Heists/Casino/Unlocks now
		// have their own content Grids; the other two are still
		// placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Businesses", &g_BusinessesContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Heists", &g_HeistsContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Daily Activities", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Stat Editor", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Transactions", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Casino", &g_CasinoContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Unlocks", &g_UnlocksContent));

		LOGF(INFO, "[GridRenderer] RecoveryGrid populated with {} items", items_draft.size());
	}
}
