#include "Commands/Command.hpp"
#include "World/Self.hpp"

namespace StandEnhanced::Features
{
	class RepairVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (Self::GetVehicle())
				Self::GetVehicle().Fix();
		}
	};

	static RepairVehicle _RepairVehicle{"repairvehicle", "Repair Vehicle", "Fixes any damage to your current vehicle"};
}