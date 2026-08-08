#include "Hooks.hpp"
#include "DetourHook.hpp"
#include "CustomMatchmaking.hpp"
#include "Hooking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingSessionDetailSendResponse(rage::netConnectionManager* mgr, void* request_frame, rage::rlSessionDetailMsg* msg)
	{
		CustomMatchmaking::OnSendSessionDetailResponse(msg);
		return Hooking::Get<Matchmaking::MatchmakingSessionDetailSendResponse>()->Original<decltype(&Matchmaking::MatchmakingSessionDetailSendResponse)>()(mgr, request_frame, msg);
	}
}