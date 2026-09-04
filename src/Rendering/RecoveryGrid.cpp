#include "Rendering/RecoveryGrid.hpp"

#include "Rendering/GridItemCommandFloat.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/PlaceholderGrid.hpp"
#include "Rendering/DailyActivitiesGrid.hpp"
#include "Rendering/RecoveryBusinessesGrid.hpp"
#include "Rendering/RecoveryCasinoGrid.hpp"
#include "Rendering/RecoveryHeistsGrid.hpp"
#include "Rendering/RecoveryUnlocksGrid.hpp"
#include "Rendering/Theme.hpp"

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
		DailyActivitiesGrid g_DailyActivitiesContent{};
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
		// Categories (MenuRecovery.cpp's Businesses/Heists/Daily
		// Activities/Casino/Unlocks, plus BuildStatEditorMenu()/
		// BuildTransactionsMenu()) - every GridItemFolder this page has,
		// grouped at the very top of the whole list rather than at the
		// bottom, so a category is always reachable before General's
		// plain toggles below. Businesses/Heists/Daily Activities/Casino/
		// Unlocks have their own content Grids; the other two are still
		// placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Businesses", &g_BusinessesContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Heists", &g_HeistsContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Daily Activities", &g_DailyActivitiesContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Stat Editor", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Transactions", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Casino", &g_CasinoContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Unlocks", &g_UnlocksContent));

		// General (MenuRecovery.cpp's generalGroup) - watchCondition()
		// (not GridItemConditional) so rpmultiplierinput doesn't reserve
		// its own layout slot while overriderpmultiplier is off - see
		// Grid::watchCondition()'s own doc comment for why.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "General", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playallmissionssolo"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "unlockgtaplus"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "overriderpmultiplier"_J));
		if (watchCondition("overriderpmultiplier"_J))
			items_draft.push_back(std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "rpmultiplierinput"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freechangeappearance"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "nochangeappearancecooldown"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "allowgenderchange"_J));
	}
}
