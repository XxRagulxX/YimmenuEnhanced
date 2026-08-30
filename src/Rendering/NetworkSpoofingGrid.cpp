#include "NetworkSpoofingGrid.hpp"

#include "GridItemCommandToggle.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	NetworkSpoofingGrid::NetworkSpoofingGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void NetworkSpoofingGrid::Populate()
	{
		// Matchmaking (Client) (matchmakingGroup) - cheaterpool and
		// spoofdatahash are both unconditional; the spoofMMRegion
		// subgroup (spoofmmregion + a further-conditional mmregion list)
		// is entirely wrapped in a ConditionalItem gated on cheaterpool
		// being off, skipped whole.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Matchmaking (Client)", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "cheaterpool"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "spoofdatahash"_J));

		// Matchmaking (Server) (matchmakingSrvGroup) - all four toggles
		// are unconditional; their paired mmregiontype/mmlanguage/
		// mmplayercount/mmmultiplexsessioncount items are each a
		// ConditionalItem gated on the toggle right next to it.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Matchmaking (Server)", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmspoofregiontype"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmspooflanguage"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmspoofplayercount"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "mmmultiplexsession"_J));

		LOGF(INFO, "[GridRenderer] NetworkSpoofingGrid populated with {} items", m_Items.size());
	}
}
