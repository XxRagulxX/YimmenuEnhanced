#include "Commands/Command.hpp"
#include "World/Self.hpp"

namespace YimMenu::Features
{
	class ClearDamage : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPed().ClearDamage();
		}
	};

	static ClearDamage _ClearDamage{"cleardamage", "Clear Damage", "Clears all the dirt and blood on you."};
}