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

	// Origin (135, 47) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	NetworkSpoofingGrid::NetworkSpoofingGrid() :
	    Grid(135, 47, 3)
	{
	}

	void NetworkSpoofingGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Matchmaking (Client) (matchmakingGroup) - cheaterpool and
		// spoofdatahash are both unconditional; the spoofMMRegion
		// subgroup (spoofmmregion + a further-conditional mmregion list)
		// is entirely wrapped in a ConditionalItem gated on cheaterpool
		// being off, skipped whole.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Matchmaking (Client)", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "cheaterpool"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spoofdatahash"_J));

		// Matchmaking (Server) (matchmakingSrvGroup) - all four toggles
		// are unconditional; their paired mmregiontype/mmlanguage/
		// mmplayercount/mmmultiplexsessioncount items are each a
		// ConditionalItem gated on the toggle right next to it.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Matchmaking (Server)", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmspoofregiontype"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmspooflanguage"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmspoofplayercount"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmmultiplexsession"_J));

		LOGF(INFO, "[GridRenderer] NetworkSpoofingGrid populated with {} items", items_draft.size());
	}
}
