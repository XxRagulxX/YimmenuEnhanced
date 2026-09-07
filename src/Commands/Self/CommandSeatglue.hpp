#pragma once
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandToggle.hpp"

#include "Scripting/Natives.hpp"
#include "World/Self.hpp"

namespace Stand
{
	class CommandSeatglue : public CommandToggle
	{
	public:
		explicit CommandSeatglue(CommandList* parent) :
		    CommandToggle(parent, LIT("Glued To Seats"), CMDNAMES("seatbelt", "seatglue"), LIT("Stops you being knocked out of a vehicle's seat"))
		{
		}

		void onEnable(Click& click) override
		{
			CommandTickDispatch::AddCommand(this);
			onTick();
		}

		void onDisable(Click& click) override
		{
			CommandTickDispatch::RemoveCommand(this);
			Restore();
		}

		void onTick() override
		{
			auto ped = Stand::Self::GetPed();
			if (!ped)
				return;

			if (ped.GetVehicle())
			{
				PED::SET_PED_CAN_RAGDOLL(ped.GetHandle(), false);
				Stand::Self::GetPlayer().SetFallDistanceOverride(1000.0f);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped.GetHandle(), 1);
			}
			else
			{
				Restore();
			}
		}

		~CommandSeatglue() override
		{
			CommandTickDispatch::RemoveCommand(this);
		}

	private:
		void Restore()
		{
			auto ped = Stand::Self::GetPed();
			if (!ped)
				return;

			PED::SET_PED_CAN_RAGDOLL(ped.GetHandle(), true);
			Stand::Self::GetPlayer().SetFallDistanceOverride(-1.0f);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped.GetHandle(), 0);
		}
	};
}

namespace Stand::Features
{
	Stand::CommandSeatglue& GetCommandSeatglue();
}
