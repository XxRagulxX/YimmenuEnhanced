#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for World > Main: mirrors MenuWorld.cpp's Kill,
	// Delete, Bring, Weather and Other groups (all unconditional
	// CommandItem/BoolCommandItem/ListCommandItem), wired the same way
	// SelfGrid/VehicleGrid wire their own unconditional items.
	//
	// Deliberately NOT included:
	// - setweather (ConditionalItem, only shown while forceweather is
	//   off) - no conditional-visibility widget yet, same reason every
	//   other ConditionalItem in this system is skipped.
	// - The whole Time group - built around three IntCommandItems (hour/
	//   minute/second) bound directly to real IntCommands;
	//   GridItemIntStepper (used by MiscGrid) only tracks its own local
	//   value fed to a button click, there's no stepper wired to a live
	//   IntCommand yet.
	// Both stay reachable via the existing ImGui World > Main category,
	// untouched. Populate() also appends a GridItemFolder row for each of
	// World's other categories (Spawn Ped, IPLs). IPLs' folder points at
	// a real content Grid (WorldIPLsGrid, owned here since nothing else
	// reaches it) - see WorldIPLsGrid.hpp for what it covers. Spawn Ped
	// still points at the shared placeholder.
	class WorldGrid : public Grid
	{
	public:
		WorldGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
