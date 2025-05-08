#include "Unlockall.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderUnlockallmenu()
	{
		auto tab = std::make_shared<TabItem>("Unlock Clothing");

		Bunker->AddItem(std::make_shared<CommandItem>("unlockbunkerresearch"_J));
		Areanawar->AddItem(std::make_shared<CommandItem>("unlockareanawarclothing"_J));

		tab->AddItem(Bunker);
		tab->AddItem(Areanawar);

		return tab;
	}
}