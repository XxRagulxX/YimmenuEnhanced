#include "game/commands/PlayerCommand.hpp"
#include "types/fx/ExplosionType.hpp"

namespace YimMenu::Features
{
	class Explode : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			player.GetPed().Explode(ExplosionType::ORBITAL_CANNON, 900.f);
		}
	};

	static Explode _Explode{"explode", "Explode", "Blows the player up"};
}