#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for World > Main: mirrors MenuWorld.cpp's Kill,
	// Delete, Bring and Other groups (all unconditional CommandItem/
	// BoolCommandItem), wired the same way SelfGrid/VehicleGrid wire
	// their own unconditional items.
	//
	// Deliberately NOT included (both whole groups need widgets this
	// system doesn't have yet, so nothing here fakes them):
	// - Weather - built around a ListCommandItem (weather selector), and
	//   there's no list/dropdown widget yet.
	// - Time - built around three IntCommandItems (hour/minute/second)
	//   bound directly to real IntCommands; GridItemIntStepper (used by
	//   MiscGrid) only tracks its own local value fed to a button click,
	//   there's no stepper wired to a live IntCommand yet.
	// Both stay reachable via the existing ImGui World > Main category,
	// untouched. Populate() also appends a GridItemFolder row for each of
	// World's other categories (Spawn Ped, IPLs), pointing at the shared
	// placeholder - same as SelfGrid.hpp's note.
	class WorldGrid : public Grid
	{
	public:
		WorldGrid();

	protected:
		void Populate() override;
	};
}
