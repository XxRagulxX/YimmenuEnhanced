#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class InfiniteClip : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(Self::GetPed().GetHandle(), TRUE);
		}

		virtual void OnDisable() override
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(Self::GetPed().GetHandle(), FALSE);
		}
	};

	static InfiniteClip _InfiniteClip{"infiniteclip", "Infinite Clip", "Have an endless clip in your gun"};
}