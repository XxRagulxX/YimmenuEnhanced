#include "TeleportGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemHeader.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"

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
	TeleportGrid::TeleportGrid() :
	    Grid(168.f, 58.f, 300.f)
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
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Misc"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "autotptowaypoint"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "tptoobjective"_J));

		// Teleport's other category (the hand-rolled "Saved" locations
		// UI) - still placeholder-only, see TeleportGrid.hpp for why.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Categories"));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Saved", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] TeleportGrid populated with {} items", m_Items.size());
	}
}
