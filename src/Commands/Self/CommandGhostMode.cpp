#include "Commands/LoopedCommand.hpp"
#include "Scripting/Natives.hpp"
#include "World/Self.hpp"

namespace YimMenu::Features
{
	// Ported from real Stand's own CommandGhost (menu name "Ghost",
	// internal names reducedcollision/ghostmode - Movement's own
	// "Reduced Collision", distinct from No Collision/"Ghost Ride" -
	// see CommandNoCollision.cpp): shrinks the ped's own collision
	// capsule to (near) nothing rather than disabling collision
	// outright, so you still physically exist but can squeeze through
	// most gaps/objects/peds.
	class GhostMode : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			PED::SET_PED_CAPSULE(Self::GetPed().GetHandle(), 1.175494e-38f);
		}

		virtual void OnDisable() override
		{
			if (!Self::GetPed())
				return;

			// 0.25 is the commonly-documented default ped capsule radius -
			// Stand's own source (onChangeToggleScriptTickEventHandler,
			// a helper this project doesn't have) never shows its actual
			// reset value directly, so this is inferred, not confirmed
			// against Stand's own behaviour.
			PED::SET_PED_CAPSULE(Self::GetPed().GetHandle(), 0.25f);
		}
	};

	static GhostMode _GhostMode{"ghostmode", "Ghost", "Shrinks your collision so you can pass through gaps"};
}
