#include "Rendering/ToxicGrid.hpp"

#include "Rendering/GridItemCommandPlayer.hpp"
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
	ToxicGrid::ToxicGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void ToxicGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Damage (damage Group) - every item is a PlayerCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Damage", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "kill"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "killexploit"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "explode"_J));

		// Griefing (griefing Group) - one PlayerCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Griefing", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "ceokick"_J));

		LOGF(INFO, "[GridRenderer] ToxicGrid populated with {} items", items_draft.size());
	}
}
