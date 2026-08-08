#include "DetourHook.hpp"
#include "Players.hpp"
#include "Hooks.hpp"

namespace YimMenu::Hooks
{
	void Info::NetworkPlayerMgrShutdown(CNetworkPlayerMgr* mgr)
	{
		if (!g_Running)
			return BaseHook::Get<Info::NetworkPlayerMgrShutdown, DetourHook>()->Original<decltype(&Info::NetworkPlayerMgrShutdown)>()(mgr);

		Players::Shutdown();
		BaseHook::Get<Info::NetworkPlayerMgrShutdown, DetourHook>()->Original<decltype(&Info::NetworkPlayerMgrShutdown)>()(mgr);
	}
}