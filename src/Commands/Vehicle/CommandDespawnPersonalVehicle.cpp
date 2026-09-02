#include "Commands/Command.hpp"
#include "Vehicle/PersonalVehicles.hpp"
#include "Core/Pointers.hpp"

namespace YimMenu
{
	class DespawnPersonalVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			PersonalVehicles::GetCurrent()->Despawn();
		}
	};

	static DespawnPersonalVehicle _DespawnPersonalVehicle{"despawnpv", "Despawn Personal Vehicle", "Returns your current Personal Vehicle to storage."};
}