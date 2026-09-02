#include "Commands/Command.hpp"
#include "World/Self.hpp"
#include "Weapons/WeaponsHashes.hpp"

namespace YimMenu::Features
{
	class GiveMaxAmmo : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto weapon : g_WeaponHashes)
			{
				Self::GetPed().SetMaxAmmoForWeapon(weapon);
			}
		}
	};

	static GiveMaxAmmo _GiveMaxAmmo{"givemaxammo", "Give Max Ammo", "Refills your ammo to max."};
}