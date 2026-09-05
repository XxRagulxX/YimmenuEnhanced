#include "Commands/Command.hpp"
#include "World/Self.hpp"

namespace YimMenu::Features
{
	class RefillArmour : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().SetArmour(Self::GetPlayer().GetMaxArmour());
		}
	};

	static RefillArmour _RefillArmour{"refillarmour", "Refill Armour", "Restores your armour to maximum"};
}
