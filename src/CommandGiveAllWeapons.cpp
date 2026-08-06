#include "Command.hpp"
#include "Self.hpp"
#include "WeaponsHashes.hpp"

namespace YimMenu::Features
{
	class GiveAllWeapons : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto weapon : g_WeaponHashes)
				Self::GetPed().GiveWeapon(weapon);
		}
	};

	static GiveAllWeapons _GiveAllWeapons{"giveallweapons", "Give All Weapons", "Gives you all weapons"};
}