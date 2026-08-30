#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Self > Weapons: mirrors Weapons.cpp's
	// BuildWeaponsMenu() Tools, Gun Van and Aimbot groups, wired the same
	// way SelfGrid wires Self > Main.
	//
	// Deliberately NOT included (all need things this system doesn't have
	// yet, so nothing here fakes them):
	// - The whole Globals group - almost entirely ConditionalItem-gated
	//   FloatCommandItems/ListCommandItems (explosion damage/camera
	//   shake, weapon/melee damage scale, ...) - no float widget yet, and
	//   the ConditionalItem gating itself isn't supported regardless
	//   (same reasons SelfGrid's Movement group is skipped entirely).
	// - Ammu-Nation - a hand-rolled ImGui UI (weapon search/stats/list
	//   box), no Grid equivalent widgets yet.
	// - aimbotaimforhead/aimbottargetdrivers/aimbotreleasedeadped - all
	//   three are ConditionalItems gated on aimbot being on, skipped for
	//   the same reason as every other ConditionalItem in this system.
	// - RenderCustomWeaponsMenu()'s whole category - deeply nested
	//   ConditionalItems (customweapon -> customweapontype -> per-type
	//   options) plus a ColorCommandItem, none of which exist here yet.
	// All of the above stay reachable via the existing ImGui Self >
	// Weapons category, untouched.
	class WeaponsGrid : public Grid
	{
	public:
		WeaponsGrid();

	protected:
		void Populate() override;
	};
}
