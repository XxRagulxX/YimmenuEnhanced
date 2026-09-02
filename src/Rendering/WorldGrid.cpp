#include "Rendering/WorldGrid.hpp"

#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemConditional.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/PlaceholderGrid.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/WorldIPLsGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		WorldIPLsGrid g_IPLsContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	WorldGrid::WorldGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void WorldGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Kill (killPeds) - both plain CommandItem buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Kill", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "killallpeds"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "killallenemies"_J));

		// Delete (deleteOpts) - all plain CommandItem buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Delete", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "delpeds"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "delvehs"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "delobjs"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "delcams"_J));

		// Bring (bringOpts) - all plain CommandItem buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Bring", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "bringpeds"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "bringvehs"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "bringobjs"_J));

		// Weather (weatherOpts) - setweather is a ConditionalItem shown
		// only while forceweather is *off* (negate), now that
		// GridItemConditional exists.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Weather", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "weather"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "setweather"_J),
		    "forceweather"_J,
		    true));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "forceweather"_J));

		// Time (timeGroup) - hour/minute/second are all unconditional
		// IntCommandItems, now that GridItemCommandInt exists; Set/Freeze
		// are a plain button and toggle.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Time", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "networktimehour"_J, "Hour"));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "networktimeminute"_J, "Minute"));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "networktimesecond"_J, "Second"));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "setnetworktime"_J, "Set"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freezenetworktime"_J, "Freeze"));

		// Other (otherOpts) - every item here is an unconditional
		// BoolCommandItem in the original, so all five map directly onto
		// GridItemCommandToggle.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Other", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "pedsignore"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "PedRiotMode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "CopsDispatch"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "enablecreatordevmode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infiniteboundary"_J));

		// World's other categories (BuildSpawnPedMenu(), the IPLs
		// Category). IPLs now has its own content Grid; Spawn Ped is
		// still placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Spawn Ped", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "IPLs", &g_IPLsContent));

		LOGF(INFO, "[GridRenderer] WorldGrid populated with {} items", items_draft.size());
	}
}
