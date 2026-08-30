#include "VehicleGrid.hpp"

#include "GridItemCommandButton.hpp"
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

	// Position matches MenuGrid.cpp's kContentX/kContentY exactly (same
	// convention as SelfGrid.cpp/MiscGrid.cpp - no shared header for these
	// yet).
	VehicleGrid::VehicleGrid() :
	    Grid(168.f, 94.f, 300.f)
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
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Globals"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "vehiclegodmode"_J, "Godmode"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "keepfixed"_J, "Keep Fixed"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "hornboost"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "modifyboostbehavior"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "autodrive"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "npcautodrive"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "autodrivehud"_J));

		// Tools (toolsGroup) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Tools"));
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
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Misc"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "speedometer"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "seatbelt"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "lowervehiclestance"_J, "Lower Stance"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "allowhatsinvehicles"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "lsccustomsbypass"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "dlcvehicles"_J));

		LOGF(INFO, "[GridRenderer] VehicleGrid populated with {} items", m_Items.size());
	}
}
