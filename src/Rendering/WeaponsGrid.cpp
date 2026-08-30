#include "WeaponsGrid.hpp"

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

	// Position matches every other content Grid's (168, 58) - see the
	// comment in MenuGrid.cpp's anonymous namespace for why (no shared
	// header for these yet).
	WeaponsGrid::WeaponsGrid() :
	    Grid(168.f, 58.f, 300.f)
	{
	}

	void WeaponsGrid::Populate()
	{
		// Tools (weaponsToolsGroup) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Tools"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "giveallweapons"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "givemaxammo"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "opengunlocker"_J));

		// Aimbot (weaponsAimbotGroup) - only the one unconditional
		// toggle; aimbotaimforhead/aimbottargetdrivers/
		// aimbotreleasedeadped are all ConditionalItems gated on aimbot
		// being on, skipped like every other ConditionalItem here.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Aimbot"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "aimbot"_J));

		LOGF(INFO, "[GridRenderer] WeaponsGrid populated with {} items", m_Items.size());
	}
}
