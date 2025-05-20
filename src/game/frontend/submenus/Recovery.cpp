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
		auto tattoos = std::make_shared<Group>("Tattoos");
		auto misc = std::make_shared<Group>("Misc");
		auto gtaplus  = std::make_shared<Group>("GTA+");
		auto business = std::make_shared<Group>("Business");

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
		misc->AddItem(std::make_shared<CommandItem>("careerprogressreawards"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockallcontacts"_J));
		tattoos->AddItem(std::make_shared<CommandItem>("unlockalltattoos"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlocksometradeprice"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockshotaro"_J));
		gtaplus->AddItem(std::make_shared<BoolCommandItem>("scmembership_bypass"_J));
		awards->AddItem(std::make_shared<CommandItem>("setsomerandomstats"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockachievements"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockvehicle"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockliverys"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockallparachutes"_J));
		misc->AddItem(std::make_shared<CommandItem>("fastrunreloadunlock"_J));
		business->AddItem(std::make_shared<CommandItem>("singlemcvehiclesell"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockdripfeedvehicle"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockmasks"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockflightschool"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlocktradeprice"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockweapons"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockhiddenliveries"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockxmasplates"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockrarecloths"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockcollectables"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockcollectablesldorganics"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockcollectablesplayingcardsactionfigures"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockcollectablessnowman"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlocklscm"_J));
		business->AddItem(std::make_shared<CommandItem>("resupplybusiness"_J));
		shopping->AddItem(vehiclesGroup);
		missions->AddItem(generalGroup);
		unlocker->AddItem(awards);
		unlocker->AddItem(bunker);
		unlocker->AddItem(tattoos);
		unlocker->AddItem(clothing);
		unlocker->AddItem(misc);
		unlocker->AddItem(gtaplus);
		unlocker->AddItem(business);
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(std::move(unlocker));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}