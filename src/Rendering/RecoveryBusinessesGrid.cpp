#include "RecoveryBusinessesGrid.hpp"

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
	RecoveryBusinessesGrid::RecoveryBusinessesGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void RecoveryBusinessesGrid::Populate()
	{
		// Business Safe (businessSafe) - a ListCommandItem (now that
		// GridItemCommandList exists) plus a plain CommandItem button,
		// both unconditional.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Business Safe", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "businesssafe"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "claimsafeearnings"_J));

		// Business Overlay (businessOverlay) - only the one unconditional
		// toggle; showwarehouse/showhangar/showbusinesses/shownightclub
		// are all ConditionalItems gated on it, skipped like every other
		// ConditionalItem here.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Business Overlay", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "businessoverlay"_J));

		// Business Manager (businessManager) - every item here is
		// unconditional, six plain CommandItem buttons plus two
		// BoolCommandItems.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Business Manager", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "resupplybusiness"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "hangerresupply"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "warehouseresupply"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "nightclubpopularity"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "salvageyardpopularity"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "moneyfrontheatremove"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "removeresupplycooldown"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "enforceeasiestmission"_J));

		LOGF(INFO, "[GridRenderer] RecoveryBusinessesGrid populated with {} items", m_Items.size());
	}
}
