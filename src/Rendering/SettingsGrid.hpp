#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Root content grid for the Settings sidebar entry. Unlike Self/
	// Vehicle/.../Debug, Settings' own first category (Hotkeys) is a
	// single hand-rolled ImGui widget (a live-rebindable command list
	// with its own "hold this button and press a key" capture flow) with
	// nothing that maps onto a GridItem at all - so this root has no
	// direct settings of its own, just a GridItemFolder row for each of
	// Settings' five categories (Hotkeys, GUI, Game, Customize, Lua
	// Scripts), same as every other root's "Categories" section.
	//
	// GUI's folder points at a real content Grid (SettingsGuiGrid, owned
	// here since nothing else reaches it) - see SettingsGuiGrid.hpp for
	// what it covers. The other four still point at the shared
	// placeholder: Hotkeys for the reason above, Game for being almost
	// entirely ConditionalItem-gated ESP toggles plus ColorCommandItems
	// (no colour widget exists here at all), Customize/Lua Scripts for
	// not having been looked at yet.
	class SettingsGrid : public Grid
	{
	public:
		SettingsGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
