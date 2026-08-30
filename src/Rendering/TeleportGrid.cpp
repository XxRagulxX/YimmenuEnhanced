#include "TeleportGrid.hpp"

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
	// convention as SelfGrid.cpp/VehicleGrid.cpp/MiscGrid.cpp - no shared
	// header for these yet).
	TeleportGrid::TeleportGrid() :
	    Grid(168.f, 94.f, 300.f)
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

		LOGF(INFO, "[GridRenderer] TeleportGrid populated with {} items", m_Items.size());
	}
}
