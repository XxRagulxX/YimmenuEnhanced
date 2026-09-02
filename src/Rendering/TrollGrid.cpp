#include "Rendering/TrollGrid.hpp"

#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandPlayer.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
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
	TrollGrid::TrollGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void TrollGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// General (general Group) - every item is a PlayerCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "General", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "sendsext"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "sendphantomcar"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "sendgooch"_J));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "giveweapons"_J));

		// Bounty (bounty Group) - amount is an IntCommandItem, now
		// GridItemCommandInt; anonymous is a BoolCommandItem; setbounty
		// is a PlayerCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Bounty", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "bountyamount"_J, "Amount"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "anonymousbounty"_J, "Anonymous"));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "setbounty"_J));

		// Vehicle (vehicle Group) - one PlayerCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Vehicle", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandPlayer>(Theme::kContentWidth, kItemH, "deleteveh"_J));

		LOGF(INFO, "[GridRenderer] TrollGrid populated with {} items", items_draft.size());
	}
}
