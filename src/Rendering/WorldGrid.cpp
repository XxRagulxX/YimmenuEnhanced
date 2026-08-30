#include "WorldGrid.hpp"

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
	// convention as SelfGrid.cpp/VehicleGrid.cpp/TeleportGrid.cpp/
	// RecoveryGrid.cpp/MiscGrid.cpp - no shared header for these yet).
	WorldGrid::WorldGrid() :
	    Grid(168.f, 94.f, 300.f)
	{
	}

	void WorldGrid::Populate()
	{
		// Kill (killPeds) - both plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Kill"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "killallpeds"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "killallenemies"_J));

		// Delete (deleteOpts) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Delete"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delpeds"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delvehs"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delobjs"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delcams"_J));

		// Bring (bringOpts) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Bring"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "bringpeds"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "bringvehs"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "bringobjs"_J));

		// Other (otherOpts) - every item here is an unconditional
		// BoolCommandItem in the original, so all five map directly onto
		// GridItemCommandToggle.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Other"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "pedsignore"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "PedRiotMode"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "CopsDispatch"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "enablecreatordevmode"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "infiniteboundary"_J));

		LOGF(INFO, "[GridRenderer] WorldGrid populated with {} items", m_Items.size());
	}
}
