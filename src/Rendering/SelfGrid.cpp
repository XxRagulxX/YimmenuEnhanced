#include "SelfGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemHeader.hpp"
#include "Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = 26.f;
		constexpr float kItemH = 28.f;
	}

	// Position matches MenuGrid.cpp's kContentX/kContentY exactly (same
	// convention as MiscGrid.cpp - no shared header for these yet).
	SelfGrid::SelfGrid() :
	    Grid(168.f, 94.f, 270.f)
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

		LOGF(INFO, "[GridRenderer] SelfGrid populated with {} items", m_Items.size());
	}
}
