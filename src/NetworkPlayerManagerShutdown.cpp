#include "DetourHook.hpp"
#include "Players.hpp"
#include "Hooks.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	void Info::NetworkPlayerMgrShutdown(CNetworkPlayerMgr* mgr)
	{
		if (!g_Running)
			return Hooking::Get<Info::NetworkPlayerMgrShutdown>()->Original<decltype(&Info::NetworkPlayerMgrShutdown)>()(mgr);

		Players::Shutdown();
		Hooking::Get<Info::NetworkPlayerMgrShutdown>()->Original<decltype(&Info::NetworkPlayerMgrShutdown)>()(mgr);
	}
}