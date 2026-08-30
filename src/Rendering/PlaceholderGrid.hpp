#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// A single "Not yet migrated." text item - stands in for any category
	// that doesn't have a real content Grid yet. One shared instance
	// (GetPlaceholderGrid() below) rather than a new one per unported
	// category: every unported destination looks identical, so there's
	// nothing category-specific for a dedicated instance to hold.
	class PlaceholderGrid : public Grid
	{
	public:
		PlaceholderGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};

	// Meyer's singleton (function-local static) rather than a file-scope
	// global, so this works regardless of static-initialization order
	// across the many content Grid .cpp files that reference it.
	Grid& GetPlaceholderGrid();
}
