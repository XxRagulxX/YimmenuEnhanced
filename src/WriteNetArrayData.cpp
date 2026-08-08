#include "DetourHook.hpp"
#include "Hooks.hpp"
#include "Pointers.hpp"
#include "netArrayHandler.hpp"
#include "GSBD.hpp"
#include "Player.hpp"
#include "PlayerData.hpp"

namespace YimMenu::Hooks
{
	class FreemodeStateKick
	{
		bool m_Enabled;
		eFreemodeState m_LastState;

	public:
		FreemodeStateKick(Player player, void* array) :
			m_Enabled(), m_LastState()
		{
			if (player.GetData().m_RunFreemodeStateKick && array == GSBD::Get())
			{
				m_Enabled = true;
				m_LastState = GSBD::Get()->FreemodeState;
				GSBD::Get()->FreemodeState = eFreemodeState::CLOSING;
				Pointers.NetArrayCachedDataPatch->Apply();
			}
		}

		~FreemodeStateKick()
		{
			if (m_Enabled)
			{
				GSBD::Get()->FreemodeState = m_LastState;
				Pointers.NetArrayCachedDataPatch->Restore();
			}
		}
	};

	int Hooks::Spoofing::WriteNetArrayData(rage::netArrayHandler* _this, CNetGamePlayer* target, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent)
	{
		FreemodeStateKick kick(target, static_cast<void*>(_this->m_Array));

		return BaseHook::Get<Spoofing::WriteNetArrayData, DetourHook>()->Original<decltype(&Spoofing::WriteNetArrayData)>()(_this, target, bit_buffer, counter, elem_start, silent);
	}
}