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
		auto tattoos = std::make_shared<Group>("Tattoos & Masks");
		auto misc = std::make_shared<Group>("Misc");
		auto gtaplus  = std::make_shared<Group>("GTA+");
		auto business = std::make_shared<Group>("Business");
		auto vehicle = std::make_shared<Group>("Vehicle");

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
		awards->AddItem(std::make_shared<CommandItem>("unlockallawards"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockgenderchange"_J));
		awards->AddItem(std::make_shared<CommandItem>("careerprogressreawards"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockallcontacts"_J));
		tattoos->AddItem(std::make_shared<CommandItem>("unlockalltattoos"_J));
		vehicle->AddItem(std::make_shared<CommandItem>("unlocksometradeprice"_J));
		gtaplus->AddItem(std::make_shared<BoolCommandItem>("scmembership_bypass"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockachievements"_J));
		vehicle->AddItem(std::make_shared<CommandItem>("unlockvehicle"_J));
		vehicle->AddItem(std::make_shared<CommandItem>("unlockvehiclegunmods"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockallparachutes"_J));
		misc->AddItem(std::make_shared<CommandItem>("fastrunreloadunlock"_J));
		business->AddItem(std::make_shared<CommandItem>("singlemcvehiclesell"_J));
		tattoos->AddItem(std::make_shared<CommandItem>("unlockmasks"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockflightschool"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlocktradeprice"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockweapons"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockcollectables"_J));
		business->AddItem(std::make_shared<CommandItem>("resupplybusiness"_J));
		business->AddItem(std::make_shared<BoolCommandItem>("supplycooldownbypass"_J));
		shopping->AddItem(vehiclesGroup);
		missions->AddItem(generalGroup);
		unlocker->AddItem(awards);
		unlocker->AddItem(bunker);
		unlocker->AddItem(tattoos);
		unlocker->AddItem(clothing);
		unlocker->AddItem(misc);
		unlocker->AddItem(gtaplus);
		unlocker->AddItem(business);
		unlocker->AddItem(vehicle);
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(std::move(unlocker));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}