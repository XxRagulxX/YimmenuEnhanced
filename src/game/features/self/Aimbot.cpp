#include "core/commands/BoolCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Pools.hpp"
#include "game/pointers/Pointers.hpp"

#include <set>

namespace YimMenu::Features
{
	class Aimbot : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		std::set<int> killed_peds;

		virtual void OnEnable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Apply();
			Pointers.GetAssistedAimTypePatch->Apply();
			killed_peds.clear();
		}

		virtual void OnTick() override
		{
			for (Ped ped : Pools::GetPeds())
			{
				int handle = ped.GetHandle();
				if (!killed_peds.contains(handle) && !ped.IsPlayer() && ped.IsDead()
				    && ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(handle, Self::GetPed().GetHandle(), false))
				{
					killed_peds.insert(handle);
					PAD::DISABLE_CONTROL_ACTION(0, 25, true);
				}
			}
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Restore();
			Pointers.GetAssistedAimTypePatch->Restore();
			killed_peds.clear();
		}
	};

	class AimbotAimForHead : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.GetLockOnPosPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.GetLockOnPosPatch->Restore();
		}
	};

	class AimbotTargetDrivers : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Restore();
		}
	};

	static Aimbot _Aimbot{"aimbot", "Aimbot", "Locks on to enemies and other players"};
	static AimbotAimForHead _AimbotAimForHead{"aimbotaimforhead", "Aim For Head", "Targets the head when locking on to enemies and other players"};
	static AimbotTargetDrivers _AimbotTargetDrivers{"aimbottargetdrivers", "Target Drivers", "Allows aimbot to lock on to enemies and other players in vehicles"};
}