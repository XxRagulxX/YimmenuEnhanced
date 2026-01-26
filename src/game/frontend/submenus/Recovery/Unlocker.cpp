#include "Unlocker.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildUnlockerMenu()
	{
		auto unlocker = std::make_shared<Category>("Unlocks");

		auto awards         = std::make_shared<Group>("Heist & Progress Awards");
		auto unlock_goodies = std::make_shared<Group>("Clothing, Tattoos & Masks");
		auto misc           = std::make_shared<Group>("Misc Unlocks & Rank");


		unlock_goodies->AddItem(std::make_shared<BoolCommandItem>("unlockindependenceday"_J));
		unlock_goodies->AddItem(std::make_shared<BoolCommandItem>("togglehalloween"_J));
		unlock_goodies->AddItem(std::make_shared<BoolCommandItem>("togglexmas"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockclothing"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockalltattoos"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockmasks"_J));


		awards->AddItem(std::make_shared<CommandItem>("unlockcareerprogressawards"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockachievements"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockcollectables"_J));


		misc->AddItem(std::make_shared<IntCommandItem>("setrankvalue"_J));
		misc->AddItem(std::make_shared<CommandItem>("setrank"_J));
		misc->AddItem(std::make_shared<IntCommandItem>("setcrewvalue"_J));
		misc->AddItem(std::make_shared<CommandItem>("setcrewrank"_J));


		misc->AddItem(std::make_shared<CommandItem>("unlockeverything"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockspecialitems"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockallparachutes"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockflightschool"_J));


		misc->AddItem(std::make_shared<CommandItem>("bunkerresearch"_J));
		misc->AddItem(std::make_shared<CommandItem>("fastrunreloadunlock"_J));


		unlocker->AddItem(std::move(awards));
		unlocker->AddItem(std::move(unlock_goodies));
		unlocker->AddItem(std::move(misc));

		return unlocker;
	}
}