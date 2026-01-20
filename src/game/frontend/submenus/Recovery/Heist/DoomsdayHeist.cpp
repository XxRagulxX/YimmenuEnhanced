#include "DoomsdayHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderDoomsdayHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Doomsday Heist");

		auto cuts = std::make_shared<Group>("Heist Cuts", 2);
		auto setups = std::make_shared<Group>("Heist Setups");
		auto misc = std::make_shared<Group>("Misc", 1);
		auto teleport = std::make_shared<Group>("Teleport");

		cuts->AddItem(std::make_shared<ListCommandItem>("doomsdayheistplayers"_J));
		cuts->AddItem(std::make_shared<CommandItem>("doomsdayheistsetmaxpayout"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut1"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut3"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut2"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut4"_J));
		cuts->AddItem(std::make_shared<CommandItem>("doomsdayheistforceready"_J));
		cuts->AddItem(std::make_shared<CommandItem>("doomsdayheistsetcuts"_J));

		setups->AddItem(std::make_shared<ListCommandItem>("doomsdayheistcategory"_J));
		setups->AddItem(std::make_shared<CommandItem>("doomsdayheistsetup"_J));

		misc->AddItem(std::make_shared<CommandItem>("doomsdayheistskiphacking"_J));
		misc->AddItem(std::make_shared<CommandItem>("doomsdayheistinstantfinish"_J));
		misc->AddItem(std::make_shared<CommandItem>("doomsdayheistinstantfinishact3"_J));

		teleport->AddItem(std::make_shared<ListCommandItem>("doomsdayheistteleportlist"_J));
		teleport->AddItem(std::make_shared<CommandItem>("doomsdayhesitteleport"_J));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(misc);
		tab->AddItem(teleport);

		return tab;
	}
}