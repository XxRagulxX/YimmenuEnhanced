#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Vehicle > Main: mirrors MenuVehicle.cpp's Globals,
	// Tools and Misc groups in full, wired the same way SelfGrid wires
	// Self > Main. boostbehavior is gated on modifyboostbehavior directly;
	// autodrivespeed/autodrivestyle are gated on IsAutoDriveEnabled()
	// (VehicleGrid.cpp) - autodrive OR npcautodrive being on, the same
	// combined-BoolCommand-predicate technique as SelfGrid.cpp's
	// ShouldClearOrSetWanted().
	//
	// Also the Vehicle submenu's root as far as MenuGrid/MenuNavigation
	// are concerned: Populate() appends a GridItemFolder row for each of
	// Vehicle's other categories (Spawn, Vehicle Editor, Saved Vehicles)
	// after the items above - see SelfGrid.hpp's identical note. Spawn's
	// folder points at a real content Grid (VehicleSpawnGrid, owned here
	// since nothing else reaches it) - see VehicleSpawnGrid.hpp for what
	// it covers. Vehicle Editor/Saved Vehicles still point at the shared
	// placeholder.
	class VehicleGrid : public Grid
	{
	public:
		VehicleGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
