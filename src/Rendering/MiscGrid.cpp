#include "MiscGrid.hpp"

#include "FiberPool.hpp"
#include "GridItemButton.hpp"
#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemHeader.hpp"
#include "GridItemTabsHorizontal.hpp"
#include "Joaat.hpp"
#include "Natives.hpp"

namespace YimMenu::Rendering
{
	MiscGrid::MiscGrid() :
	    Grid(20.f, 20.f, 260.f)
	{
	}

	void MiscGrid::Populate()
	{
		m_Items.push_back(std::make_unique<GridItemHeader>(30.f, "YimMenu (Stand-style)"));
		m_Items.push_back(std::make_unique<GridItemTabsHorizontal>(
		    28.f,
		    std::vector<std::string>{"Misc", "Globals", "Locals", "Scripts"},
		    0));

		// "Network Bail" isn't a registered Command in src/Misc.cpp (it's
		// an inline ImGui button + FiberPool job) - reused verbatim as a
		// GridItemButton action callback rather than wrapping it in a
		// Command just for this.
		m_Items.push_back(std::make_unique<GridItemButton>(28.f, "Network Bail", [] {
			FiberPool::queueJob([] {
				NETWORK::NETWORK_BAIL(0, 24, 0);
			});
		}));

		m_Items.push_back(std::make_unique<GridItemCommandButton>(28.f, "dumpdatahash"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(26.f, "standrenderertest"_J));

		LOGF(INFO, "[GridRenderer] MiscGrid populated with {} items", m_Items.size());
	}
}
