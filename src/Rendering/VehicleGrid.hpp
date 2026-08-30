#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Vehicle > Main: mirrors MenuVehicle.cpp's Globals,
	// Tools and Misc groups (all real BoolCommand/Command toggles+buttons),
	// wired the same way SelfGrid wires Self > Main.
	//
	// Deliberately NOT included (both need things this system doesn't have
	// yet, so nothing here fakes them):
	// - boostbehavior (ConditionalItem gated on modifyboostbehavior) - a
	//   ListCommandItem, and no list/dropdown widget exists yet either.
	// - autodrivespeed/autodrivestyle (ConditionalItem gated on autodrive
	//   or npcautodrive being on) - an IntCommandItem slider (different
	//   from GridItemIntStepper's buttons) and a ListCommandItem.
	// All of the above stay reachable via the existing ImGui Vehicle > Main
	// category, untouched.
	//
	// Also the Vehicle submenu's root as far as MenuGrid/MenuNavigation
	// are concerned: Populate() appends a GridItemFolder row for each of
	// Vehicle's other categories (Spawn, Vehicle Editor, Saved Vehicles)
	// after the items above - see SelfGrid.hpp's identical note.
	class VehicleGrid : public Grid
	{
	public:
		VehicleGrid();

	protected:
		void Populate() override;
	};
}
