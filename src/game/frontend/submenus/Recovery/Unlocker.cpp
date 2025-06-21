#include "Unlocker.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildUnlockerMenu()
	{
		auto unlocker = std::make_shared<Category>("Unlocks");

		auto awards = std::make_shared<Group>("Heist Awards");
		auto unlock_goodies = std::make_shared<Group>("Clothing, Tattoos & Masks");
		auto misc = std::make_shared<Group>("Misc");


		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockclothing"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockalltattoos"_J));
		unlock_goodies->AddItem(std::make_shared<CommandItem>("unlockmasks"_J));


		awards->AddItem(std::make_shared<CommandItem>("unlockallawards"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockachievements"_J));
		awards->AddItem(std::make_shared<CommandItem>("unlockcollectables"_J));

		misc->AddItem(std::make_shared<CommandItem>("bunkerresearch"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockspecialitems"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockallparachutes"_J));
		misc->AddItem(std::make_shared<CommandItem>("fastrunreloadunlock"_J));
		misc->AddItem(std::make_shared<CommandItem>("unlockflightschool"_J));
		misc->AddItem(std::make_shared<CommandItem>("nightclubpopularity"_J));

		unlocker->AddItem(std::move(awards));
		unlocker->AddItem(std::move(unlock_goodies));
		unlocker->AddItem(std::move(misc));

		return unlocker;
	}
}