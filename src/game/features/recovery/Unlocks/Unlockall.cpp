#include "core/commands/IntCommand.hpp"
#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/backend/Players.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"

namespace YimMenu::Features
{
	namespace ApartmentHeist
	{
		static IntCommand _ApartmentHeistCut1{"apartmentheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut2{"apartmentheistcut2", "Player 2", "Player 2 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut3{"apartmentheistcut3", "Player 3", "Player 3 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut4{"apartmentheistcut4", "Player 4", "Player 4 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base1 = ScriptGlobal(1929794).At(1);
				auto base2 = ScriptGlobal(1931762).At(3008);

				*base1.At(1).As<int*>() = 100 - (_ApartmentHeistCut1.GetState() + _ApartmentHeistCut2.GetState() + _ApartmentHeistCut3.GetState() + _ApartmentHeistCut4.GetState());
				*base1.At(2).As<int*>() = _ApartmentHeistCut2.GetState();
				*base1.At(3).As<int*>() = _ApartmentHeistCut3.GetState();
				*base1.At(4).As<int*>() = _ApartmentHeistCut4.GetState();

				ScriptMgr::Yield(500ms);

				*base2.At(1).As<int*>() = -1 * (*base1.At(1).As<int*>() + *base1.At(2).As<int*>() + *base1.At(3).As<int*>() + *base1.At(4).As<int*>() - 100);
				*base2.At(2).As<int*>() = *base1.At(2).As<int*>();
				*base2.At(3).As<int*>() = *base1.At(3).As<int*>();
				*base2.At(4).As<int*>() = *base1.At(4).As<int*>();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto gpbd = GlobalPlayerBD::Get(); gpbd && Scripts::SafeToModifyFreemodeBroadcastGlobals())
				{
					for (auto& player : Players::GetPlayers())
					{
						gpbd->Entries[player.second.GetId()].HeistCutSelectionStage = 6;
					}
				}
			}
		};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_HEIST_PLANNING_STAGE", -1);
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				*ScriptLocal("fm_mission_controller"_J, 12216).At(24).As<int*>() = 7;
				*ScriptLocal("fm_mission_controller"_J, 10213).As<int*>() = *ScriptLocal("fm_mission_controller"_J, 10213).As<int*>() | (1 << 9);
			}
		};

		class BunkerResearch : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
                const std::vector<int> Research_ids = {
                    15381, // APC Sam Battery
                    15382, // Ballistic Equipment
                    15428, // Half-track 20mm Quad Autocannon
                    15429, // Weaponized Tampa Dual Remote Minigun
                    15430, // Weaponized Tampa Rear-Firing Mortar
                    15431, // Weaponized Tampa Front Missile Launchers
                    15491, // Weaponized Tampa Heavy Chassis Upgrade
                    15432, // Dune FAV 40mm Grenade Launcher
                    15433, // Dune FAV 7.62mm Minigun
                    15434, // Insurgent Pick-Up Custom .50 Cal Minigun
                    15435, // Insurgent Pick-Up Custom Heavy Armor Plating
                    15436, // Technical Custom 7.62mm Minigun
                    15437, // Technical Custom Ram-bar
                    15438, // Technical Custom Brute-bar
                    15439, // Technical Custom Heavy Chassis Upgrade
                    15447, // Oppressor Missile Launchers
                    15448, // Fractal Livery Set
                    15449, // Digital Livery Set
                    15450, // Geometric Livery Set
                    15451, // Nature Reserve Livery Set
                    15452, // Naval Battle Livery Set
                    15453, // Anti-Aircraft Trailer Dual 20mm Flak
                    15454, // Anti-Aircraft Trailer Homing Missile Battery
                    15455, // Mobile Operations Center Rear Turrets
                    15456, // Incendiary Rounds
                    15457, // Hollow Point Rounds
                    15458, // Armor Piercing Rounds
                    15459, // Full Metal Jacket Rounds
                    15460, // Explosive Rounds
                    15461, // Pistol Mk II Mounted Scope
                    15462, // Pistol Mk II Compensator
                    15463, // SMG Mk II Holographic Sight
                    15464, // SMG Mk II Heavy Barrel
                    15465, // Heavy Sniper Mk II Night Vision Scope
                    15466, // Heavy Sniper Mk II Thermal Scope
                    15467, // Heavy Sniper Mk II Heavy Barrel
                    15468, // Combat MG Mk II Holographic Sight
                    15469, // Combat MG Mk II Heavy Barrel
                    15470, // Assault Rifle Mk II Holographic Sight
                    15471, // Assault Rifle Mk II Heavy Barrel
                    15472, // Carbine Rifle Mk II Holographic Sight
                    15473, // Carbine Rifle Mk II Heavy Barrel
                    15474, // Proximity Mines
                    15492, // Brushstroke Camo Mk II Weapon Livery
                    15493, // Skull Mk II Weapon Livery
                    15494, // Sessanta Nove Mk II Weapon Livery
                    15495, // Perseus Mk II Weapon Livery
                    15496, // Leopard Mk II Weapon Livery
                    15497, // Zebra Mk II Weapon Livery
                    15498, // Geometric Mk II Weapon Livery
                    15499, // Boom! Mk II Weapon Livery
                };
                for (int id : Research_ids)
                {
                    Stats::SetPackedBool(id, TRUE); 
                }
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				*ScriptLocal("fm_mission_controller"_J, 20387).At(1725).At(1).As<int*>() = 80;
				*ScriptLocal("fm_mission_controller"_J, 20387).As<int*>() = 12;
				*ScriptLocal("fm_mission_controller"_J, 29006).At(1).As<int*>() = 99999;
				*ScriptLocal("fm_mission_controller"_J, 32462).At(1).At(68).As<int*>() = 99999;

				// TODO: find a way of getting current heist info so that InstantFinishPacific can be implemented here conditionally.
			}
		};

		class InstantFinishPacific : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				*ScriptLocal("fm_mission_controller"_J, 20387).At(2686).As<int*>() = 1875000;
				*ScriptLocal("fm_mission_controller"_J, 20387).At(1062).As<int*>() = 5;
				*ScriptLocal("fm_mission_controller"_J, 20387).As<int*>() = 12;
				*ScriptLocal("fm_mission_controller"_J, 29006).At(1).As<int*>() = 99999;
				*ScriptLocal("fm_mission_controller"_J, 32462).At(1).At(68).As<int*>() = 99999;
			}
		};

		static BunkerResearch _UnlockBunkerreSearch{"unlockbunkerresearch", "Unlock Bunker Research", "Unlocks all Bunker Research Items"};
	}
}