#pragma once

#include "types/rage/vector.hpp"

#include <chrono>
#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

namespace YimMenu::Features
{
	struct TeleportPlace
	{
		std::string name;
		rage::fvector3 position;
		float heading;

		// Optional metadata for enhanced functionality
		bool requiresInterior = false; // Some locations only work when inside properties
		bool isGroundLevel    = true;  // Whether to apply ground detection
		std::string description;       // For tooltips and help text

		// Default constructor
		TeleportPlace() = default;

		// Constructor with basic parameters (maintains compatibility)
		TeleportPlace(const std::string& n, const rage::fvector3& pos, float h) :
		    name(n),
		    position(pos),
		    heading(h)
		{
		}

		// Enhanced constructor with metadata
		TeleportPlace(const std::string& n, const rage::fvector3& pos, float h, bool interior, bool ground, const std::string& desc = "") :
		    name(n),
		    position(pos),
		    heading(h),
		    requiresInterior(interior),
		    isGroundLevel(ground),
		    description(desc)
		{
		}
	};

	using SubPlaceMap = std::map<std::string, std::vector<TeleportPlace>>;
	using CategoryMap = std::map<std::string, SubPlaceMap>;

	// Core functionality
	CategoryMap GetAllTeleportLocations();
	void RenderPredefinedPlacesTeleport();

	// Enhanced helper functions (exposed for external use)
	namespace TeleportHelpers
	{
		// Safe teleportation with validation
		void TeleportEntityTo(const TeleportPlace& place);

		// Property detection functions
		std::optional<TeleportPlace> GetYourArcade();
		std::optional<TeleportPlace> GetYourFacility();
		std::optional<TeleportPlace> GetYourKosatka();
		std::optional<TeleportPlace> GetPropertyByBlip(int blipId, const char* propertyName, bool useCache = true);

		// Utility functions
		TeleportPlace MakePlace(const char* name, float x, float y, float z, float heading);
		void ClearPropertyCache();

		// Validation functions
		bool IsValidCoordinate(const rage::fvector3& position);
		bool IsPlayerInInterior();

		// Enhanced property rendering
		void RenderPropertyTeleportOptions(const std::string& propertyType, const std::vector<TeleportPlace>& interiorLocations);
	}

	// Configuration constants
	namespace TeleportConfig
	{
		constexpr float WORLD_MIN_X   = -4000.0f;
		constexpr float WORLD_MAX_X   = 4000.0f;
		constexpr float WORLD_MIN_Y   = -4000.0f;
		constexpr float WORLD_MAX_Y   = 4000.0f;
		constexpr float WORLD_MIN_Z   = -200.0f;
		constexpr float WORLD_MAX_Z   = 2000.0f;
		constexpr auto CACHE_DURATION = std::chrono::minutes(5);
		constexpr float GROUND_OFFSET = 1.0f;
	}
}
