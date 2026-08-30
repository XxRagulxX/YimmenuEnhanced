#include "WeaponsGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	WeaponsGrid::WeaponsGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void WeaponsGrid::Populate()
	{
		// Tools (weaponsToolsGroup) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Tools", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "giveallweapons"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "givemaxammo"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "opengunlocker"_J));

		// Gun Van (weaponsGunVanGroup) - all three items are
		// unconditional (two ListCommandItems, now that
		// GridItemCommandList exists, plus a plain CommandItem button).
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Gun Van", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "gunvan_weapon"_J));
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "gunvan_slot"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "gunvan_apply"_J));

		// Aimbot (weaponsAimbotGroup) - only the one unconditional
		// toggle; aimbotaimforhead/aimbottargetdrivers/
		// aimbotreleasedeadped are all ConditionalItems gated on aimbot
		// being on, skipped like every other ConditionalItem here.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Aimbot", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "aimbot"_J));

		LOGF(INFO, "[GridRenderer] WeaponsGrid populated with {} items", m_Items.size());
	}
}
