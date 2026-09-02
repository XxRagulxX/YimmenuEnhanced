#include "Rendering/PlaceholderGrid.hpp"

#include "Rendering/GridItemText.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	PlaceholderGrid::PlaceholderGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void PlaceholderGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, 20.f, "Not yet migrated.", Theme::kPlaceholderText));
	}

	Grid& GetPlaceholderGrid()
	{
		static PlaceholderGrid instance{};
		return instance;
	}
}
