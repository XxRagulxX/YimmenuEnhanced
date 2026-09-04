#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Root content grid for the Settings sidebar entry. This root has no
	// direct settings of its own, just a GridItemFolder row for each of
	// Settings' five categories (Hotkeys, GUI, Game, Customize, Lua
	// Scripts), same as every other root's "Categories" section.
	//
	// Hotkeys/GUI/Game/Lua Scripts each point at a real content Grid
	// (HotkeysGrid/SettingsGuiGrid/SettingsGameGrid/LuaScriptsGrid, owned
	// here since nothing else reaches them) - see their own class
	// comments for what each covers (Hotkeys' own, in particular, for
	// how it replaces the original's single hand-rolled ImGui widget and
	// its mouse-hold capture gesture). Customize still points at the
	// shared placeholder - it edits ImGuiStyle/ImGuiCol_*, meaningless
	// once the Grid renderer is primary, and needs a real redesign
	// rather than a straight port.
	class SettingsGrid : public Grid
	{
	public:
		SettingsGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
