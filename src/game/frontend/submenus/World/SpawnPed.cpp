#include "SpawnPed.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/PedModels.hpp"
#include "game/gta/Ped.hpp"
#include "game/gta/Natives.hpp"
#include "types/ped/PedCombatAttribute.hpp"
#include "game/gta/data/Weapons.hpp"
#include "game/gta/Scripts.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildSpawnPedMenu()
	{
		auto menu = std::make_shared<Category>("Spawn Ped");

		static bool invincible;
		static bool spawnDead;
		static bool spawnAsBodyguard;
		static bool spawnAsCop;
		static bool giveAllWeapons;
		static bool spawnAsProstitute;
		static std::vector<Ped> spawnedPeds;

		menu->AddItem(std::make_unique<ImGuiItem>([] {
			static char search[64];
			ImGui::SetNextItemWidth(300.f);
			ImGui::InputTextWithHint("Name", "Search", search, sizeof(search));

			const int visible = std::min(20, static_cast<int>(g_PedModels.size()));
			const float height = visible * ImGui::GetTextLineHeightWithSpacing();
			if (ImGui::BeginListBox("##vehicles", {300.f, height}))
			{
				std::string lower = search;
				std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
				for (int veh = 0; veh < g_PedModels.size(); veh++)
				{
					auto name = g_PedModels[veh];
					auto lowerName = std::string(name);
					std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

					bool matchesSearch = lowerName.find(lower) != std::string::npos;
					if (matchesSearch)
					{
						ImGui::PushID(name);
						if (ImGui::Selectable(name))
						{
							FiberPool::Push([name] {
								auto hash = Joaat(name);
								auto handle = Ped::Create(hash, Self::GetPed().GetPosition(), Self::GetPed().GetHeading());

								handle.SetCombatAttribute(PedCombatAttribute::AlwaysFight, true);
								handle.SetCombatAttribute(PedCombatAttribute::DisableAllRandomsFlee, true);
								handle.SetCombatAttribute(PedCombatAttribute::DisableFleeFromCombat, true);
								handle.SetCombatAttribute(PedCombatAttribute::CanUseVehicles, true);
								handle.SetCombatAttribute(PedCombatAttribute::CanLeaveVehicle, true);

								if (invincible)
									handle.SetInvincible(true);

								if (spawnDead)
									handle.Kill();

								if (spawnAsBodyguard)
								{
									handle.SetCombatAttribute(PedCombatAttribute::CanCharge, true);
									handle.SetCombatAttribute(PedCombatAttribute::CanCommandeerVehicles, true);
									handle.SetCombatAttribute(PedCombatAttribute::DisableInjuredOnGround, true);
									handle.SetCombatAttribute(PedCombatAttribute::AllowDogFighting, true);
									handle.SetCombatAttribute(PedCombatAttribute::PerfectAccuracy, true);
									handle.SetCombatAttribute(PedCombatAttribute::UseVehicleAttack, true);
									handle.SetCombatAttribute(PedCombatAttribute::CanDoDrivebys, true);
									handle.SetCombatAttribute(PedCombatAttribute::FleesFromInvincibleOpponents, false);
									handle.SetCombatAttribute(PedCombatAttribute::CanThrowSmokeGrenade, true);
									handle.SetCombatAttribute(PedCombatAttribute::CanSeeUnderwaterPeds, true);
									
									auto group = Self::GetPlayer().GetGroup();
									handle.AddToGroup(group);
									PED::SET_GROUP_SEPARATION_RANGE(group, 9999.9f);
									PED::SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(handle.GetHandle(), group, true);
									PED::SET_GROUP_FORMATION_SPACING(group, 10.0f, 0.0f, 0.0f);
								}

								if (spawnAsCop)
								{
									handle.SetAsCop();
								}

								if (giveAllWeapons)
								{
									for (auto hash : g_WeaponHashes)
										handle.GiveWeapon(hash);
								}

								if (spawnAsProstitute)
								{
									handle.StartScenario("WORLD_HUMAN_PROSTITUTE_HIGH_CLASS");
									handle.SetKeepTask(true);

									if (!*Pointers.IsSessionStarted)
									{
										PED_INDEX ped = handle.GetHandle();
										Scripts::StartScript("pb_prostitute"_J, eStackSizes::FRIEND, &ped, 1);
									}
								}

								spawnedPeds.push_back(handle);
							});
						}
						ImGui::PopID();
					}
				}

				ImGui::EndListBox();
			}

			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Checkbox("Invincible", &invincible);
			ImGui::Checkbox("Spawn Dead", &spawnDead);
			ImGui::Checkbox("Spawn As Bodyguard", &spawnAsBodyguard);
			ImGui::Checkbox("Spawn As Cop", &spawnAsCop);
			ImGui::Checkbox("Give All Weapons", &giveAllWeapons);
			ImGui::Checkbox("Spawn As Prostitute", &spawnAsProstitute);
			if (ImGui::Button("Remove All"))
			{
				FiberPool::Push([] {
					for (auto& ped : spawnedPeds)
						if (ped)
							ped.Delete();

					spawnedPeds.clear();
				});
			}
			ImGui::EndGroup();
		}));

		return menu;
	}
}