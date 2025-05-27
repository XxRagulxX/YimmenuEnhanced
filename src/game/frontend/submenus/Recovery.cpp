#include "Recovery.hpp"
#include "Recovery/HeistModifier.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto missions = std::make_shared<Category>("Missions");
		auto casino   = std::make_shared<Category>("Casino");

		auto generalGroup = std::make_shared<Group>("General");
		auto unlocker = std::make_shared<Category>("Unlocks");
		auto awards       = std::make_shared<Group>("Heist Awards");
		auto unlock_goodies = std::make_shared<Group>("Clothing, Tattoos & Masks");
		auto vehicle        = std::make_shared<Group>("Vehicle");
		auto misc = std::make_shared<Group>("Misc");
		auto business = std::make_shared<Group>("Business");
		auto gtaplus  = std::make_shared<Group>("GTA+");
		
		

		auto casinoGroup  = std::make_shared<Group>("CasinoRigSlotMachines");


		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("forcelaunchheist"_J));
		generalGroup->AddItem(std::make_shared<IntCommandItem>("rpmultiplierinput"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("rpmultiplier"_J));

		casinoGroup->AddItem(std::make_shared<BoolCommandItem>("casinomanipulaterigslotmachines"_J));

		misc->AddItem(std::make_shared<CommandItem>("bunkerresearch"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockclothing"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockallawards"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockgenderchange"_J));
		awards->AddItem(std::make_shared<CommandItem>("careerprogressreawards"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockalltattoos"_J));
		gtaplus->AddItem(std::make_shared<BoolCommandItem>("scmembership_bypass"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockachievements"_J));
		vehicle->AddItem(std::make_shared<CommandItem>("unlockvehicle"_J));
		vehicle->AddItem(std::make_shared<CommandItem>("unlockvehiclegunmods"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockallparachutes"_J));
		misc->AddItem(std::make_shared<CommandItem>("fastrunreloadunlock"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockmasks"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockflightschool"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockweapons"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockcollectables"_J));
		business->AddItem(std::make_shared<CommandItem>("resupplybusiness"_J));
		business->AddItem(std::make_shared<BoolCommandItem>("supplycooldownbypass"_J));
		business->AddItem(std::make_shared<CommandItem>("mcbusinessmaxsellprice"_J));
		misc->AddItem(std::make_shared<CommandItem>("nightclubpopularity"_J));
		missions->AddItem(generalGroup);
		unlocker->AddItem(awards);
		unlocker->AddItem(unlock_goodies);
		unlocker->AddItem(misc);
		unlocker->AddItem(gtaplus);
		unlocker->AddItem(business);
		unlocker->AddItem(vehicle);
		casino->AddItem(casinoGroup);

		AddCategory(std::move(missions));
		AddCategory(std::move(unlocker));
		AddCategory(std::move(casino));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}