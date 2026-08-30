#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Players > Troll: mirrors Troll.cpp's general/
	// bounty/vehicle groups exactly - bountyamount now has a real widget
	// (GridItemCommandInt), same as NetworkGrid's own identical row.
	class TrollGrid : public Grid
	{
	public:
		TrollGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
