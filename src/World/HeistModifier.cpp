#include "World/HeistModifier.hpp"
#include "World/ApartmentHeist.hpp"
#include "World/DiamondCasinoHeist.hpp"
#include "World/CayoPericoHeist.hpp"
#include "World/DoomsdayHeist.hpp"
#include "World/Missions.hpp"
#include "World/KortzCenterHeist.hpp"

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