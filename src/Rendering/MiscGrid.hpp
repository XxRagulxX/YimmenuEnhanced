#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// First real (non-decorative) menu grid: mirrors Debug > Misc's
	// existing ImGui items (src/Misc.cpp), wired to their actual
	// commands/actions rather than placeholder state.
	//
	// Not a full replacement of Misc's ImGui rendering yet: DoTeleport and
	// the "fm_mission_controller DoTeamSwap" button both need numeric
	// input (interiorIndex/enterOwnerInterior, Team) that this system has
	// no widget for yet, so they're deliberately left out here - the
	// existing ImGui Misc category is untouched and still the only way to
	// reach those two actions.
	class MiscGrid : public Grid
	{
	public:
		MiscGrid();

	protected:
		void Populate() override;
	};
}
