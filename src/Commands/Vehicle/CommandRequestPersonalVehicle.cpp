#include "Commands/Command.hpp"
#include "Vehicle/PersonalVehicles.hpp"
#include "Core/Pointers.hpp"

namespace YimMenu
{
	class RequestPersonalVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			PersonalVehicles::GetCurrent()->Request();
		}
	};

	static RequestPersonalVehicle _RequestPersonalVehicle{"requestpv", "Request Personal Vehicle", "Requests your current Personal Vehicle."};
}