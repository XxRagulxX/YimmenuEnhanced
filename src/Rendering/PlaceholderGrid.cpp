#include "PlaceholderGrid.hpp"

#include "GridItemText.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr DirectX::XMFLOAT4 kPlaceholderColour{0.7f, 0.7f, 0.7f, 1.f};
	}

	// Position matches MenuGrid.cpp's kContentX/kContentY exactly (same
	// convention as every other content Grid - no shared header for
	// these yet).
	PlaceholderGrid::PlaceholderGrid() :
	    Grid(168.f, 94.f, 300.f)
	{
	}

	void PlaceholderGrid::Populate()
	{
		m_Items.push_back(std::make_unique<GridItemText>(20.f, "Not yet migrated.", kPlaceholderColour));
	}

	Grid& GetPlaceholderGrid()
	{
		static PlaceholderGrid instance{};
		return instance;
	}
}
