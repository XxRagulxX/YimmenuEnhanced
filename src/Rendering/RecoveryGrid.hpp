#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Recovery > Main: mirrors MenuRecovery.cpp's
	// generalGroup in full, wired the same way SelfGrid/VehicleGrid wire
	// their own conditional items.
	//
	// The Daily Activities/Stat Editor/Transactions categories stay
	// reachable via the existing ImGui Recovery submenu, untouched -
	// Populate() still appends a GridItemFolder row for each, same as
	// SelfGrid.hpp's note. Businesses/Heists/Casino/Unlocks' folders
	// each point at a real content Grid (RecoveryBusinessesGrid/
	// RecoveryHeistsGrid/RecoveryCasinoGrid/RecoveryUnlocksGrid, owned
	// here since nothing else reaches them); the other two still point
	// at the shared placeholder.
	class RecoveryGrid : public Grid
	{
	public:
		RecoveryGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
