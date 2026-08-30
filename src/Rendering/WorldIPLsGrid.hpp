#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for World > IPLs: mirrors MenuWorld.cpp's iplsGroup -
	// all four items (the iplselector ListCommandItem plus three plain
	// CommandItem buttons) are unconditional, so nothing here is skipped.
	class WorldIPLsGrid : public Grid
	{
	public:
		WorldIPLsGrid();

	protected:
		void Populate() override;
	};
}
