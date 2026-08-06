#include "HeistModifier.hpp"
#include "ApartmentHeist.hpp"
#include "DiamondCasinoHeist.hpp"
#include "CayoPericoHeist.hpp"
#include "DoomsdayHeist.hpp"
#include "Missions.hpp"
#include "KortzCenterHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildHeistModifierMenu()
	{
		auto menu        = std::make_shared<Category>("Heists");
		auto heistTabBar = std::make_shared<TabBarItem>("Heist Modifier");

		heistTabBar->AddItem(RenderApartmentHeistMenu());
		heistTabBar->AddItem(RenderDiamondCasinoHeistMenu());
		heistTabBar->AddItem(RenderCayoPericoHeistMenu());
		heistTabBar->AddItem(RenderDoomsdayHeistMenu());
		heistTabBar->AddItem(RenderMissionsMenu());
		heistTabBar->AddItem(RenderKortzCenterHeistMenu());

		menu->AddItem(std::move(heistTabBar));

		return menu;
	}
}