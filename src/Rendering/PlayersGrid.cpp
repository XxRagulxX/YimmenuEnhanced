#include "PlayersGrid.hpp"

#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemPlayerList.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "KickGrid.hpp"
#include "PlaceholderGrid.hpp"
#include "Theme.hpp"
#include "ToxicGrid.hpp"
#include "TrollGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		ToxicGrid g_ToxicContent{};
		TrollGrid g_TrollContent{};
		KickGrid g_KickContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	PlayersGrid::PlayersGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void PlayersGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// DrawPlayerList()'s own spectate toggle + player list.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Players", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spectate"_J));
		items_draft.push_back(std::make_unique<GridItemPlayerList>(Theme::kContentWidth));

		// Every one of MenuPlayers.cpp's own categories.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Info", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Troll", &g_TrollContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Toxic", &g_ToxicContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Kick", &g_KickContent));

		LOGF(INFO, "[GridRenderer] PlayersGrid populated with {} items", items_draft.size());
	}
}
