#include "PlaceholderGrid.hpp"

#include "GridItemText.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	PlaceholderGrid::PlaceholderGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void PlaceholderGrid::Populate()
	{
		m_Items.push_back(std::make_unique<GridItemText>(20.f, "Not yet migrated.", Theme::kPlaceholderText));
	}

	Grid& GetPlaceholderGrid()
	{
		static PlaceholderGrid instance{};
		return instance;
	}
}
