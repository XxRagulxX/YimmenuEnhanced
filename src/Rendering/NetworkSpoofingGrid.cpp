#include "NetworkSpoofingGrid.hpp"

#include "GridItemCommandToggle.hpp"
#include "GridItemHeader.hpp"
#include "Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = 26.f;
		constexpr float kItemH = 28.f;
	}

	// Position matches every other content Grid's (168, 58) - see the
	// comment in MenuGrid.cpp's anonymous namespace for why (no shared
	// header for these yet).
	NetworkSpoofingGrid::NetworkSpoofingGrid() :
	    Grid(168.f, 58.f, 300.f)
	{
	}

	void NetworkSpoofingGrid::Populate()
	{
		// Matchmaking (Client) (matchmakingGroup) - cheaterpool and
		// spoofdatahash are both unconditional; the spoofMMRegion
		// subgroup (spoofmmregion + a further-conditional mmregion list)
		// is entirely wrapped in a ConditionalItem gated on cheaterpool
		// being off, skipped whole.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Matchmaking (Client)"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "cheaterpool"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spoofdatahash"_J));

		// Matchmaking (Server) (matchmakingSrvGroup) - all four toggles
		// are unconditional; their paired mmregiontype/mmlanguage/
		// mmplayercount/mmmultiplexsessioncount items are each a
		// ConditionalItem gated on the toggle right next to it.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Matchmaking (Server)"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmspoofregiontype"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmspooflanguage"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmspoofplayercount"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmmultiplexsession"_J));

		LOGF(INFO, "[GridRenderer] NetworkSpoofingGrid populated with {} items", m_Items.size());
	}
}
