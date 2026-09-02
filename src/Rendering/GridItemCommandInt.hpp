#pragma once
#include "Rendering/GridItem.hpp"
#include "Commands/IntCommand.hpp"
#include "Util/Joaat.hpp"

#include <optional>
#include <string>

namespace YimMenu::Rendering
{
	// A label + current integer value + "-"/"+" buttons - the Grid
	// equivalent of IntCommandItem (src/IntCommandItem.cpp) for the
	// ImGui menu, minus its own text-entry fallback (ImGui::InputInt,
	// used when the command has no min/max or use_slider is false) and
	// its slider bar (ImGui::SliderInt, used otherwise): stepping by
	// `step` per click/Left-Right, clamped to whichever of min/max the
	// command actually has, is the whole interaction here - same
	// trade-off GridItemIntStepper (this project's own stepper, not
	// bound to a real command) already makes. Right-anchored to this
	// item's own edge, same as GridItemIntStepper - unlike
	// GridItemCommandList, an int's value box is always a fixed, small
	// width, so there's no risk of a wide option label running into it.
	class GridItemCommandInt : public GridItem
	{
	public:
		GridItemCommandInt(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt, int step = 1);

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

		bool isFocusable() const override
		{
			return true;
		}

		// Always returns true (handled) when a real command is behind
		// this item - see the identical doc comment on
		// GridItemCommandList::onArrow().
		bool onArrow(int delta) override;

	private:
		void Step(int direction);

		struct Layout
		{
			float valueX;
			float valueWidth;
			float minusX;
			float plusX;
			float buttonSize;
		};
		Layout ComputeLayout() const;

		const std::string& Label() const;

		IntCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
		int m_Step;
	};
}
