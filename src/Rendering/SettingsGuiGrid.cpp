#include "Rendering/SettingsGuiGrid.hpp"

#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemConditional.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	SettingsGuiGrid::SettingsGuiGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void SettingsGuiGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// General - unloadmenu is added directly to MenuSettings.cpp's
		// gui Category with no wrapping Group of its own.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "General", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "unloadmenu"_J));

		// UI (uiStyle) - styleselector is an unconditional ListCommandItem,
		// now that GridItemCommandList exists.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "UI", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "styleselector"_J));

		// Overlay - overlayfps/overlaypos/overlaylock are all
		// ConditionalItems gated on the toggle below being on, now that
		// GridItemConditional exists. A hidden one still reserves its own
		// row (see GridItemConditional.hpp's class comment) - toggling
		// "overlay" off leaves two blank rows here rather than the list
		// shrinking to fit.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Overlay", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "overlay"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "overlayfps"_J),
		    "overlay"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "overlaypos"_J),
		    "overlay"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "overlaylock"_J),
		    "overlay"_J));

		// Chat - clearchat is a plain CommandItem button.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Chat", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "clearchat"_J));
	}
}
