#include "WorldIPLsGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
#include "Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = 28.f;
	}

	// Position matches every other content Grid's (168, 58) - see the
	// comment in MenuGrid.cpp's anonymous namespace for why (no shared
	// header for these yet).
	WorldIPLsGrid::WorldIPLsGrid() :
	    Grid(168.f, 58.f, 300.f)
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
