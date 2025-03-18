#include "Troll.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildTrollMenu()
	{
		auto menu = std::make_shared<Category>("Troll");

		auto general = std::make_shared<Group>("General");
		auto bounty = std::make_shared<Group>("Bounty", 1);

		general->AddItem(std::make_shared<PlayerCommandItem>("sendsext"_J));

		bounty->AddItem(std::make_shared<IntCommandItem>("bountyamount"_J, "Amount"));
		bounty->AddItem(std::make_shared<BoolCommandItem>("anonymousbounty"_J, "Anonymous"));
		bounty->AddItem(std::make_shared<PlayerCommandItem>("setbounty"_J));

		menu->AddItem(general);
		menu->AddItem(bounty);

		return menu;
	}
}