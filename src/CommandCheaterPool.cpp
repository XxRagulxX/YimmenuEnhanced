#include "LoopedCommand.hpp"
#include "DetourHook.hpp"
#include "Hooks.hpp"
#include "Pointers.hpp"

namespace YimMenu::Features
{
	class CheaterPool : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		int m_OldRegion;

		virtual void OnEnable() override
		{
			Pointers.SetJoinRequestPoolTypePatch->Apply();
			Pointers.HandleJoinRequestIgnorePoolPatch->Apply();
			m_OldRegion = *Pointers.RegionCode;
		}

		virtual void OnTick() override
		{
			*Pointers.RegionCode = 0; // put everyone in the same region for easier matchmaking
		}

		virtual void OnDisable() override
		{
			Pointers.SetJoinRequestPoolTypePatch->Restore();
			Pointers.HandleJoinRequestIgnorePoolPatch->Restore();
			*Pointers.RegionCode = m_OldRegion;
		}
	};

	static CheaterPool _CheaterPool{"cheaterpool", "Join YimMenu-only Sessions", "Matchmaking will put you into sessions with other YimMenu users."};
}

namespace YimMenu::Hooks
{
	int Network::GetPoolType()
	{
		if (YimMenu::Features::_CheaterPool.GetState())
			return 1;

		return BaseHook::Get<Network::GetPoolType, DetourHook>()->Original<decltype(&Network::GetPoolType)>()();
	}
}