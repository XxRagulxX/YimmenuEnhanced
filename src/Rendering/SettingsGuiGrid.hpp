#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Settings > GUI: mirrors MenuSettings.cpp's gui
	// Category - unloadmenu and clearchat (plain CommandItem buttons),
	// uiStyle's styleselector (a ListCommandItem, now that
	// GridItemCommandList exists), and overlay's own unconditional
	// toggle.
	//
	// Deliberately NOT included:
	// - overlayfps/overlaypos/overlaylock - all three are ConditionalItems
	//   gated on overlay being on, skipped for the same reason as every
	//   other ConditionalItem in this system.
	// Stays reachable via the existing ImGui Settings > GUI category,
	// untouched.
	class SettingsGuiGrid : public Grid
	{
	public:
		SettingsGuiGrid();

	protected:
		void Populate() override;
	};
}
