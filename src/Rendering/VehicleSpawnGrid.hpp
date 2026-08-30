#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Vehicle > Spawn: mirrors SpawnVehicle.cpp's two
	// Settings groups (New Vehicle's spawninsideveh/spawnvehmaxed,
	// Personal Vehicle's spawninsidepv/spawnclonepv) - all four are
	// unconditional BoolCommandItems.
	//
	// Deliberately NOT included: the actual spawn UI itself - both tabs'
	// Spawn groups are a single ImGuiItem each (a search box + vehicle-
	// class filter + scrollable result list for New Vehicle, a similar
	// list of the player's own personal vehicles for Personal Vehicle),
	// with no equivalent widgets here (searchable/filterable list, plus
	// TabItem/TabBarItem for the New Vehicle/Personal Vehicle split
	// itself). Stays reachable via the existing ImGui Vehicle > Spawn
	// category, untouched.
	class VehicleSpawnGrid : public Grid
	{
	public:
		VehicleSpawnGrid();

	protected:
		void Populate() override;
	};
}
