#include "Menu/Menu.hpp"
#include "Menu/UIManager.hpp"
#include "Menu/MenuSelf.hpp"
#include "Menu/MenuVehicle.hpp"
#include "Menu/MenuTeleport.hpp"
#include "Menu/MenuNetwork.hpp"
#include "Menu/MenuPlayers.hpp"
#include "Menu/MenuRecovery.hpp"
#include "Menu/MenuSettings.hpp"
#include "Menu/MenuDebug.hpp"
#include "Menu/MenuWorld.hpp"

namespace YimMenu
{
	// Drawing this tree is no longer this file's job at all - it now
	// happens directly from Rendering/GridRenderer.cpp's own DrawImpl,
	// alongside every other always-on overlay it already draws
	// (Notifications, ESP, ChatDisplay, ...), via UIManager::Draw()/
	// DrawText() (see Config/Themes.hpp's own RenderClassicTheme()/
	// RenderClassicThemeText() and Menu/ClassicUI.hpp's class comment for
	// the two-pass contract that requires). This file's only remaining
	// job is building the tree itself once, at startup.
	void Menu::Init()
	{
		// Arguably the only place this file should be edited at for more menus
		UIManager::AddSubmenu(std::make_shared<Submenus::Self>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Vehicle>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Teleport>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Network>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Players>());
		UIManager::AddSubmenu(std::make_shared<Submenus::World>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Recovery>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Settings>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Debug>());
	}
}
