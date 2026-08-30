#pragma once
#include "GridItem.hpp"
#include "Joaat.hpp"
#include "ListCommand.hpp"

#include <optional>
#include <string>

namespace YimMenu::Rendering
{
	// A label + current selected item + "<"/">" buttons cycling through
	// a real YimMenu::ListCommand's own option list - the Grid
	// equivalent of ListCommandItem (src/ListCommandItem.cpp) for the
	// ImGui menu, minus the dropdown/combo box: there's no popup system
	// here yet, so cycling one entry at a time with the arrow buttons is
	// the whole interaction - the same trade-off GridItemIntStepper
	// already makes in place of ImGui::InputInt's text entry.
	//
	// Laid out left-to-right in sequence (label, then value box, then
	// buttons), NOT right-anchored to the item's own edge the way
	// GridItemIntStepper's value+buttons are: an option label can be
	// much wider than an int's few digits (e.g. a business or weather
	// name), and right-anchoring a wide value box would run it back
	// underneath the label instead of leaving room for it. The
	// trade-off is that the buttons land at a different x per row
	// depending on that row's own label+value width, and - same
	// unsolved problem as everywhere else in this system - a very long
	// label plus a very long option can still overflow the panel's
	// right edge, since there's no text wrapping/truncation yet.
	class GridItemCommandList : public GridItem
	{
	public:
		GridItemCommandList(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt);

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

	private:
		struct Layout
		{
			float valueX;
			float valueWidth;
			float prevX;
			float nextX;
			float buttonSize;
		};
		Layout ComputeLayout() const;

		const std::string& Label() const;
		const char* CurrentItemText() const;
		float MaxItemWidth() const; // cached on first call - the list itself doesn't change at runtime

		ListCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
		mutable std::optional<float> m_MaxItemWidth;
	};
}
