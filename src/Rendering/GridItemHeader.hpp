#pragma once
#include "GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	// A title bar: translucent dark background with a white label,
	// mirroring stand-reference's src/Menu/GridItemHeader.* role (though
	// this is a single concrete widget, not stand's abstract base class
	// with animated/loading variants). Purely decorative for now - no
	// collapse/drag behaviour yet (that needs the input pass).
	class GridItemHeader : public GridItem
	{
	public:
		GridItemHeader(float height, std::string title) :
		    GridItem(height),
		    m_Title(std::move(title))
		{
		}

		void Draw() override;
		void DrawText() override;

	private:
		std::string m_Title;
	};
}
