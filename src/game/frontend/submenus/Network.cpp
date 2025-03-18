#include "Network.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Network::Network() :
	    Submenu::Submenu("Network")
	{
		// TODO: this needs a rework
		auto session = std::make_shared<Category>("Session");
		auto bountyGroup = std::make_shared<Group>("Bounty", 1);
		auto toxicGroup = std::make_shared<Group>("Toxic");
		auto trollGroup = std::make_shared<Group>("Troll");
		auto enhancements = std::make_shared<Group>("Enhancements");

		bountyGroup->AddItem(std::make_shared<IntCommandItem>("bountyamount"_J, "Amount"));
		bountyGroup->AddItem(std::make_shared<BoolCommandItem>("anonymousbounty"_J, "Anonymous"));
		bountyGroup->AddItem(std::make_shared<CommandItem>("setbountyall"_J, "Set Bounties"));

		trollGroup->AddItem(std::make_shared<CommandItem>("sendsextall"_J, "Send Sexts"));

		toxicGroup->AddItem(std::make_shared<CommandItem>("killall"_J, "Kill All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("explodeall"_J, "Explode All"));

		enhancements->AddItem(std::make_shared<BoolCommandItem>("fastjoin"_J));

		session->AddItem(bountyGroup);
		session->AddItem(trollGroup);
		session->AddItem(toxicGroup);
		session->AddItem(enhancements);
	
		AddCategory(std::move(session));
	}
}