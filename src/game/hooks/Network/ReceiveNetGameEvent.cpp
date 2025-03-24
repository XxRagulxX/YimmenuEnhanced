#include "core/util/Joaat.hpp"
#include "game/backend/Self.hpp"
#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/CNetGamePlayer.hpp"
#include "types/network/netGameEvent.hpp"
#include "types/rage/datBitBuffer.hpp"

namespace YimMenu::Hooks
{
	static void SendEventAck(rage::netEventMgr* event_mgr, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t seq_id, uint32_t event_index, uint32_t event_handled_bits, rage::netGameEvent::Type type)
	{
		if (source_player->m_PlayerIndex != 255 && !Pointers.EventAck(0x778LL * source_player->m_PlayerIndex + (intptr_t)event_mgr + 0x2C408, target_player, event_index, event_handled_bits))
		{
			Pointers.SendEventAck(event_mgr, source_player);
			Pointers.EventAck((intptr_t)event_mgr + 0x2C408 + 0x778LL * source_player->m_PlayerIndex, target_player, event_index, event_handled_bits);
		}
		*reinterpret_cast<std::uint16_t*>(0x118LL * (uint64_t)type + (uint64_t)event_mgr + 4 * source_player->m_PlayerIndex + 0x458) = seq_id;
	}

	bool ShouldAllowNetEvent(Player source, rage::netGameEvent::Type type, rage::datBitBuffer& buffer)
	{
		switch (type)
		{
		case rage::netGameEvent::Type::WEAPON_DAMAGE_EVENT:
		{
			uint8_t damage_type  = buffer.Read<uint8_t>(2);
			uint32_t weapon_type = buffer.Read<uint32_t>(32);

			if (weapon_type == "WEAPON_TRANQUILIZER"_J)
			{
				LOG(INFO) << "this has been blocked from " << source.GetName();
				//player.AddDetection();
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::SCRIPTED_GAME_EVENT:
		{
			int64_t args[54]{};
			uint32_t args_size = buffer.Read<uint32_t>(32);

			if (args_size > sizeof(args))
				return false;

			buffer.ReadArray(args, 8 * args_size);

			if (!Network::HandleScriptedGameEvent(source, args, args_size))
				return false;

			break;
		}
		default: break;
		}

		return true;
	}

	void Network::ReceiveNetGameEvent(rage::netEventMgr* mgr, rage::netGameEvent* event, rage::datBitBuffer* buffer, CNetGamePlayer* src, CNetGamePlayer* dst, std::uint16_t seq_id, std::uint32_t a7, int a8)
	{
		if (!ShouldAllowNetEvent(src, event->m_Type, *buffer))
			return SendEventAck(mgr, src, dst, seq_id, a7, a8, event->m_Type);

		BaseHook::Get<Network::ReceiveNetGameEvent, DetourHook<decltype(&Network::ReceiveNetGameEvent)>>()->Original()(mgr, event, buffer, src, dst, seq_id, a7, a8);
	}
}