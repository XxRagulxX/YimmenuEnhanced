#include "Category.hpp"
#include "FiberPool.hpp"
#include "Items.hpp"
#include "Natives.hpp"
#include "ScriptFunction.hpp"
#include "ScriptEvent.hpp"
#include "Self.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildMiscMenu()
	{
		auto misc = std::make_unique<Category>("Misc");

		misc->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Network Bail"))
			{
				FiberPool::queueJob([] {
					NETWORK::NETWORK_BAIL(0, 24, 0);
				});
			}

			static int interiorIndex = 0;
			ImGui::InputInt("interiorIndex", &interiorIndex);

			static bool enterOwnerInterior = false;
			ImGui::Checkbox("enterOwnerInterior", &enterOwnerInterior);

			if (ImGui::Button("DoTeleport"))
			{
				FiberPool::queueJob([] {
					SCRIPT_EVENT_SEND_TO_INTERIOR message;
					message.Interior = interiorIndex;
					message.EnterOwnerInterior = enterOwnerInterior;
					message.GoonsOnly = false;
					message.InstanceId = 0;
					message.SubInstanceId = -1;
					message.Owner = Self::GetPlayer().GetId();
					message.Distance = 99999;
					message.Position = {0, 0, 0};

					message.SetAllPlayers();
					message.Send();
				});
			}

			static int team;
			ImGui::InputInt("Team", &team);
			if (ImGui::Button("fm_mission_controller DoTeamSwap"))
			{
				FiberPool::queueJob([] {
					static ScriptFunction DoTeamSwap("fm_mission_controller"_J, ScriptPointer("DoTeamSwap", "2D 02 04 00 00 38 00 50"));
					DoTeamSwap.Call<void>(team, true);
				});
			}
		}));

		misc->AddItem(std::make_shared<CommandItem>("dumpdatahash"_J));

		return misc;
	}
}