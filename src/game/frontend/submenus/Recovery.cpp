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
		auto clothing = std::make_shared<Group>("Clothing");
		auto awards  = std::make_shared<Group>("Heist Awards");
		auto arenawar = std::make_shared<Group>("Arena War");
		auto misc = std::make_shared<Group>("Misc");
		auto gtaplus  = std::make_shared<Group>("GTA+");

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
		clothing->AddItem(std::make_shared<CommandItem>("unlockclothing"_J));
		awards->AddItem(std::make_shared<CommandItem>("cayoawardsunlock"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockgenderchange"_J));
		misc->AddItem(std::make_shared<CommandItem>("careerprogressreawards"_J));
		awards->AddItem(std::make_shared<CommandItem>("agentsabotageawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("bottomdollarbountiesawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("thechopshopawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("lossantosdrugwarsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("thecontractawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("lossantostunersawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("lossantossummerspecialawardsunlock"_J));
		casino->AddItem(std::make_shared<CommandItem>("casinoheistawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("nightclubawardsunlock"_J));
		arenawar->AddItem(std::make_shared<CommandItem>("arenawarawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("doomsdayawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("apartmentheistawardsunlock"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockallcontacts"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlocksometattoos"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlocksometradeprice"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockshotaro"_J));
		gtaplus->AddItem(std::make_shared<BoolCommandItem>("scmembership_bypass"_J));
		shopping->AddItem(vehiclesGroup);
		missions->AddItem(generalGroup);
		unlocker->AddItem(awards);
		unlocker->AddItem(bunker);
		unlocker->AddItem(clothing);
		unlocker->AddItem(arenawar);
		unlocker->AddItem(misc);
		unlocker->AddItem(gtaplus);
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(std::move(unlocker));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}