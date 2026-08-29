#pragma once
#include "GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	// A label with an on/off indicator, mirroring how Stand's own list
	// items show bool-command state inline. Clicking flips its own local
	// state - not yet wired to a real BoolCommand (that's follow-up work
	// once a real menu page uses this instead of TestGrid).
	class GridItemToggle : public GridItem
	{
	public:
		GridItemToggle(float height, std::string label, bool state) :
		    GridItem(height),
		    m_Label(std::move(label)),
		    m_State(state)
		{
		}

		void Draw() override;
		void DrawText() override;
		void OnClick(float cursorX, float cursorY) override;

	private:
		std::string m_Label;
		bool m_State;
	};
}
