#include "Network.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Network::Network() :
	    Submenu::Submenu("Network")
	{
		// TODO: this needs a rework
		auto session = std::make_shared<Category>("Session");
		auto toxicGroup = std::make_shared<Group>("Toxic");
		auto enhancements = std::make_shared<Group>("Enhancements");

		toxicGroup->AddItem(std::make_shared<CommandItem>("killall"_J, "Kill All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("explodeall"_J, "Explode All"));
	
		enhancements->AddItem(std::make_shared<BoolCommandItem>("fastjoin"_J));

		session->AddItem(toxicGroup);
		session->AddItem(enhancements);
	
		AddCategory(std::move(session));
	}
}