#include "Commands/LoopedCommand.hpp"
#include "World/Self.hpp"

namespace YimMenu::Features
{
	// Real Stand's own CommandAutoHeal (internal name "demigodmode") tops
	// health/armour up to max the moment either drops below it, via a
	// one-shot script-tick handler registered from its own onChange - not
	// a continuous per-frame poll. This project has no such "run once,
	// register a handler that keeps re-checking a captured condition"
	// primitive; LoopedCommand's own OnTick (every tick, while on) is the
	// idiom every other continuous self-effect in this codebase already
	// uses (see Godmode.cpp/CommandNoRagdoll.cpp), so that's what this
	// uses too - same end result (health/armour never sit below max
	// while this is on), just via this project's own tick shape rather
	// than Stand's.
	class AutoHeal : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			const auto health = Self::GetPed().GetHealth();
			const auto maxHealth = Self::GetPed().GetMaxHealth();
			if (health > 0 && health < maxHealth)
				Self::GetPed().SetHealth(maxHealth);

			const auto maxArmour = Self::GetPlayer().GetMaxArmour();
			if (Self::GetPed().GetArmour() != maxArmour)
				Self::GetPed().SetArmour(maxArmour);
		}
	};

	static AutoHeal _AutoHeal{"autoheal", "Auto Heal", "Keeps your health and armour topped up"};
}
