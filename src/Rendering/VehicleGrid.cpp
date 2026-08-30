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

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	VehicleGrid::VehicleGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void VehicleGrid::Populate()
	{
		// Globals (MenuVehicle.cpp's globalsGroup) - the two unconditional
		// list items (autodrive/npcautodrive/autodrivehud) map directly
		// onto GridItemCommandToggle; modifyboostbehavior's own toggle
		// does too, but its ConditionalItem-gated boostbehavior dropdown
		// is skipped (no list widget yet), as are autodrivespeed/
		// autodrivestyle (IntCommandItem slider + ListCommandItem, both
		// gated on autodrive/npcautodrive being on).
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Globals", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "vehiclegodmode"_J, "Godmode"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "keepfixed"_J, "Keep Fixed"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "hornboost"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "modifyboostbehavior"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "autodrive"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "npcautodrive"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "autodrivehud"_J));

		// Tools (toolsGroup) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Tools", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "enterlastvehicle"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "repairvehicle"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "fixallvehicles"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "callmechanic"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "requestpv"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "despawnpv"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "savepersonalvehicle"_J));

		// Misc (miscGroup) - every item here is an unconditional
		// BoolCommandItem in the original, so all six map directly onto
		// GridItemCommandToggle.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Misc", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "speedometer"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "seatbelt"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "lowervehiclestance"_J, "Lower Stance"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "allowhatsinvehicles"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "lsccustomsbypass"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "dlcvehicles"_J));

		// Vehicle's other categories (BuildSpawnVehicleMenu()/
		// BuildVehicleEditorMenu()/BuildSavedVehiclesMenu()). Spawn now
		// has its own content Grid; the other two are still
		// placeholder-only.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Categories", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Spawn", &g_SpawnContent));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Vehicle Editor", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Saved Vehicles", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] VehicleGrid populated with {} items", m_Items.size());
	}
}
