#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	class GridItemIntStepper;
	class GridItemToggle;

	// First real (non-decorative) menu grid: mirrors Debug > Misc's
	// existing ImGui items (src/Misc.cpp), wired to their actual
	// commands/actions rather than placeholder state.
	//
	// Not a full replacement of Misc's ImGui rendering yet: there's no
	// keyboard text-entry system, so interiorIndex/Team use stepper
	// buttons (GridItemIntStepper) instead of free-form ImGui::InputInt
	// text fields. The existing ImGui Misc category is untouched and
	// still available as the free-form-entry alternative.
	class MiscGrid : public Grid
	{
	public:
		MiscGrid();

	protected:
		void Populate() override;

	private:
		// Non-owning: m_Items owns the actual objects. Kept so the
		// DoTeleport/DoTeamSwap button callbacks can read their current
		// values at click time - mirrors Misc.cpp's own function-local
		// static int/bool captured by its ImGui button lambdas.
		GridItemIntStepper* m_InteriorIndexStepper = nullptr;
		GridItemToggle* m_EnterOwnerInteriorToggle = nullptr;
		GridItemIntStepper* m_TeamStepper = nullptr;
	};
}
