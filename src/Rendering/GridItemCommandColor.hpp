#pragma once
#include "GridItem.hpp"
#include "Joaat.hpp"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	// Pushes a coloured swatch preview row followed by four R/G/B/A
	// channel stepper rows (0-255 each) into items_draft, all bound to
	// the same real YimMenu::ColorCommand, looked up by joaat hash - the
	// Grid equivalent of ColorCommandItem (src/ColorCommandItem.cpp) for
	// the ImGui menu, minus its own ImGui::ColorPicker4 popup (a
	// continuous 2D/gradient picker): this project's rendering is solid
	// rects only (no gradient/shader support), so four discrete
	// per-channel steppers stand in for it instead - same "no popup,
	// step through it instead" trade-off GridItemCommandList/
	// GridItemCommandInt already make.
	//
	// A free function pushing five separate GridItem rows, not one
	// GridItem, on purpose: every row in this system is its own
	// keyboard-focusable/clickable GridItem (see GridItem.hpp's class
	// comment) - one mega-widget covering all four channels would need
	// its own separate "which of my four rows is focused" concept
	// nothing else here has, whereas four ordinary GridItemCommandInt-
	// shaped rows plumb straight into MenuFocus/Grid::getFocusableItems()
	// like everything else already does.
	void AddColorCommandRows(std::vector<std::unique_ptr<GridItem>>& items_draft, int16_t width, joaat_t id, std::optional<std::string> labelOverride = std::nullopt);
}
