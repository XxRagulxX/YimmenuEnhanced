#include "VehicleSpawnGrid.hpp"

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
	VehicleSpawnGrid::VehicleSpawnGrid() :
	    Grid(168.f, 58.f, 300.f)
	{
	}

	void VehicleSpawnGrid::Populate()
	{
		// New Vehicle > Settings - both unconditional.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "New Vehicle"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawninsideveh"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawnvehmaxed"_J));

		// Personal Vehicle > Settings - both unconditional.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Personal Vehicle"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawninsidepv"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spawnclonepv"_J));

		LOGF(INFO, "[GridRenderer] VehicleSpawnGrid populated with {} items", m_Items.size());
	}
}
