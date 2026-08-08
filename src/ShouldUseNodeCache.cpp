#include "DetourHook.hpp"
#include "NodeHooks.hpp"
#include "Hooks.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	bool Hooks::Spoofing::ShouldUseNodeCache(void* node, int flags)
	{
		if (NodeHooks::ShouldSkipNodeCache(reinterpret_cast<CProjectBaseSyncDataNode*>(node)))
			return false;

		return Hooking::Get<Spoofing::ShouldUseNodeCache>()->Original<decltype(&Spoofing::ShouldUseNodeCache)>()(node, flags);
	}
}