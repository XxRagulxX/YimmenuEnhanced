#pragma once
#include "Rendering/GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	// A label + current integer value + "-"/"+" buttons - the Grid
	// equivalent of ImGui::InputInt's default stepper buttons (used by
	// e.g. Misc.cpp's interiorIndex/Team fields), minus direct keyboard
	// text entry, which needs its own separate input system this project
	// doesn't have yet. Value is clamped to [min, max], stepping by 1 per
	// click.
	class GridItemIntStepper : public GridItem
	{
	public:
		GridItemIntStepper(int16_t width, int16_t height, std::string label, int initialValue, int min, int max) :
		    GridItem(GRIDITEM_INDIFFERENT, width, height),
		    m_Label(std::move(label)),
		    m_Value(initialValue),
		    m_Min(min),
		    m_Max(max)
		{
		}

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

		bool isFocusable() const override
		{
			return true;
		}

		// Left(-1)/Right(+1) steps the value directly, clamped to
		// [min, max] same as the +/- buttons - see the identical doc
		// comment on GridItemCommandList::onArrow(). Always returns
		// true (handled).
		bool onArrow(int delta) override;

		int GetValue() const
		{
			return m_Value;
		}

	private:
		struct Layout
		{
			float valueX;
			float valueWidth;
			float minusX;
			float plusX;
			float buttonSize;
		};
		Layout ComputeLayout() const;

		std::string m_Label;
		int m_Value;
		int m_Min;
		int m_Max;
	};
}
