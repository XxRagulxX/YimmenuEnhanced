#pragma once
#include "GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	// A button-styled rectangle with a centred label. Purely visual for
	// now - no click handling yet (needs the input/hit-testing pass).
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

	private:
		std::string m_Label;
	};
}
