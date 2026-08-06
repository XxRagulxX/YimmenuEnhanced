#include "Command.hpp"
#include "Self.hpp"

namespace YimMenu::Features
{
	class Suicide : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPed().SetInvincible(false);
			Self::GetPed().SetHealth(0);
		}
	};

	static Suicide _Suicide{"suicide", "Suicide", "Kills you"};
}