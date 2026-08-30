#include "WorldIPLsGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	WorldIPLsGrid::WorldIPLsGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void WorldIPLsGrid::Populate()
	{
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "iplselector"_J, "IPL"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "loadipl"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "unloadipl"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "ipltp"_J));

		LOGF(INFO, "[GridRenderer] WorldIPLsGrid populated with {} items", m_Items.size());
	}
}
