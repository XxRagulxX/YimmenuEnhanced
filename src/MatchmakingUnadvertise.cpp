#include "Hooks.hpp"
#include "DetourHook.hpp"
#include "CustomMatchmaking.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingUnadvertise(int profile_index, MatchmakingId* id, rage::rlTaskStatus* status)
	{
		if (!CustomMatchmaking::OnUnadvertise(id))
		{
			status->m_Status = 2;
			return true;
		}
		return Hooking::Get<Matchmaking::MatchmakingUnadvertise>()->Original<decltype(&Matchmaking::MatchmakingUnadvertise)>()(profile_index, id, status);
	}
}