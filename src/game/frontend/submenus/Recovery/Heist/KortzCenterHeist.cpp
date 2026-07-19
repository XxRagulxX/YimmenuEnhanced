#include "KortzCenterHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderKortzCenterHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Kortz Center Heist");

		auto target    = std::make_shared<Group>("Primary Target", 1);
		auto action    = std::make_shared<Group>("", 1);

		target->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistprimarytarget"_J));

		action->AddItem(std::make_shared<CommandItem>("kortzcenterheistsetup"_J, "Setup##kortz"));

		tab->AddItem(target);
		tab->AddItem(action);

		return tab;
	}
}