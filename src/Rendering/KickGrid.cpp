#include "Rendering/KickGrid.hpp"

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
	KickGrid::KickGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void KickGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Kicks (kicks Group) - every item is a PlayerCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Kicks", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "hkick"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "shkick"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "endkick"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "nfkick"_J));

		// Other (other Group) - one PlayerCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Other", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "blackscreen"_J));
	}
}
