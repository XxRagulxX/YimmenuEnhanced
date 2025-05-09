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
		auto arenawar = std::make_shared<Group>("Arena War");

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
		shopping->AddItem(vehiclesGroup);
		missions->AddItem(generalGroup);
		unlocker->AddItem(bunker);
		unlocker->AddItem(casino);
		unlocker->AddItem(arenawar);
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(std::move(unlocker));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}