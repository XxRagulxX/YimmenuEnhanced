#include "Rendering/VehicleGrid.hpp"

#include "Commands/BoolCommand.hpp"
#include "Commands/Commands.hpp"
#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemConditional.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/PlaceholderGrid.hpp"
#include "Rendering/SavedVehiclesGrid.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/VehicleSpawnGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		VehicleSpawnGrid g_SpawnContent{};
		SavedVehiclesGrid g_SavedVehiclesContent{};

		// autodrivespeed/autodrivestyle's own MenuVehicle.cpp gate reads
		// two BoolCommands (autodrive OR npcautodrive), so - same as
		// SelfGrid.cpp's ShouldClearOrSetWanted() - this needs
		// GridItemConditional's std::function<bool()> overload rather
		// than its plain joaat_t one.
		bool IsAutoDriveEnabled()
		{
			auto* playerAutoDrive = Commands::GetCommand<BoolCommand>("autodrive"_J);
			auto* npcAutoDrive = Commands::GetCommand<BoolCommand>("npcautodrive"_J);
			return (playerAutoDrive && playerAutoDrive->GetState()) || (npcAutoDrive && npcAutoDrive->GetState());
		}
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
		// Globals (MenuVehicle.cpp's globalsGroup) - boostbehavior is
		// gated on modifyboostbehavior directly (GridItemConditional's
		// plain joaat_t overload); autodrivespeed/autodrivestyle are
		// gated on IsAutoDriveEnabled() above (its combined
		// autodrive-OR-npcautodrive condition needs the
		// std::function<bool()> overload instead).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Globals", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "vehiclegodmode"_J, "Godmode"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "keepfixed"_J, "Keep Fixed"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "hornboost"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "modifyboostbehavior"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "boostbehavior"_J),
		    "modifyboostbehavior"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "autodrive"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "npcautodrive"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "autodrivehud"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "autodrivespeed"_J),
		    IsAutoDriveEnabled));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "autodrivestyle"_J),
		    IsAutoDriveEnabled));

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
		// BuildVehicleEditorMenu()/BuildSavedVehiclesMenu()). Spawn/Saved
		// Vehicles now have their own content Grids; Vehicle Editor is
		// still placeholder-only (bespoke Phase 4 work).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Spawn", &g_SpawnContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Vehicle Editor", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Saved Vehicles", &g_SavedVehiclesContent));

		LOGF(INFO, "[GridRenderer] VehicleGrid populated with {} items", items_draft.size());
	}
}
