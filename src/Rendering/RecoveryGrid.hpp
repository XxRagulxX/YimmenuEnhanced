#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Recovery > Main: mirrors MenuRecovery.cpp's
	// generalGroup, wired the same way SelfGrid/VehicleGrid wire their
	// own unconditional items.
	//
	// Deliberately NOT included:
	// - rpmultiplierinput (ConditionalItem gated on overriderpmultiplier)
	//   - a FloatCommandItem, and no float widget exists yet, same reason
	//     SelfGrid's Movement group is skipped entirely.
	// All of Businesses/Casino and the Heists/Daily Activities/Stat
	// Editor/Transactions/Unlocks categories stay reachable via the
	// existing ImGui Recovery submenu, untouched.
	class RecoveryGrid : public Grid
	{
	public:
		RecoveryGrid();

	protected:
		void Populate() override;
	};
}
