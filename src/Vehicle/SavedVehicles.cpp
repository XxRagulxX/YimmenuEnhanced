#include "Vehicle/SavedVehicles.hpp"
#include "Commands/BoolCommand.hpp"

namespace YimMenu::Submenus
{
	// Used to also be drawn here, by the classic ImGui menu builder this
	// file no longer has (see SavedVehicles.hpp) - left registered since
	// Rendering/SavedVehiclesGrid.cpp still looks it up by name
	// (Commands::GetCommand<BoolCommand>("spawninsidesavedveh"_J)) and
	// draws it as part of the Grid port instead.
	static BoolCommand spawnInsideSavedVehicle{"spawninsidesavedveh", "Spawn Inside", "Spawn inside the vehicle."};
}
