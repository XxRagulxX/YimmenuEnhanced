#include "TptoPlaces.hpp"

#include "core/backend/FiberPool.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"

#include <format>
#include <imgui.h>

namespace YimMenu::Features
{
	static TeleportPlace MakePlace(const char* name, float x, float y, float z, float heading)
	{
		return {std::string(name), {x, y, z}, heading};
	}

	CategoryMap GetAllTeleportLocations()
	{
		return {
		    {"CayoPerico",
		        {
		            {"Storage",
		                {
		                    MakePlace("North", 5081.0415f, -5755.32f, 15.829645f, -45.0f),
		                    MakePlace("West", 5006.722f, -5786.597f, 17.831688f, 35.0f),
		                    MakePlace("South", 5027.603f, -5734.682f, 17.255005f, -50.0f),
		                }},
		            {"Vault",
		                {
		                    MakePlace("Primary Target", 5006.7f, -5756.2f, 14.8f, 145.0f),
		                    MakePlace("Secondary Target", 4999.764f, -5749.864f, 14.84f, 0.0f),
		                }},
		            {"Compound",
		                {
		                    MakePlace("El Rubio's Office", 5010.12f, -5750.135f, 28.84334f, 325.0f),
		                    MakePlace("Front Gate Exit", 4990.039f, -5717.690f, 19.880217f, 50.0f),
		                }},
		        }},
		    {"Clothing Stores",
		        {
		            {"Downtown",
		                {
		                    MakePlace("Main Entrance", 100.0f, -200.0f, 10.0f, 0.0f),
		                }},
		        }},
		    
		};
	}

	void RenderPredefinedPlacesTeleport()
	{
		static std::string selectedCategory;
		static std::string selectedSubcategory;

		const auto& allCategories = GetAllTeleportLocations();

		ImGui::BeginGroup();
		ImGui::Text("Teleport");

		
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
			}
			ImGui::EndCombo();
		}

		
		if (!selectedCategory.empty())
		{
			const auto& subMap = allCategories.at(selectedCategory);
			if (ImGui::BeginCombo("##Subcategory",
			        selectedSubcategory.empty() ? "Select Subcategory" : selectedSubcategory.c_str()))
			{
				for (const auto& [sub, _] : subMap)
				{
					bool isSelected = (selectedSubcategory == sub);
					if (ImGui::Selectable(sub.c_str(), isSelected))
						selectedSubcategory = sub;
				}
				ImGui::EndCombo();
			}
		}

		
		if (!selectedCategory.empty() && !selectedSubcategory.empty())
		{
			const auto& places = allCategories.at(selectedCategory).at(selectedSubcategory);

			ImGui::Text("Available Locations:");
			for (const auto& place : places)
			{
				if (ImGui::Selectable(place.name.c_str()))
				{
					FiberPool::Push([place] {
						Entity entity = Self::GetPed();
						if (auto vehicle = Self::GetVehicle())
							entity = vehicle;

						entity.SetPosition(place.position);
						entity.SetHeading(place.heading);

						Notifications::Show("Teleport", std::format("Teleported to {}", place.name), NotificationType::Success, 3000);
					});
				}

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text("Coords: %.2f, %.2f, %.2f", place.position.x, place.position.y, place.position.z);
					ImGui::EndTooltip();
				}
			}
		}

		ImGui::EndGroup();
	}
}
