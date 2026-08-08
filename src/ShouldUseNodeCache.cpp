#include "DetourHook.hpp"
#include "NodeHooks.hpp"
#include "Hooks.hpp"

namespace YimMenu::Hooks
{
	bool Hooks::Spoofing::ShouldUseNodeCache(void* node, int flags)
	{
		if (NodeHooks::ShouldSkipNodeCache(reinterpret_cast<CProjectBaseSyncDataNode*>(node)))
			return false;

		return BaseHook::Get<Spoofing::ShouldUseNodeCache, DetourHook>()->Original<decltype(&Spoofing::ShouldUseNodeCache)>()(node, flags);
	}
}