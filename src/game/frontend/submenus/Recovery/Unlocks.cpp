#include "Unlocks.hpp"
#include "Unlocks/Unlockall.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildUnlockall()
	{
		auto menu = std::make_shared<Category>("Unlocks");

		// Example unlocks � you should replace or add your actual unlock functions here
		menu->AddItem(RenderUnlockallmenu());
		menu->AddItem(std::make_shared<ImGuiItem>([] {
			ImGui::EndTabBar();
		}));
		return menu;
	}
}
