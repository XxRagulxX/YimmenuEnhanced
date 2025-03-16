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

		toxicGroup->AddItem(std::make_shared<CommandItem>("killall"_J, "Kill All"));
		toxicGroup->AddItem(std::make_shared<CommandItem>("explodeall"_J, "Explode All"));
	
		session->AddItem(toxicGroup);
	
		AddCategory(std::move(session));
	}
}