#include "TptoPlaces.hpp"

#include "core/backend/FiberPool.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

#include <format>
#include <imgui.h>
#include <mutex>
#include <unordered_map>

namespace YimMenu::Features
{
	// Helper functions namespace
	namespace TeleportHelpers
	{
		// Thread-safe caching for performance
		static std::unordered_map<std::string, TeleportPlace> propertyCache;
		static std::mutex cacheMutex;
		static std::chrono::steady_clock::time_point lastCacheUpdate;
		static constexpr auto CACHE_DURATION = std::chrono::minutes(5);

		TeleportPlace MakePlace(const char* name, float x, float y, float z, float heading)
		{
			return {std::string(name), {x, y, z}, heading};
		}

		// Enhanced teleport with safety checks and ground detection
		void TeleportEntityTo(const TeleportPlace& place)
		{
			// Validate coordinates are within game world bounds
			if (place.position.x < -4000.0f || place.position.x > 4000.0f || place.position.y < -4000.0f
			    || place.position.y > 4000.0f || place.position.z < -200.0f || place.position.z > 2000.0f)
			{
				Notifications::Show("Teleport", "Invalid coordinates detected", NotificationType::Warning, 3000);
				return;
			}

			Entity entity = Self::GetPed();
			if (auto vehicle = Self::GetVehicle())
				entity = vehicle;

			if (!entity.IsValid())
			{
				Notifications::Show("Teleport", "Invalid entity", NotificationType::Error, 3000);
				return;
			}

			// Store original position for potential rollback
			auto originalPos     = entity.GetPosition();
			auto originalHeading = entity.GetHeading();

			try
			{
				// Enhanced positioning with ground detection for outdoor locations
				Vector3 targetPos = {place.position.x, place.position.y, place.position.z};

				// For outdoor locations, get proper ground height
				if (place.position.z < 100.0f) // Likely ground level
				{
					float groundZ;
					if (MISC::GET_GROUND_Z_FOR_3D_COORD(place.position.x, place.position.y, place.position.z + 50.0f, &groundZ, FALSE, FALSE))
					{
						targetPos.z = groundZ + 1.0f; // Slightly above ground
					}
				}

				// Smooth teleportation
				entity.SetPosition(targetPos);
				entity.SetHeading(place.heading);

				// Ensure entity is properly loaded at new location
				STREAMING::REQUEST_COLLISION_AT_COORD(targetPos.x, targetPos.y, targetPos.z);

				// Brief pause to ensure proper loading
				Sleep(100);

				Notifications::Show("Teleport", std::format("Teleported to {}", place.name), NotificationType::Success, 3000);
			}
			catch (...)
			{
				// Rollback on failure
				entity.SetPosition(originalPos);
				entity.SetHeading(originalHeading);
				Notifications::Show("Teleport", "Teleport failed, position restored", NotificationType::Error, 3000);
			}
		}

		// Enhanced property detection with caching
		std::optional<TeleportPlace> GetPropertyByBlip(int blipId, const char* propertyName, bool useCache)
		{
			std::string cacheKey = std::format("{}_{}", blipId, propertyName);

			// Check cache first
			if (useCache)
			{
				std::lock_guard<std::mutex> lock(cacheMutex);
				auto now = std::chrono::steady_clock::now();

				if (now - lastCacheUpdate < CACHE_DURATION)
				{
					auto it = propertyCache.find(cacheKey);
					if (it != propertyCache.end())
						return it->second;
				}
			}

			// Skip if player is in interior (more reliable check)
			if (INTERIOR::IS_VALID_INTERIOR(INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::PLAYER_PED_ID())))
				return std::nullopt;

			int propertyBlip = HUD::GET_FIRST_BLIP_INFO_ID(blipId);
			if (!HUD::DOES_BLIP_EXIST(propertyBlip))
				return std::nullopt;

			Vector3 pos = HUD::GET_BLIP_COORDS(propertyBlip);
			TeleportPlace place{propertyName, rage::fvector3{pos.x, pos.y, pos.z}, 0.0f};

			// Cache the result
			if (useCache)
			{
				std::lock_guard<std::mutex> lock(cacheMutex);
				propertyCache[cacheKey] = place;
				lastCacheUpdate         = std::chrono::steady_clock::now();
			}

			return place;
		}

		// Enhanced arcade detection with better error handling
		std::optional<TeleportPlace> GetYourArcade()
		{
			auto arcade = GetPropertyByBlip(740, "Your Arcade");
			if (!arcade)
				return std::nullopt;

			Vector3 pos      = {arcade->position.x, arcade->position.y, arcade->position.z};
			const char* zone = ZONE::GET_NAME_OF_ZONE(pos.x, pos.y, pos.z);

			if (!zone)
				return arcade; // Return basic arcade if zone detection fails

			std::string label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(zone);

			struct ArcadeData
			{
				const char* labelKey;
				Vector3 pos;
				float heading;
			};

			static const ArcadeData arcades[] = {{"MP_ARC_1", {-245.9931f, 6210.773f, 31.939024f}, -50.0f}, {"MP_ARC_2", {1695.5393f, 4784.196f, 41.94444f}, -95.0f}, {"MP_ARC_3", {-115.45246f, -1772.0801f, 29.858917f}, -125.0f}, {"FMC_LOC_WSTVNWD", {-600.911f, 279.97433f, 82.041245f}, 80.0f}, {"MP_ARC_5", {-1269.7747f, -304.4372f, 37.001965f}, 75.0f}, {"MP_ARC_6", {758.91815f, -814.60864f, 26.301702f}, 90.0f}};

			for (const auto& arcadeData : arcades)
			{
				std::string arcadeLabel = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(arcadeData.labelKey);
				if (!arcadeLabel.empty() && label.find(arcadeLabel) != std::string::npos)
				{
					arcade->position = rage::fvector3{arcadeData.pos.x, arcadeData.pos.y, arcadeData.pos.z};
					arcade->heading  = arcadeData.heading;
					return arcade;
				}
			}

			return arcade;
		}

		// Enhanced Kosatka detection
		std::optional<TeleportPlace> GetYourKosatka()
		{
			auto kosatka = GetPropertyByBlip(760, "Your Kosatka");
			if (kosatka)
			{
				kosatka->heading = 175.0f;
				// Adjust Z coordinate to be on the submarine deck
				kosatka->position.z = std::max(kosatka->position.z, -5.0f);
			}
			return kosatka;
		}

		// Enhanced facility detection
		std::optional<TeleportPlace> GetYourFacility()
		{
			return GetPropertyByBlip(590, "Your Facility");
		}

		// Enhanced property teleport rendering with better UX
		void RenderPropertyTeleportOptions(const std::string& propertyType, const std::vector<TeleportPlace>& interiorLocations)
		{
			bool hasProperty = false;

			// Check if property exists before showing options
			if (propertyType == "Arcade")
				hasProperty = GetYourArcade().has_value();
			else if (propertyType == "Facility")
				hasProperty = GetYourFacility().has_value();
			else if (propertyType == "Kosatka")
				hasProperty = GetYourKosatka().has_value();

			if (!hasProperty)
			{
				ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "No %s detected", propertyType.c_str());
				ImGui::TextWrapped("Make sure you own a %s and are not in an interior.", propertyType.c_str());
				return;
			}

			// Entrance teleport
			if (ImGui::Button(("Teleport to " + propertyType + " Entrance").c_str(), ImVec2(-1, 0)))
			{
				FiberPool::Push([propertyType] {
					std::optional<TeleportPlace> property;
					if (propertyType == "Arcade")
						property = GetYourArcade();
					else if (propertyType == "Facility")
						property = GetYourFacility();
					else if (propertyType == "Kosatka")
						property = GetYourKosatka();

					if (property.has_value())
						TeleportEntityTo(*property);
					else
						Notifications::Show(propertyType + " Teleport", "Could not detect your " + propertyType, NotificationType::Warning, 3000);
				});
			}

			// Interior locations
			if (!interiorLocations.empty())
			{
				ImGui::Separator();
				ImGui::Text("Interior Locations:");

				for (const auto& location : interiorLocations)
				{
					if (ImGui::Selectable(location.name.c_str()))
					{
						FiberPool::Push([location] {
							if (INTERIOR::IS_VALID_INTERIOR(INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::PLAYER_PED_ID())))
								TeleportEntityTo(location);
							else
								Notifications::Show("Teleport", "You must be inside your property to use this", NotificationType::Warning, 3000);
						});
					}

					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text("Coords: %.2f, %.2f, %.2f",
						    location.position.x,
						    location.position.y,
						    location.position.z);
						ImGui::EndTooltip();
					}
				}
			}
		}

		// Cache management
		void ClearPropertyCache()
		{
			std::lock_guard<std::mutex> lock(cacheMutex);
			propertyCache.clear();
		}
	}

	// Lazy-loaded location data for better performance
	CategoryMap GetAllTeleportLocations()
	{
		static CategoryMap cachedLocations;
		static bool initialized = false;

		if (!initialized)
		{
			cachedLocations = {
			    {"Cayo Perico",
			        {
			            {"Misc",
			                {
			                    TeleportHelpers::MakePlace("El Rubio's Office", 5010.12f, -5750.135f, 28.84334f, 325.0f),
			                    TeleportHelpers::MakePlace("Front Gate Exit", 4990.039f, -5717.690f, 19.880217f, 50.0f),
			                    TeleportHelpers::MakePlace("Radio Tower", 5263.7124f, -5407.5835f, 65.24931f, 0.0f),
			                    TeleportHelpers::MakePlace("Drainage Pipe", 5044.001f, -5815.6426f, -11.808871f, 0.0f),
			                    TeleportHelpers::MakePlace("Drainage: 2nd Checkpoint", 5053.773f, -5773.2266f, -5.40778f, 0.0f),
			                    TeleportHelpers::MakePlace("Ocean (Safe Zone)", 4771.479f, -6165.737f, -39.079613f, 0.0f),
			                }},
			            {"Storage",
			                {
			                    TeleportHelpers::MakePlace("North", 5081.0415f, -5755.32f, 15.829645f, -45.0f),
			                    TeleportHelpers::MakePlace("West", 5006.722f, -5786.597f, 17.831688f, 35.0f),
			                    TeleportHelpers::MakePlace("South", 5027.603f, -5734.682f, 17.255005f, -50.0f),
			                }},
			            {"Vault",
			                {
			                    TeleportHelpers::MakePlace("Primary Target", 5006.7f, -5756.2f, 14.8f, 145.0f),
			                    TeleportHelpers::MakePlace("Secondary Target", 4999.764f, -5749.864f, 14.84f, 0.0f),
			                }},
			            {"Airstrip",
			                {
			                    TeleportHelpers::MakePlace("Loot - #1", 4503.587402f, -4555.740723f, 2.854459f, 0.0f),
			                    TeleportHelpers::MakePlace("Loot - #2", 4437.821777f, -4447.841309f, 3.028436f, 0.0f),
			                    TeleportHelpers::MakePlace("Loot - #3", 4447.091797f, -4442.184082f, 5.936794f, 0.0f),
			                }},
			            {"Crop Fields",
			                {
			                    TeleportHelpers::MakePlace("Loot - #1", 5330.527f, -5269.7515f, 33.18603f, 0.0f),
			                }},
			            {"Main Dock",
			                {
			                    TeleportHelpers::MakePlace("Loot - #1", 5193.909668f, -5135.642578f, 2.045917f, 0.0f),
			                    TeleportHelpers::MakePlace("Loot - #2", 4963.184570f, -5108.933105f, 1.670808f, 0.0f),
			                    TeleportHelpers::MakePlace("Loot - #3", 4998.709473f, -5165.559570f, 1.464137f, 0.0f),
			                    TeleportHelpers::MakePlace("Loot - #4", 4924.693359f, -5243.244629f, 1.223599f, 0.0f),
			                }},
			            {"North Dock",
			                {
			                    TeleportHelpers::MakePlace("Loot - #1", 5132.558594f, -4612.922852f, 1.162808f, 0.0f),
			                    TeleportHelpers::MakePlace("Loot - #2", 5065.255371f, -4591.706543f, 1.555012f, 0.0f),
			                    TeleportHelpers::MakePlace("Loot - #3", 5090.916016f, -4682.670898f, 1.107098f, 0.0f),
			                }},
			        }},
			    {"Casino Heist",
			        {{"Inside",
			             {
			                 TeleportHelpers::MakePlace("Waste Disposal", 2542.052f, -214.3084f, -58.722965f, 0.0f),
			                 TeleportHelpers::MakePlace("Staff Lobby", 2547.9192f, -273.16754f, -58.723003f, 0.0f),
			                 TeleportHelpers::MakePlace("Mantrap Door", 2465.4746f, -279.2276f, -70.694145f, 0.0f),
			                 TeleportHelpers::MakePlace("Inside The Vault", 2515.1252f, -238.91661f, -70.73713f, 0.0f),
			                 TeleportHelpers::MakePlace("Outside The Vault", 2497.5098f, -238.50768f, -70.7388f, 0.0f),
			                 TeleportHelpers::MakePlace("Daily Cash Storage", 2520.8645f, -286.30685f, -58.723007f, 0.0f),
			             }},
			            {"Outside",
			                {
			                    TeleportHelpers::MakePlace("Main Gate", 917.24634f, 48.989567f, 80.89892f, 0.0f),
			                    TeleportHelpers::MakePlace("Staff Lobby", 965.14856f, -9.05023f, 80.63045f, 0.0f),
			                    TeleportHelpers::MakePlace("Waste Disposal", 997.5346f, 84.51491f, 80.990555f, 0.0f),
			                }}}},
			    {"Property",
			        {
			            {"Arcade", {}},
			            {"Facility", {}},
			            {"Kosatka", {}},
			        }},
			};
			initialized = true;
		}

		return cachedLocations;
	}

	void RenderPredefinedPlacesTeleport()
	{
		static std::string selectedCategory;
		static std::string selectedSubcategory;
		const auto& allCategories = GetAllTeleportLocations();

		ImGui::BeginGroup();

		// Header with refresh button
		ImGui::Text("Teleport System");
		ImGui::SameLine();
		if (ImGui::SmallButton("Refresh Properties"))
		{
			TeleportHelpers::ClearPropertyCache();
		}

		ImGui::Separator();

		// Category selection with improved styling
		ImGui::SetNextItemWidth(-1);
		if (ImGui::BeginCombo("##Category", selectedCategory.empty() ? "Select Category" : selectedCategory.c_str()))
		{
			for (const auto& [cat, _] : allCategories)
			{
				bool isSelected = (selectedCategory == cat);
				if (ImGui::Selectable(cat.c_str(), isSelected))
				{
					selectedCategory = cat;
					selectedSubcategory.clear();
				}
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		// Subcategory selection
		if (!selectedCategory.empty())
		{
			const auto& subMap = allCategories.at(selectedCategory);
			ImGui::SetNextItemWidth(-1);
			if (ImGui::BeginCombo("##Subcategory",
			        selectedSubcategory.empty() ? "Select Subcategory" : selectedSubcategory.c_str()))
			{
				for (const auto& [sub, _] : subMap)
				{
					bool isSelected = (selectedSubcategory == sub);
					if (ImGui::Selectable(sub.c_str(), isSelected))
						selectedSubcategory = sub;
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
		}

		// Location selection with enhanced UI
		if (!selectedCategory.empty() && !selectedSubcategory.empty())
		{
			ImGui::Separator();

			if (selectedCategory == "Property")
			{
				if (selectedSubcategory == "Arcade")
				{
					ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "Arcade Teleportation");
					TeleportHelpers::RenderPropertyTeleportOptions("Arcade", {{"Planning Board", {2711.773f, -369.458f, -54.781f}, 0.0f}, {"Garage Exit", {2677.237f, -361.494f, -55.187f}, 0.0f}});
				}
				else if (selectedSubcategory == "Facility")
				{
					ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "Facility Teleportation");
					TeleportHelpers::RenderPropertyTeleportOptions("Facility", {{"Heist Screen", {350.69284f, 4872.308f, -60.794243f}, -50.0f}, {"Heist Board", {515.528f, 4835.353f, -62.587f}, 0.0f}, {"Prisoner Cell", {512.888f, 4833.033f, -68.989f}, 0.0f}});
				}
				else if (selectedSubcategory == "Kosatka")
				{
					ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "Kosatka Teleportation");
					TeleportHelpers::RenderPropertyTeleportOptions("Kosatka", {{"Heist Board", {1561.2369f, 385.8831f, -49.689915f}, 175.0f}});
				}
			}
			else
			{
				const auto& places = allCategories.at(selectedCategory).at(selectedSubcategory);
				ImGui::TextColored(ImVec4(0.5f, 0.5f, 1.0f, 1.0f), "Available Locations (%zu)", places.size());

				// Scrollable region for many locations
				if (ImGui::BeginChild("LocationList", ImVec2(0, 200), true))
				{
					for (const auto& place : places)
					{
						if (ImGui::Selectable(place.name.c_str()))
						{
							FiberPool::Push([place] {
								TeleportHelpers::TeleportEntityTo(place);
							});
						}

						if (ImGui::IsItemHovered())
						{
							ImGui::BeginTooltip();
							ImGui::Text("Coordinates:");
							ImGui::Text("X: %.2f", place.position.x);
							ImGui::Text("Y: %.2f", place.position.y);
							ImGui::Text("Z: %.2f", place.position.z);
							ImGui::Text("Heading: %.1f°", place.heading);
							ImGui::EndTooltip();
						}
					}
				}
				ImGui::EndChild();
			}
		}

		ImGui::EndGroup();
	}
}