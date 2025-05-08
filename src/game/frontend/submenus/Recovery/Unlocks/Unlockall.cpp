#include "Unlockall.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderUnlockallmenu()
	{
		auto tab = std::make_shared<TabItem>("");

		auto cuts   = std::make_shared<Group>("Heist Cuts", 2);
		auto setups = std::make_shared<Group>("Heist Setups");
		auto misc   = std::make_shared<Group>("Misc", 1);

		misc->AddItem(std::make_shared<CommandItem>("apartmentheistskiphacking"_J));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistskipdrilling"_J));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistinstantfinish"_J));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistinstantfinishpacific"_J));

		tab->AddItem(misc);

		return tab;
	}
}