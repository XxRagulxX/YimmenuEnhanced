#include "core/hooking/DetourHook.hpp"
#include "game/backend/Players.hpp"
#include "game/frontend/ChatDisplay.hpp"
#include "game/hooks/Hooks.hpp"
#include "types/network/netEvent.hpp"
#include "types/network/netMessage.hpp"
#include "types/rage/datBitBuffer.hpp"
#include "core/frontend/widgets/imgui_colors.h"

namespace YimMenu::Hooks
{
	static std::optional<rage::netMessage::Type> ReadType(rage::datBitBuffer& buffer)
	{
		if (buffer.Read<int>(14) != 0x3246)
			return std::nullopt;

		auto extended = buffer.Read<bool>(1);
		return buffer.Read<rage::netMessage::Type>(extended ? 16 : 8);
	}

	void Network::ReceiveNetMessage(void* a1, rage::netConnectionManager* mgr, rage::netEvent* event)
	{
		if (!g_Running)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		if (event->GetEventType() != rage::netEvent::Type::FrameReceived)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		// TODO: port security ID stuff from V1
		auto fr_evt = reinterpret_cast<rage::netEventFrameReceived*>(event);
		rage::datBitBuffer buffer(fr_evt->m_Data, fr_evt->m_Length, true);
		
		rage::netMessage::Type type = ReadType(buffer).value_or(rage::netMessage::Type::Invalid);

		switch (type)
		{
		case rage::netMessage::Type::TextMessage:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);
			if (player)
			{
				char msg[256]{};
				buffer.ReadString(msg, sizeof(msg)); // we don't need the rest
				ChatDisplay::Show(player.GetName(), msg, ImGui::Colors::LightBlue);
			}
			break;
		}
		default: 
			break;
		}

		BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);
	}
}