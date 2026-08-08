#include "Hooks.hpp"
#include "DetourHook.hpp"
#include "CustomMatchmaking.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingUpdate(int profile_index, MatchmakingId* id, int num_slots, int available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* data, rage::rlTaskStatus* status)
	{
		CustomMatchmaking::OnUpdate(num_slots, available_slots, info, data, id);
		return Hooking::Get<Matchmaking::MatchmakingUpdate>()->Original<decltype(&Matchmaking::MatchmakingUpdate)>()(profile_index, id, num_slots, available_slots, info, data, status);
	}
}