#pragma once
#include "Entity.hpp"
#include "Ped.hpp"
#include "Player.hpp"
#include "Vehicle.hpp"

namespace YimMenu
{
	class Self
	{
		Ped m_SelfPed;
		Player m_SelfPlayer;
		Vehicle m_Vehicle;

	public:
		static Ped GetPed()
		{
			return GetInstance().m_SelfPed;
		}

		static Player GetPlayer()
		{
			return GetInstance().m_SelfPlayer;
		}

		static Vehicle GetVehicle()
		{
			return GetInstance().m_Vehicle;
		}

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static void Update()
		{
			GetInstance().UpdateImpl();
		}

	private:
		Self();
		void RunScriptImpl();
		void UpdateImpl();

		static Self& GetInstance()
		{
			static Self Instance;
			return Instance;
		}
	};
}