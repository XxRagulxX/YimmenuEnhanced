#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Self > Weapons: mirrors Weapons.cpp's
	// BuildWeaponsMenu() Tools group (all unconditional CommandItem
	// buttons) plus the Aimbot group's one unconditional BoolCommandItem,
	// wired the same way SelfGrid wires Self > Main.
	//
	// Deliberately NOT included (all need things this system doesn't have
	// yet, so nothing here fakes them):
	// - The whole Globals group - almost entirely ConditionalItem-gated
	//   FloatCommandItems/ListCommandItems (explosion damage/camera
	//   shake, weapon/melee damage scale, ...) - no float or list widget
	//   yet, same reasons SelfGrid's Movement group is skipped entirely.
	// - Ammu-Nation - a hand-rolled ImGui UI (weapon search/stats/list
	//   box), no Grid equivalent widgets yet.
	// - Gun Van - built around two ListCommandItems (weapon/slot
	//   selectors), no list/dropdown widget yet.
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
