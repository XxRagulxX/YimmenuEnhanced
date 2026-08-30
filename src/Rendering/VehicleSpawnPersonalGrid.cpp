#include "VehicleSpawnPersonalGrid.hpp"

#include "BoolCommand.hpp"
#include "Commands.hpp"
#include "FiberPool.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemSelectList.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Notifications.hpp"
#include "PersonalVehicles.hpp"
#include "Pointers.hpp"
#include "Self.hpp"
#include "Theme.hpp"
#include "Vehicle.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// rows() callback - PersonalVehicles::Update() is throttled to
		// once every 10 seconds internally (see PersonalVehicles.cpp),
		// so calling it every time this runs (potentially several times
		// a frame - see GridItemSelectList's own class comment) is the
		// same cheap no-op the rest of the time the original's own
		// per-frame ImGuiItem call was.
		std::vector<std::string> PersonalVehicleRows()
		{
			if (!*Pointers.IsSessionStarted)
				return {};

			PersonalVehicles::Update();

			std::vector<std::string> rows;
			rows.reserve(PersonalVehicles::GetPersonalVehicles().size());
			for (auto& [name, veh] : PersonalVehicles::GetPersonalVehicles())
				rows.push_back(name);

			return rows;
		}

		// Looked up by name (rows()'s own value) rather than by index -
		// unlike VehicleSpawnNewGrid's g_VehicleHashes (a fixed,
		// compile-time array), PersonalVehicles::GetPersonalVehicles()
		// can change out from under an index between calls (a vehicle
		// despawned/repurchased elsewhere), so the name itself is the
		// only identifier still guaranteed to mean the same vehicle.
		void OnSelectPersonalVehicle(size_t, const std::string& value, bool, bool, bool)
		{
			auto& vehicles = PersonalVehicles::GetPersonalVehicles();
			auto it = vehicles.find(value);
			if (it == vehicles.end())
				return;

			auto& personalVeh = it->second;
			FiberPool::queueJob([&personalVeh] {
				auto* spawnClone = Commands::GetCommand<BoolCommand>("spawnclonepv"_J);
				auto* spawnInside = Commands::GetCommand<BoolCommand>("spawninsidepv"_J);

				if (spawnClone && spawnClone->GetState())
				{
					auto coords = Vehicle::GetSpawnLocRelToPed(Self::GetPed().GetHandle(), personalVeh->GetModel());
					auto heading = Self::GetPed().GetHeading();
					auto handle = personalVeh->Clone(coords, heading);

					if (spawnInside && spawnInside->GetState())
						Self::GetPed().SetInVehicle(handle);
				}
				else
				{
					if (!personalVeh->Request(spawnInside && spawnInside->GetState()))
						Notifications::Show("Spawn Personal Vehicle", "Failed to spawn Personal Vehicle.", NotificationType::Error);
				}
			});
		}
	}

	// Origin sits right below where VehicleSpawnGrid's own tab strip
	// draws - see this class's own header comment and GridTabbed's for
	// why a tab target hardcodes this itself rather than the usual
	// (1438, 587).
	VehicleSpawnPersonalGrid::VehicleSpawnPersonalGrid() :
	    Grid(1438, 622, 3)
	{
	}

	void VehicleSpawnPersonalGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Spawn (spawn Group) - the search box + result list ImGuiItem.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Spawn", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemSelectList>(Theme::kContentWidth, "Search", PersonalVehicleRows, OnSelectPersonalVehicle));

		// Settings (settings Group) - both unconditional.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Settings", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spawninsidepv"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spawnclonepv"_J));

		LOGF(INFO, "[GridRenderer] VehicleSpawnPersonalGrid populated with {} items", items_draft.size());
	}
}
