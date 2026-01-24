#include <string>
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu::Features
{

	class NightClubPopularity : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			Stats::SetInt("MPX_CLUB_POPULARITY", 1000); // Nightclub Popularity
		}
	};

	class SupplyCooldownBypass : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			*ScriptGlobal(262145).At(18857).As<int*>() = 0; // BIKER_PURCHASE_SUPPLIES_DELAY
			*ScriptGlobal(262145).At(21367).As<int*>() = 0; // GR_PURCHASE_SUPPLIES_DELAY
		}

		virtual void OnDisable() override
		{
			*ScriptGlobal(262145).At(18857).As<int*>() = 600; // BIKER_PURCHASE_SUPPLIES_DELAY
			*ScriptGlobal(262145).At(21367).As<int*>() = 600; // GR_PURCHASE_SUPPLIES_DELAY
		}
	};

	class ResupplyBusiness : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			*ScriptGlobal(1673814).At(1).At(0).As<int*>() = 1; // Cash
			*ScriptGlobal(1673814).At(1).At(1).As<int*>() = 1; // Document Forge
			*ScriptGlobal(1673814).At(1).At(2).As<int*>() = 1; // Weed Farm
			*ScriptGlobal(1673814).At(1).At(3).As<int*>() = 1; // Meth Lab
			*ScriptGlobal(1673814).At(1).At(4).As<int*>() = 1; // Cocaine Lockup
			*ScriptGlobal(1673814).At(1).At(5).As<int*>() = 1; // Bunker
			*ScriptGlobal(1673814).At(1).At(6).As<int*>() = 1; // Acid Lab
		}
	};

	class EnforceEasiestMission : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto thread = Scripts::FindScriptThread("gb_biker_contraband_sell"_J);
			if (!thread)
				return;

			// epctLocal_731.f_17 -> mission / vehicle selector
			constexpr int kMissionTypeLocal = 731 + 17; // = 748

			auto missionType = ScriptLocal(thread, kMissionTypeLocal).As<int*>();
			if (!missionType)
				return;

			// Force "1 Big Truck" (mission type 0)
			if (*missionType != 0)
			{
				*missionType = 0;
			}
		}
	};

	class HangerResupply : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				if (*ScriptGlobal(2655288).As<int*>() == -1)
				{
					Notifications::Show("Hangar Resupply", "Session not ready. Try again in a moment.", NotificationType::Error);
					return;
				}
				Notifications::Show("Hangar Resupply", "Hangar resupply started.");
				while (true)
				{
					int currentStock = *ScriptGlobal(1845299 + 1 + 260 + 304 + 3).As<int*>();

					if (currentStock >= 50)
					{
						Notifications::Show("Hangar Resupply", "Hangar fully stocked (50 crates).");
						break;
					}
					Stats::SetPackedBool(36828, true);

					ScriptMgr::Yield(30000ms);
				}
			});
		}
	};

	class WarehouseResupply : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				if (*ScriptGlobal(2655288).As<int*>() == -1)
				{
					Notifications::Show("Warehouse Resupply", "Session not ready. Try again in a moment.", NotificationType::Error);
					return;
				}
				Notifications::Show("Warehouse Resupply", "Warehouse resupply started.");
				while (true)
				{
					int currentStock = *ScriptGlobal(1845299 + 1 + 260 + 128 + 1).At(0, 3).As<int*>();

					if (currentStock >= 111)
					{
						Notifications::Show("Warehouse Resupply", "Warehouse fully stocked (111 crates).");
						break;
					}

					Stats::SetPackedBool(32359, true);
					Stats::SetPackedBool(32363, true);

					ScriptMgr::Yield(30000ms);
				}
			});
		}
	};

	class SalvageyardPopularity : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			Stats::SetPackedInt(51051, 100); // Salvage Yard Popularity
		}
	};

	class MoneyfrontHeatremove : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			Stats::SetPackedInt(24924, 0); // Money Fronts Business Heat
			Stats::SetPackedInt(24925, 0);
			Stats::SetPackedInt(24926, 0);
		}
	};



	static NightClubPopularity _NightClubPopularity{"nightclubpopularity", "Max Nightclub Popularity", "Sets Nightclub Popularity to 1000"};
	static SupplyCooldownBypass _SupplyCooldownBypass{"removeresupplycooldown", "Remove ReSupply Cooldown", "Removes Resupply Cooldown"};
	static ResupplyBusiness _resupplybusiness{"resupplybusiness", "Resupply Business", "Resupply all Business"};
	static EnforceEasiestMission _EnforceEasiestMission{"enforceeasiestmission", "Enforce Easiest Mission", "Enforces the easiest mission type for Biker Sell Missions"};
	static HangerResupply _HangerResupply{"hangerresupply", "Resupply Hanger Supplies", "Easyway to resupply hanger supplies"};
	static WarehouseResupply _WarehouseResupply{"warehouseresupply", "Resupply Warehouse Supplies", "Easyway to resupply warehouse"};
	static SalvageyardPopularity _SalvageyardPopularity{"salvageyardpopularity", "Max Salvage Yard Popularity", "set Salvage Yard Popularity to 100"};
	static MoneyfrontHeatremove _MoneyfromHeatremove{"moneyfrontheatremove", "Remove Money Front Heat", "Set Money Front Heat to 0"};
}