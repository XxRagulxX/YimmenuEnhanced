#include "VehicleGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"
#include "Theme.hpp"
#include "VehicleSpawnGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		VehicleSpawnGrid g_SpawnContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	VehicleGrid::VehicleGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void VehicleGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Globals (MenuVehicle.cpp's globalsGroup) - the two unconditional
		// list items (autodrive/npcautodrive/autodrivehud) map directly
		// onto GridItemCommandToggle; modifyboostbehavior's own toggle
		// does too, but its ConditionalItem-gated boostbehavior dropdown
		// is skipped (no list widget yet), as are autodrivespeed/
		// autodrivestyle (IntCommandItem slider + ListCommandItem, both
		// gated on autodrive/npcautodrive being on).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Globals", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "vehiclegodmode"_J, "Godmode"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "keepfixed"_J, "Keep Fixed"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "hornboost"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "modifyboostbehavior"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "autodrive"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "npcautodrive"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "autodrivehud"_J));

		// Tools (toolsGroup) - all plain CommandItem buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Tools", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "enterlastvehicle"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "repairvehicle"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "fixallvehicles"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "callmechanic"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "requestpv"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "despawnpv"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "savepersonalvehicle"_J));

		// Misc (miscGroup) - every item here is an unconditional
		// BoolCommandItem in the original, so all six map directly onto
		// GridItemCommandToggle.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Misc", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "speedometer"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "seatbelt"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "lowervehiclestance"_J, "Lower Stance"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "allowhatsinvehicles"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "lsccustomsbypass"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "dlcvehicles"_J));

		// Vehicle's other categories (BuildSpawnVehicleMenu()/
		// BuildVehicleEditorMenu()/BuildSavedVehiclesMenu()). Spawn now
		// has its own content Grid; the other two are still
		// placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Spawn", &g_SpawnContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Vehicle Editor", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Saved Vehicles", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] VehicleGrid populated with {} items", items_draft.size());
	}
}
