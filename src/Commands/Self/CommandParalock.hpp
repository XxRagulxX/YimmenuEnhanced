#pragma once
#include "Commands/Widgets/CommandListSelect.hpp"
#include "Commands/Widgets/CommandTickDispatch.hpp"

#include "Ped/PedConfigFlag.hpp"
#include "Scripting/Natives.hpp"
#include "Util/Joaat.hpp"
#include "World/Self.hpp"

namespace Stand
{
	class CommandParalock : public CommandListSelect
	{
	public:
		explicit CommandParalock(CommandList* parent) :
		    CommandListSelect(parent,
		        LIT("Paralock"),
		        CMDNAMES("paralock"),
		        LIT("Force your parachute availability on or off"),
		        {{0, LIT("Off")}, {1, LIT("Full")}, {2, LIT("Empty")}},
		        0)
		{
		}

		void onChange(Click& click, int prev_value) override
		{
			CommandListSelect::onChange(click, prev_value);

			if (value == 0)
				CommandTickDispatch::RemoveCommand(this);
			else
				CommandTickDispatch::AddCommand(this);
		}

		void onTick() override
		{
			if (!Stand::Self::GetPed())
				return;

			switch (value)
			{
			case 1:
				if (auto player = Stand::Self::GetPlayer())
					PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player.GetId());
				if (!Stand::Self::GetPed().HasWeapon("GADGET_PARACHUTE"_J))
					Stand::Self::GetPed().GiveWeapon("GADGET_PARACHUTE"_J);
				break;

			case 2:
				Stand::Self::GetPed().RemoveWeapon("GADGET_PARACHUTE"_J);
				Stand::Self::GetPed().SetConfigFlag(PedConfigFlag::HasReserveParachute, false);
				break;

			default:
				break;
			}
		}

		~CommandParalock() override
		{
			CommandTickDispatch::RemoveCommand(this);
		}
	};
}

namespace Stand::Features
{
	Stand::CommandParalock& GetCommandParalock();
}
