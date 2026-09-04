#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Recovery > Main: mirrors MenuRecovery.cpp's
	// generalGroup in full, wired the same way SelfGrid/VehicleGrid wire
	// their own conditional items.
	//
	// Transactions still stays reachable via the existing ImGui Recovery
	// submenu, untouched - populate() still appends a GridItemFolder row
	// for it, same as SelfGrid.hpp's note. Businesses/Heists/Daily
	// Activities/Stat Editor/Casino/Unlocks' folders each point at a real
	// content Grid (RecoveryBusinessesGrid/RecoveryHeistsGrid/
	// DailyActivitiesGrid/StatEditorGrid/RecoveryCasinoGrid/
	// RecoveryUnlocksGrid, owned here since nothing else reaches them);
	// Transactions still points at the shared placeholder.
	class RecoveryGrid : public Grid
	{
	public:
		RecoveryGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
