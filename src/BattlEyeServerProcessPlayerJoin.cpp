#include "DetourHook.hpp"
#include "BoolCommand.hpp"
#include "Commands.hpp"
#include "Hooks.hpp"
#include "Natives.hpp"
#include "CBattlEyePlayerModifyContext.hpp"
#include "AnticheatBypass.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	bool Anticheat::BattlEyeServerProcessPlayerJoin(CBattlEyePlayerModifyInterface* server_iface, CBattlEyePlayerModifyContext* context)
	{
		if (!AnticheatBypass::IsBattlEyeRunning())
		{
			if (context->m_IsLocal)
			{
				if (NETWORK::NETWORK_SESSION_IS_CLOSED_FRIENDS() || NETWORK::NETWORK_SESSION_IS_CLOSED_CREW() || NETWORK::NETWORK_SESSION_IS_SOLO() || NETWORK::NETWORK_SESSION_IS_PRIVATE())
				{
					return true;
				}
			}

			static auto cheater_pool = Commands::GetCommand<BoolCommand>("cheaterpool"_J);
			if (cheater_pool->GetState())
			{
				return true;
			}
		}

		return Hooking::Get<Anticheat::BattlEyeServerProcessPlayerJoin>()->Original<decltype(&Anticheat::BattlEyeServerProcessPlayerJoin)>()(server_iface, context);
	}
}