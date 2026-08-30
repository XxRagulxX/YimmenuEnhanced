#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Teleport > Main: mirrors MenuTeleport.cpp's Misc
	// group, wired the same way SelfGrid/VehicleGrid wire their own
	// unconditional items.
	//
	// Deliberately NOT included:
	// - tptowaypoint (ConditionalItem, only shown while autotptowaypoint
	//   is OFF) - no conditional-visibility widget yet, same reason
	//   SelfGrid/VehicleGrid skip their own ConditionalItems.
	// - The whole "Saved" category - a hand-rolled ImGui UI (category/
	//   location list boxes, a name/category text entry, a delete
	//   confirmation popup, double-click-to-teleport) with no Grid
	//   equivalent widgets yet (list selection, text entry, popups). Stays
	//   reachable via the existing ImGui Teleport > Saved category,
	//   untouched - Populate() still appends a GridItemFolder row for it
	//   (pointing at the shared placeholder), same as SelfGrid.hpp's note.
	class TeleportGrid : public Grid
	{
	public:
		TeleportGrid();

	protected:
		void Populate() override;
	};
}
