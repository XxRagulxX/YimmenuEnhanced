#pragma once
#include "Commands/FloatCommand.hpp"
#include "Rendering/GridItem.hpp"
#include "Util/Joaat.hpp"

#include <optional>
#include <string>

namespace YimMenu::Rendering
{
	// A label + current float value (shown to 2 decimal places) + "-"/
	// "+" buttons - the Grid equivalent of FloatCommandItem (src/
	// FloatCommandItem.cpp) for the ImGui menu. See the identical class
	// comment on GridItemCommandInt for every trade-off here (no text
	// entry, no slider bar - stepping by `step` is the whole
	// interaction) and why it's laid out the same way (right-anchored
	// value + buttons).
	class GridItemCommandFloat : public GridItem
	{
	public:
		GridItemCommandFloat(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt, float step = 0.1f);

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

		bool isFocusable() const override
		{
			return true;
		}

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

		FloatCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
		float m_Step;
	};
}
