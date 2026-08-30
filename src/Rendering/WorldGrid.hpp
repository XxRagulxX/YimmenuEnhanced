#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for World > Main: mirrors MenuWorld.cpp's Kill,
	// Delete, Bring, Weather, Time and Other groups in full, now that
	// GridItemConditional/GridItemCommandInt exist (setweather's own
	// ConditionalItem, and Time's three IntCommand-bound steppers).
	//
	// Populate() also appends a GridItemFolder row for each of
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
