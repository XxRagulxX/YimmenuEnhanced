#include "RecoveryGrid.hpp"

#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"
#include "RecoveryBusinessesGrid.hpp"
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
		// General (MenuRecovery.cpp's generalGroup) - every unconditional
		// BoolCommandItem maps directly onto GridItemCommandToggle.
		// rpmultiplierinput is skipped: it's a ConditionalItem gated on
		// overriderpmultiplier, and this system has no float widget yet.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "General", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playallmissionssolo"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "unlockgtaplus"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "overriderpmultiplier"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freechangeappearance"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "nochangeappearancecooldown"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "allowgenderchange"_J));

		// Recovery's other categories (Businesses/Casino, plus
		// BuildHeistModifierMenu()/BuildDailyActivitiesMenu()/
		// BuildStatEditorMenu()/BuildTransactionsMenu()/
		// BuildUnlockerMenu()). Businesses now has its own content Grid;
		// the other six are still placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Businesses", &g_BusinessesContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Heists", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Daily Activities", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Stat Editor", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Transactions", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Casino", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Unlocks", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] RecoveryGrid populated with {} items", items_draft.size());
	}
}
