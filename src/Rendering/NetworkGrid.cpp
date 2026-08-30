#include "NetworkGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemHeader.hpp"
#include "Joaat.hpp"
#include "NetworkSpoofingGrid.hpp"
#include "PlaceholderGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = 26.f;
		constexpr float kItemH = 28.f;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		NetworkSpoofingGrid g_SpoofingContent{};
	}

	// Position matches every other content Grid's (168, 58) - see the
	// comment in MenuGrid.cpp's anonymous namespace for why (no shared
	// header for these yet).
	NetworkGrid::NetworkGrid() :
	    Grid(168.f, 58.f, 300.f)
	{
	}

	void NetworkGrid::Populate()
	{
		// Join (joinGroup's joinSession subgroup) - joinsessiontype is an
		// unconditional ListCommandItem, now that GridItemCommandList
		// exists; joinsession/forcequittosp are both unconditional
		// CommandItem buttons. Label overrides match MenuNetwork.cpp's
		// own ("Session Type" instead of the registered "Join Session
		// Type"; "Join" instead of "Join##session" - the "##session"
		// suffix is an ImGui widget-ID disambiguator with no equivalent
		// need here).
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Join"));
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "joinsessiontype"_J, "Session Type"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "joinsession"_J, "Join"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "forcequittosp"_J));

		// Bounty (bountyGroup) - only anonymousbounty; see the class
		// comment for why bountyamount/setbountyall are skipped.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Bounty"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "anonymousbounty"_J, "Anonymous"));

		// Troll (trollGroup) - only harassplayers/spamkillfeed; see the
		// class comment for why sendsextall/deletevehall are skipped.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Troll"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "harassplayers"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spamkillfeed"_J));

		// Misc (miscGroup) - forcethunder is an unconditional
		// BoolCommandItem.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Misc"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "forcethunder"_J));

		// Enhancements (enhancements) - every item here is an
		// unconditional BoolCommandItem in the original, so all eight
		// map directly onto GridItemCommandToggle.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Enhancements"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "notifyonplayerjoin"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "fastjoin"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "disabledeathbarriers"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "despawnbypass"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "bypasscasinogeoblock"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "forcescripthost"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "pausegame"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "nocalls"_J));

		// Network's other categories (Spoofing, plus
		// BuildSavedPlayersMenu()/BuildRandomEventsMenu()'s own
		// Category("Saved Players")/("Random Events")). Spoofing now has
		// its own content Grid; the other two are still
		// placeholder-only.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Categories"));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Spoofing", &g_SpoofingContent));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Saved Players", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Random Events", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] NetworkGrid populated with {} items", m_Items.size());
	}
}
