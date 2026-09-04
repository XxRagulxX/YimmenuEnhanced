#pragma once
#include "Rendering/GridItem.hpp"
#include "Util/Joaat.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	class Grid;

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

	// AddColorCommandRows() above with no gating parameter of its own -
	// unlike a single-GridItem widget, there's nothing to hand a
	// condition directly. Registers condition with grid.watchCondition()
	// (see its own doc comment in Grid.hpp) and only builds/pushes the
	// five rows when it's true, rather than always building them and
	// wrapping each in GridItemConditional - so hidden rows don't reserve
	// any layout space, and the caller's own Grid (not this free
	// function) is what needs repopulating live when condition changes.
	// Needed wherever a ColorCommand swatch is itself behind a
	// ConditionalItem in the original ImGui menu (Weapons > Custom
	// Weapons' paintguncolor, Settings > Game's ESP name/skeleton/hash
	// colour swatches, ...).
	void AddConditionalColorCommandRows(Grid& grid,
	    std::vector<std::unique_ptr<GridItem>>& items_draft,
	    int16_t width,
	    joaat_t id,
	    std::function<bool()> condition,
	    std::optional<std::string> labelOverride = std::nullopt);
}
