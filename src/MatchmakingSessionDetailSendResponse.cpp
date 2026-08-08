#include "Hooks.hpp"
#include "DetourHook.hpp"
#include "CustomMatchmaking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingSessionDetailSendResponse(rage::netConnectionManager* mgr, void* request_frame, rage::rlSessionDetailMsg* msg)
	{
		CustomMatchmaking::OnSendSessionDetailResponse(msg);
		return BaseHook::Get<Matchmaking::MatchmakingSessionDetailSendResponse, DetourHook>()->Original<decltype(&Matchmaking::MatchmakingSessionDetailSendResponse)>()(mgr, request_frame, msg);
	}
}