#include "DetourHook.hpp"
#include "Hooks.hpp"
#include "Players.hpp"
#include "CNetGamePlayer.hpp"
#include "BoolCommand.hpp"
#include "Natives.hpp"
#include "FiberPool.hpp"

namespace YimMenu::Features
{
	static BoolCommand _NotifyOnPlayerJoin{
	    "notifyonplayerjoin",
	    "Notify on Player Join",
	    "Notifies you when a player joins above the map",
	    true};
}

namespace YimMenu::Hooks
{
	void Info::AssignPhysicalIndex(CNetworkPlayerMgr* mgr, CNetGamePlayer* player, std::uint8_t index)
	{
		if (!g_Running)
			return BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);

		if (index != 255)
		{
			if (player->m_PlayerIndex != 255)
				LOGF(WARNING, "Player {} changed their player index from {} to {}", player->GetName(), player->m_PlayerIndex, index);
			BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);
			Players::OnPlayerJoin(player);
			if (Features::_NotifyOnPlayerJoin.GetState() && !player->IsLocal())
			{
				std::string name = player->GetName();
				FiberPool::Push([name] {
					HUD::SET_TEXT_OUTLINE();
					HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(std::format("<C>{}</C> joined.", name).data());
					HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
				});
			}
		}
		else
		{
			Players::OnPlayerLeave(player);
			BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);
		}
	}
}