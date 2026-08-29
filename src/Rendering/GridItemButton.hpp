#pragma once
#include "GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	// A button-styled rectangle with a centred label. Click just logs for
	// now - not yet wired to a real command (that's follow-up work once a
	// real menu page uses this instead of TestGrid).
	class GridItemButton : public GridItem
	{
	public:
		GridItemButton(float height, std::string label) :
		    GridItem(height),
		    m_Label(std::move(label))
		{
		}

		void Draw() override;
		void DrawText() override;
		void OnClick(float cursorX, float cursorY) override;

	private:
		std::string m_Label;
	};
}
