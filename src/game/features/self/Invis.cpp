#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class Invis : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPed())
			{
				Self::GetPed().SetVisible(false);
				Self::GetPlayer().SetVisibleLocally(true);
			}
		}

		virtual void OnDisable() override
		{
			if (Self::GetPed())
			{
				Self::GetPed().SetVisible(true);
				Self::GetPlayer().SetVisibleLocally(false);
			}
		}
	};

	static Invis _Invis{"invis", "Invisibility", "Be invisible"};
}