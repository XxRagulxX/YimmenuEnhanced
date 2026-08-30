#include "VehicleSpawnGrid.hpp"

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
	VehicleSpawnGrid::VehicleSpawnGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void VehicleSpawnGrid::Populate()
	{
		// New Vehicle > Settings - both unconditional.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "New Vehicle", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawninsideveh"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawnvehmaxed"_J));

		// Personal Vehicle > Settings - both unconditional.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Personal Vehicle", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawninsidepv"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawnclonepv"_J));

		LOGF(INFO, "[GridRenderer] VehicleSpawnGrid populated with {} items", m_Items.size());
	}
}
