#pragma once
#include "GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	// A label with an on/off indicator, mirroring how Stand's own list
	// items show bool-command state inline. Purely visual for now: state
	// is fixed at construction, not yet togglable (needs input/hit-testing
	// and BoolCommand wiring).
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

	private:
		std::string m_Label;
		bool m_State;
	};
}
