#include "Recovery.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "Recovery/HeistModifier.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping = std::make_shared<Category>("Shopping");
		auto missions = std::make_shared<Category>("Missions");
		auto vehiclesGroup = std::make_shared<Group>("Vehicles");
		auto generalGroup = std::make_shared<Group>("General");
		auto unlocker = std::make_shared<Category>("Unlocks");
		auto bunker = std::make_shared<Group>("Bunker Research");
		auto casino = std::make_shared<Group>("Casino Heist");
		auto awards  = std::make_shared<Group>("Heist Awards");
		auto arenawar = std::make_shared<Group>("Arena War");
		auto misc = std::make_shared<Group>("Misc");

		vehiclesGroup->AddItem(std::make_shared<BoolCommandItem>("dlcvehicles"_J));

		vehiclesGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
			{
				if (GiveVehicleReward::IsSafeToRunScript())
				{
					GiveVehicleReward::SetShouldRunScript(true);
				}
			}
		}));

		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("forcelaunchheist"_J));

		bunker->AddItem(std::make_shared<CommandItem>("bunkerresearch"_J));
		casino->AddItem(std::make_shared<CommandItem>("unlockcasinoheistclothing"_J));
		arenawar->AddItem(std::make_shared<CommandItem>("unlockareanawarclothing"_J));
		awards->AddItem(std::make_shared<CommandItem>("cayoawardsunlock"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockgenderchange"_J));
		misc->AddItem(std::make_shared<CommandItem>("careerprogressreawards"_J));
		awards->AddItem(std::make_shared<CommandItem>("agentsabotageawardsunlock"_J));
		shopping->AddItem(vehiclesGroup);
		missions->AddItem(generalGroup);
		unlocker->AddItem(awards);
		unlocker->AddItem(bunker);
		unlocker->AddItem(casino);
		unlocker->AddItem(arenawar);
		unlocker->AddItem(misc);
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(std::move(unlocker));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}