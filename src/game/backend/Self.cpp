#include "Self.hpp"

#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu
{
	Self::Self() :
	    m_SelfPed(nullptr),
	 // m_SelfPlayer(nullptr),
	    m_Vehicle(nullptr)
	{
	}

	void Self::RunScriptImpl()
	{
		while (g_Running)
		{
			m_SelfPed = Ped(/*Pointers.GetLocalPed()*/ nullptr, PLAYER::PLAYER_PED_ID());
			// m_SelfPlayer = Player(PLAYER::PLAYER_ID());
			if (m_SelfPed.IsValid())
			{
				m_Vehicle = m_SelfPed.GetVehicle();
			}

			ScriptMgr::Yield();
		}
	}
}