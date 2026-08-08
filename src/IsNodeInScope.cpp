#include "DetourHook.hpp"
#include "NodeHooks.hpp"
#include "Hooks.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	bool Hooks::Spoofing::IsNodeInScope(void* node, void* a2, std::uint8_t playerId, int flags, unsigned int a5, int a6)
	{
		if (NodeHooks::ShouldForceInScope(reinterpret_cast<CProjectBaseSyncDataNode*>(node)))
			return true;

		return Hooking::Get<Spoofing::IsNodeInScope>()->Original<decltype(&Spoofing::IsNodeInScope)>()(node, a2, playerId, flags, a5, a6);
	}
}