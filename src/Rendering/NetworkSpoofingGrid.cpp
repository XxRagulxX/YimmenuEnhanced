#include "NetworkSpoofingGrid.hpp"

#include "BoolCommand.hpp"
#include "Commands.hpp"
#include "GridItemCommandInt.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemConditional.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// mmregion's own condition is spoofmmregion being on AND
		// spoofmmregion's own row being visible in the first place
		// (cheaterpool being off) - two BoolCommands, not one, so this
		// needs GridItemConditional's std::function<bool()> overload
		// rather than its plain joaat_t one.
		bool ShouldShowMmRegion()
		{
			auto* cheaterpool = Commands::GetCommand<BoolCommand>("cheaterpool"_J);
			auto* spoofmmregion = Commands::GetCommand<BoolCommand>("spoofmmregion"_J);
			return (!cheaterpool || !cheaterpool->GetState()) && spoofmmregion && spoofmmregion->GetState();
		}
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	NetworkSpoofingGrid::NetworkSpoofingGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void NetworkSpoofingGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Matchmaking (Client) (matchmakingGroup) - cheaterpool and
		// spoofdatahash are unconditional. The spoofMMRegion subgroup
		// (spoofmmregion + its own further-conditional mmregion list) is
		// wrapped in a ConditionalItem gated on cheaterpool being *off*
		// (negate) in the original - spoofmmregion below carries that
		// same condition directly (there's no single GridItem standing in
		// for "the subgroup" here to wrap once, unlike ConditionalItem's
		// own model - see GridItemConditional.hpp's class comment on why
		// a hidden row still reserves its own space either way), and
		// mmregion's own condition composes both checks via
		// ShouldShowMmRegion() above.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Matchmaking (Client)", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "cheaterpool"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spoofmmregion"_J, "Spoof Region"),
		    "cheaterpool"_J,
		    true));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "mmregion"_J),
		    &ShouldShowMmRegion));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spoofdatahash"_J));

		// Matchmaking (Server) (matchmakingSrvGroup) - all four toggles
		// are unconditional; their paired mmregiontype/mmlanguage/
		// mmplayercount/mmmultiplexsessioncount items are each a
		// ConditionalItem gated on the toggle right next to it, now that
		// GridItemConditional exists (mmplayercount/mmmultiplexsessioncount
		// also needed GridItemCommandInt, which exists now too).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Matchmaking (Server)", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmspoofregiontype"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "mmregiontype"_J),
		    "mmspoofregiontype"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmspooflanguage"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "mmlanguage"_J),
		    "mmspooflanguage"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmspoofplayercount"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "mmplayercount"_J),
		    "mmspoofplayercount"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mmmultiplexsession"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "mmmultiplexsessioncount"_J),
		    "mmmultiplexsession"_J));

		LOGF(INFO, "[GridRenderer] NetworkSpoofingGrid populated with {} items", items_draft.size());
	}
}
