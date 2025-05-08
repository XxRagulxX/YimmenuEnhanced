#include "Unlockall.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderUnlockallmenu()
	{
		auto tab = std::make_shared<TabItem>("Unlock Clothing");

		auto Other = std::make_shared<Group>("Other")

		Bunker->AddItem(std::make_shared<CommandItem>("unlockbunkerresearch"_J));
		Areanawar->AddItem(std::make_shared<CommandItem>("unlockareanawarclothing"_J));
		Casino->AddItem(std::make_shared<CommandItem>("unlockcasinoheistclothing"_J));
		Other->AddItem(std::make_shared<CommandIten>("unlockorbitalcannonfree"_J));
		Other->AddItem(std::make_shared<CommandItem>("unlockgenderchange"_J));

		tab->AddItem(Bunker);
		tab->AddItem(Areanawar);
		tab->AddItem(Casino);
		tab->AddItem(Other);

		return tab;
	}
}