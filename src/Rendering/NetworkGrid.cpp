#include "Rendering/NetworkGrid.hpp"

#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/NetworkSpoofingGrid.hpp"
#include "Rendering/RandomEventsGrid.hpp"
#include "Rendering/SavedPlayersGrid.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		NetworkSpoofingGrid g_SpoofingContent{};
		SavedPlayersGrid g_SavedPlayersContent{};
		RandomEventsGrid g_RandomEventsContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	NetworkGrid::NetworkGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void NetworkGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Network's other categories (Spoofing/Saved Players, plus
		// BuildRandomEventsMenu()'s own Category("Random Events")) -
		// grouped at the very top of the whole list rather than at the
		// bottom, so a category is always reachable before the plain
		// toggles below. Every one of these now has its own real content
		// Grid.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Spoofing", &g_SpoofingContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Saved Players", &g_SavedPlayersContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Random Events", &g_RandomEventsContent));

		// Join (joinGroup's joinSession subgroup) - joinsessiontype is an
		// unconditional ListCommandItem, now that GridItemCommandList
		// exists; joinsession/forcequittosp are both unconditional
		// CommandItem buttons. Label overrides match MenuNetwork.cpp's
		// own ("Session Type" instead of the registered "Join Session
		// Type"; "Join" instead of "Join##session" - the "##session"
		// suffix is an ImGui widget-ID disambiguator with no equivalent
		// need here).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Join", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "joinsessiontype"_J, "Session Type"));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "joinsession"_J, "Join"));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "forcequittosp"_J));

		// Bounty (bountyGroup) - bountyamount now has a real widget
		// (GridItemCommandInt); setbountyall is still skipped - see the
		// class comment for why.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Bounty", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "bountyamount"_J, "Amount"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "anonymousbounty"_J, "Anonymous"));

		// Troll (trollGroup) - only harassplayers/spamkillfeed; see the
		// class comment for why sendsextall/deletevehall are skipped.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Troll", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "harassplayers"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spamkillfeed"_J));

		// Misc (miscGroup) - forcethunder is an unconditional
		// BoolCommandItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Misc", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "forcethunder"_J));

		// Enhancements (enhancements) - every item here is an
		// unconditional BoolCommandItem in the original, so all eight
		// map directly onto GridItemCommandToggle.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Enhancements", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "notifyonplayerjoin"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "fastjoin"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "disabledeathbarriers"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "despawnbypass"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "bypasscasinogeoblock"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "forcescripthost"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "pausegame"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "nocalls"_J));
	}
}
