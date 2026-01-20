#include "CayoPericoHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderCayoPericoHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Cayo Perico Heist");

		auto cuts = std::make_shared<Group>("Heist Cuts", 2);
		auto setups = std::make_shared<Group>("Heist Setups");
		auto loots = std::make_shared<Group>("Loots", 2);
		auto misc = std::make_shared<Group>("Misc", 4);
		auto teleport = std::make_shared<Group>("Teleport");

		cuts->AddItem(std::make_shared<ListCommandItem>("cayopericoheistplayers"_J));
		cuts->AddItem(std::make_shared<CommandItem>("cayopericoheistsetmaxpayout"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut1"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut3"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut2"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut4"_J));
		cuts->AddItem(std::make_shared<CommandItem>("cayopericoheistsetcuts"_J));
		cuts->AddItem(std::make_shared<CommandItem>("cayopericoheistforceready"_J));


		setups->AddItem(std::make_shared<CommandItem>("cayopericoheistrequestforkosatka"_J));
		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistdifficulty"_J));
		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistprimarytarget"_J));
		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistweapon"_J));
		setups->AddItem(std::make_shared<CommandItem>("cayopericoheistsetup"_J));

		loots->AddItem(std::make_shared<IntCommandItem>("cayopericoheistprimarytargetvalue"_J));
		loots->AddItem(std::make_shared<IntCommandItem>("cayopericoheistsecondarytakevalue"_J));
		loots->AddItem(std::make_shared<CommandItem>("cayopericoheistsetprimarytargetvalue"_J, "Set##primarytargetvalue"));
		loots->AddItem(std::make_shared<CommandItem>("cayopericoheistsetsecondarytakevalue"_J, "Set##secondarytakevalue"));

		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistskiphacking"_J));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistcutsewer"_J));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistcutglass"_J));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheisttakeprimarytarget"_J));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistinstantfinish"_J));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistremovecayopericocameras"_J));
		misc->AddItem(std::make_shared<BoolCommandItem>("cayopericoheistinfiniteplasmacutterheat"_J));
		misc->AddItem(std::make_shared<BoolCommandItem>("cayopericoheistremovefencingfeeandpavelcut"_J));


		teleport->AddItem(std::make_shared<BoolCommandItem>("cayopericoheistotherteleport"_J));
		teleport->AddItem(std::make_shared<ConditionalItem>("cayopericoheistotherteleport"_J, std::make_shared<ListCommandItem>("cayopericootherteleportlist"_J)));
		teleport->AddItem(std::make_shared<ListCommandItem>("cayopericoteleportlist"_J));
		teleport->AddItem(std::make_shared<CommandItem>("cayopericoheistteleportcayo"_J));


		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(loots);
		tab->AddItem(misc);
		tab->AddItem(teleport);

		return tab;
	}
}