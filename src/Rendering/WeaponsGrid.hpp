#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Self > Weapons: mirrors Weapons.cpp's
	// BuildWeaponsMenu() Globals, Tools, Gun Van, Aimbot and Custom
	// Weapons groups in full, wired the same way SelfGrid wires Self >
	// Main - see WeaponsGrid.cpp's own predicate functions
	// (IsCustomWeaponEnabled()/CustomWeaponType()/IsGravityGunRow()/...)
	// for how RenderCustomWeaponsMenu()'s several levels of nested
	// ConditionalItem/Group flatten onto individual GridItemConditional
	// rows.
	//
	// Deliberately NOT included: Ammu-Nation, a hand-rolled ImGui weapon
	// search/stats/list-box UI - deferred to Phase 3 once the
	// searchable-list primitive (GridItemSelectList) has a
	// search-list-plus-detail-pane consumer to model it on. Stays
	// reachable via the existing ImGui Self > Weapons category until
	// then.
	class WeaponsGrid : public Grid
	{
	public:
		WeaponsGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
