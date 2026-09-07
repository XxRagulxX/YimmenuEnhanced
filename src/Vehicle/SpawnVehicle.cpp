#include "Vehicle/SpawnVehicle.hpp"
#include "Commands/CommandToggle.hpp"

namespace StandEnhanced::Submenus
{
	// These four commands used to also be drawn here, by the classic
	// ImGui menu builder this file no longer has (see SpawnVehicle.hpp) -
	// left registered since Rendering/VehicleSpawnNewGrid.cpp/
	// VehicleSpawnPersonalGrid.cpp still look them up by name
	// (Commands::GetCommand<CommandToggle>("spawninsideveh"_J) etc.) and
	// draw them as part of the Grid port instead.
	static CommandToggle spawnInsideVehicle{"spawninsideveh", "Spawn Inside", "Spawn inside the vehicle."};
	static CommandToggle spawnVehicleMaxed{"spawnvehmaxed", "Spawn Maxed", "Spawn the vehicle maxed."};
	static CommandToggle spawnInsidePersonalVehicle{"spawninsidepv", "Spawn Inside", "Spawn inside the personal vehicle."};
	static CommandToggle spawnClonePersonalVehicle{"spawnclonepv", "Spawn Clone", "Spawn a clone of the persone vehicle."};
}
