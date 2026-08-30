#include "SelfGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemHeader.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"
#include "WeaponsGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = 26.f;
		constexpr float kItemH = 28.f;

		// Owned here rather than in MenuGrid.cpp: unlike SelfGrid itself
		// (Self's root, registered in MenuGrid's sidebar table),
		// WeaponsGrid is only ever reached through the "Weapons" folder
		// row below - nothing else needs to know it exists.
		WeaponsGrid g_WeaponsContent{};
	}

	// Position matches every other content Grid's (168, 58) - see the
	// comment in MenuGrid.cpp's anonymous namespace for why (no shared
	// header for these yet).
	SelfGrid::SelfGrid() :
	    Grid(168.f, 58.f, 300.f)
	{
	}

	void SelfGrid::Populate()
	{
		// Globals (MenuSelf.cpp's globalsGroup) - every item here is an
		// unconditional BoolCommandItem in the original, so all nine map
		// directly onto GridItemCommandToggle. localvis is skipped: it's a
		// ConditionalItem gated on invis, and this system has no
		// conditional-visibility widget yet.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Globals"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "godmode"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "invis"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "otr"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "noragdoll"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "noidlekick"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "unlimitedoxygen"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mobileradio"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "keepplayerclean"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "disablecriticalhits"_J));

		// Tools (toolsGroup) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Tools"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "skipcutscene"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "skipconversation"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "suicide"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "heal"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "cleardamage"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "fillinventory"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "openwardrobe"_J));

		// Special Ability (specialAbilityGroup) - only the two
		// unconditional toggles; the ListCommandItem dropdown is gated
		// behind a ConditionalItem on mpspecialability, skipped for the
		// same reason as localvis above.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Special Ability"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "infspecialability"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mpspecialability"_J, "Enable in MP"));

		// Self's other categories (MenuSelf.cpp's BuildWeaponsMenu()/
		// CreateOutfitsMenu()). Weapons now has its own content Grid
		// (WeaponsGrid); Outfit Editor is still placeholder-only.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Categories"));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Weapons", &g_WeaponsContent));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Outfit Editor", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] SelfGrid populated with {} items", m_Items.size());
	}
}
