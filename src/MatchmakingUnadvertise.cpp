#include "Hooks.hpp"
#include "DetourHook.hpp"
#include "CustomMatchmaking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingUnadvertise(int profile_index, MatchmakingId* id, rage::rlTaskStatus* status)
	{
		if (!CustomMatchmaking::OnUnadvertise(id))
		{
			status->m_Status = 2;
			return true;
		}
		return BaseHook::Get<Matchmaking::MatchmakingUnadvertise, DetourHook>()->Original<decltype(&Matchmaking::MatchmakingUnadvertise)>()(profile_index, id, status);
	}
}