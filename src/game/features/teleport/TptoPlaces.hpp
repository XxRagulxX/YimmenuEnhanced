#pragma once

#include "types/rage/vector.hpp"

#include <string>
#include <vector>

namespace YimMenu::Features
{
	struct TeleportPlace
	{
		std::string name;
		rage::fvector3 position;
		float heading;
	};

	using SubPlaceMap = std::map<std::string, std::vector<TeleportPlace>>; // e.g., Storage -> [north, south, west]
	using CategoryMap = std::map<std::string, SubPlaceMap>;                // e.g., CayoPerico -> Storage -> ...

	CategoryMap GetAllTeleportLocations();

	void RenderPredefinedPlacesTeleport();
}