#include "TeleportGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"
#include "PlaceholderGrid.hpp"

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
	TeleportGrid::TeleportGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void TeleportGrid::Populate()
	{
		// Misc (MenuTeleport.cpp's miscGroup) - autotptowaypoint is an
		// unconditional BoolCommandItem, so it maps directly onto
		// GridItemCommandToggle. tptowaypoint is skipped: it's a
		// ConditionalItem only shown while autotptowaypoint is off, and
		// this system has no conditional-visibility widget yet.
		// tptoobjective is an unconditional CommandItem button.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Misc", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "autotptowaypoint"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "tptoobjective"_J));

		// Teleport's other category (the hand-rolled "Saved" locations
		// UI) - still placeholder-only, see TeleportGrid.hpp for why.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Categories", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Saved", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] TeleportGrid populated with {} items", m_Items.size());
	}
}
