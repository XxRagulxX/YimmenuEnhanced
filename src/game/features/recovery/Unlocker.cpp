//#include "core/commands/BoolCommand.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/backend/Tunables.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Features
{
	class BunkerResearch : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetPackedBool(15381, TRUE); // APC Sam Battery
			Stats::SetPackedBool(15382, TRUE); // Ballistic Equipment
			Stats::SetPackedBool(15428, TRUE); // Half-track 20mm Quad Autocannon
			Stats::SetPackedBool(15429, TRUE); // Weaponized Tampa Dual Remote Minigun
			Stats::SetPackedBool(15430, TRUE); // Weaponized Tampa Rear-Firing Mortar
			Stats::SetPackedBool(15431, TRUE); // Weaponized Tampa Front Missile Launchers
			Stats::SetPackedBool(15432, TRUE); // Dune FAV 40mm Grenade Launcher
			Stats::SetPackedBool(15433, TRUE); // Dune FAV 7.62mm Minigun
			Stats::SetPackedBool(15434, TRUE); // Insurgent Pick-Up Custom .50 Cal Minigun
			Stats::SetPackedBool(15435, TRUE); // Insurgent Pick-Up Custom Heavy Armor Plating
			Stats::SetPackedBool(15436, TRUE); // Technical Custom 7.62mm Minigun
			Stats::SetPackedBool(15437, TRUE); // Technical Custom Ram-bar
			Stats::SetPackedBool(15438, TRUE); // Technical Custom Brute-bar
			Stats::SetPackedBool(15439, TRUE); // Technical Custom Heavy Chassis Upgrade
			Stats::SetPackedBool(15447, TRUE); // Oppressor Missile Launchers
			Stats::SetPackedBool(15448, TRUE); // Fractal Livery Set
			Stats::SetPackedBool(15449, TRUE); // Digital Livery Set
			Stats::SetPackedBool(15450, TRUE); // Geometric Livery Set
			Stats::SetPackedBool(15451, TRUE); // Nature Reserve Livery Set
			Stats::SetPackedBool(15452, TRUE); // Naval Battle Livery Set
			Stats::SetPackedBool(15453, TRUE); // Anti-Aircraft Trailer Dual 20mm Flak
			Stats::SetPackedBool(15454, TRUE); // Anti-Aircraft Trailer Homing Missile Battery
			Stats::SetPackedBool(15455, TRUE); // Mobile Operations Center Rear Turrets
			Stats::SetPackedBool(15456, TRUE); // Incendiary Rounds
			Stats::SetPackedBool(15457, TRUE); // Hollow Point Rounds
			Stats::SetPackedBool(15458, TRUE); // Armor Piercing Rounds
			Stats::SetPackedBool(15459, TRUE); // Full Metal Jacket Rounds
			Stats::SetPackedBool(15460, TRUE); // Explosive Rounds
			Stats::SetPackedBool(15461, TRUE); // Pistol Mk II Mounted Scope
			Stats::SetPackedBool(15462, TRUE); // Pistol Mk II Compensator
			Stats::SetPackedBool(15463, TRUE); // SMG Mk II Holographic Sight
			Stats::SetPackedBool(15464, TRUE); // SMG Mk II Heavy Barrel
			Stats::SetPackedBool(15465, TRUE); // Heavy Sniper Mk II Night Vision Scope
			Stats::SetPackedBool(15466, TRUE); // Heavy Sniper Mk II Thermal Scope
			Stats::SetPackedBool(15467, TRUE); // Heavy Sniper Mk II Heavy Barrel
			Stats::SetPackedBool(15468, TRUE); // Combat MG Mk II Holographic Sight
			Stats::SetPackedBool(15469, TRUE); // Combat MG Mk II Heavy Barrel
			Stats::SetPackedBool(15470, TRUE); // Assault Rifle Mk II Holographic Sight
			Stats::SetPackedBool(15471, TRUE); // Assault Rifle Mk II Heavy Barrel
			Stats::SetPackedBool(15472, TRUE); // Carbine Rifle Mk II Holographic Sight
			Stats::SetPackedBool(15473, TRUE); // Carbine Rifle Mk II Heavy Barrel
			Stats::SetPackedBool(15474, TRUE); // Proximity Mines
			Stats::SetPackedBool(15491, TRUE); // Weaponized Tampa Heavy Chassis Upgrade
			Stats::SetPackedBool(15492, TRUE); // Brushstroke Camo Mk II Weapon Livery
			Stats::SetPackedBool(15493, TRUE); // Skull Mk II Weapon Livery
			Stats::SetPackedBool(15494, TRUE); // Sessanta Nove Mk II Weapon Livery
			Stats::SetPackedBool(15495, TRUE); // Perseus Mk II Weapon Livery
			Stats::SetPackedBool(15496, TRUE); // Leopard Mk II Weapon Livery
			Stats::SetPackedBool(15497, TRUE); // Zebra Mk II Weapon Livery
			Stats::SetPackedBool(15498, TRUE); // Geometric Mk II Weapon Livery
			Stats::SetPackedBool(15499, TRUE); // Boom! Mk II Weapon Livery
			Notifications::Show("Bunker Research", "Bunker research has been unlocked", NotificationType::Success);
		}
	};

    class UnlockClothing : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Notifications::Show("Clothing", "Unlocking Clothing InProgress. Please wait until Completion", NotificationType::Info);
			*ScriptGlobal(262145).At(23812).As<int*>() = 1;
			int ids[] = {
				3593, 3608, 3616, 3750, 6097, 6106, 6169, 6181, 7475, 7551, 9443,
				15412, 15708, 15710, 15717, 15735, 15739, 15741, 15743, 18125, 22058,
				22063, 22150, 22152, 22159, 22162, 22166, 22170, 22172, 22174, 25000,
				25005, 25006, 26968, 26969, 27068, 27082, 27084, 28231, 28254, 28255, 
				30240, 30254, 30407, 31736, 31830, 31835, 31840, 31843, 31845, 31850, 
				31855, 31857, 31858, 31865, 31870, 31874, 31875, 31878, 31879, 31880, 
				31884, 31885, 31889, 31890, 31892, 31894, 31895, 31899, 31900, 31905, 
				31915, 31920, 31925, 31928, 31930, 31932, 31935, 31937, 31940, 31942, 
				31945, 31947, 31952, 31955, 31957, 31960, 31962, 31965, 31967, 31970, 
				31972, 31977, 31980, 31982, 31985, 31987, 31990, 31992, 31995, 32000, 
				32002, 32005, 32007, 32010, 32012, 32015, 32018, 32084, 32104, 32114, 
				32124, 32134, 32144, 32154, 32164, 32174, 32224, 32273, 32275, 32316, 
				32407, 32408, 34372, 34375, 34380, 34382, 34389, 36759, 36763, 36809, 
				42062, 42191, 42211, 42257, 42268, 42286, 42287, 54591, 54623, 54629,
				54651, 24970, 24977, 25348, 25349
			    };
			for (int i = 0; i < sizeof(ids) / sizeof(ids[0]); ++i)
			{
				Stats::SetPackedBool(ids[i], TRUE);
			}
			for (int i = 3783; i <= 3802; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 4257; i <= 4259; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 4262; i <= 4269; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 7467; i <= 7481; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 9426; i <= 9481; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 22124; i <= 22132; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 25244; i <= 25258; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 25265; i <= 25367; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 28171; i <= 28175; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 27184; i <= 27193; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 28185; i <= 28191; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 28197; i <= 28249; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 28393; i <= 28427; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 28447; i <= 28478; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 30254; i <= 30258; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 30355; i <= 30372; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 30418; i <= 30422; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 30429; i <= 30433; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 31760; i <= 31764; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 31827; i <= 32174; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 51215; i <= 51221; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 51234; i <= 51239; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 51240; i <= 51258; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int i = 15562; i <= 15568; i++)
			{
				Stats::SetPackedBool(i, TRUE);
			}
			for (int id = 110; id <= 113; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 3483; id <= 3492; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 3496; id <= 3505; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 3765; id <= 3779; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 3783; id <= 3802; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 4257; id <= 4269; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 4333; id <= 4335; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 6082; id <= 6083; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 6091; id <= 6092; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 6303; id <= 6304; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 6316; id <= 6317; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 7467; id <= 7469; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 7471; id <= 7495; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 7515; id <= 7528; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 7595; id <= 7601; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 9362; id <= 9385; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 9426; id <= 9440; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 9462; id <= 9481; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15389; id <= 15390; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15392; id <= 15396; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15398; id <= 15399; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15402; id <= 15407; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15409; id <= 15410; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15414; id <= 15423; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15425; id <= 15427; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15719; id <= 15721; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 15730; id <= 15732; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 18121; id <= 18125; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 18134; id <= 18137; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 22050; id <= 22051; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 22124; id <= 22132; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 25018; id <= 25021; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 25032; id <= 25099; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 27109; id <= 27115; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 27195; id <= 27197; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 27208; id <= 27211; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 30259; id <= 30289; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 30294; id <= 30295; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 30524; id <= 30557; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 30563; id <= 30583; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 30634; id <= 30637; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 30699; id <= 30701; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 30703; id <= 30704; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31768; id <= 31777; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31779; id <= 31782; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31784; id <= 31790; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31805; id <= 31808; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31827; id <= 31828; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31832; id <= 31833; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31837; id <= 31838; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31847; id <= 31848; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31852; id <= 31853; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31862; id <= 31863; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31867; id <= 31868; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31872; id <= 31873; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31882; id <= 31883; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31887; id <= 31888; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31897; id <= 31898; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31902; id <= 31903; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31907; id <= 31908; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31912; id <= 31913; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31917; id <= 31918; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 31922; id <= 31923; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32020; id <= 32023; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32025; id <= 32028; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32030; id <= 32033; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32035; id <= 32038; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32040; id <= 32043; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32045; id <= 32048; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32050; id <= 32053; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32055; id <= 32058; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32060; id <= 32063; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32065; id <= 32074; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 32307; id <= 32311; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 34394; id <= 34399; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 34401; id <= 34410; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 34505; id <= 34510; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 36703; id <= 36704; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 36717; id <= 36718; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 36737; id <= 36738; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 36751; id <= 36752; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 36768; id <= 36769; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 36774; id <= 36776; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 36782; id <= 36784; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 41885; id <= 41898; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 41902; id <= 41913; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 42193; id <= 42201; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 42203; id <= 42209; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 42213; id <= 42216; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 51248; id <= 51257; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 54572; id <= 54621; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 54625; id <= 54627; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 54631; id <= 54635; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			for (int id = 28232; id <= 28249; ++id)
			{
				Stats::SetPackedBool(id, TRUE);
			}
			Notifications::Show("Clothing", "Unlocking Clothing Completed", NotificationType::Success);
			
		}
	};
    class UnlockAllAwards : public Command
	{
		using Command::Command;
		
		virtual void OnCall() override
		{

            // Victory
            Stats::SetInt("MPX_AWD_FM_DM_WINS", 50);
            Stats::SetInt("MPX_AWD_FMWINAIRRACE", 25);
            Stats::SetInt("MPX_AWD_FMRALLYWONDRIVE", 25);
            Stats::SetInt("MPX_AWD_FMRALLYWONNAV", 25);
            Stats::SetInt("MPX_AWD_FMWINSEARACE", 25);
            Stats::SetInt("MPX_AWD_FM_TDM_WINS", 50);
            Stats::SetInt("MPX_AWD_FM_TDM_MVP", 50);
            Stats::SetInt("MPX_AWD_FM_GTA_RACES_WON", 50);
            Stats::SetInt("MPX_AWD_FMWINRACETOPOINTS", 25);
            Stats::SetBool("MPX_AWD_FMWINCUSTOMRACE", true);
            Stats::SetBool("MPX_AWD_FMKILL3ANDWINGTARACE", true);
            Stats::SetInt("MPX_AWD_RACES_WON", 50);
            Stats::SetInt("MPX_AWD_FM_RACE_LAST_FIRST", 25);
            Stats::SetInt("MPX_AWD_FMHORDWAVESSURVIVE", 10);
            Stats::SetInt("MPX_AWD_FM_TENNIS_WON", 25);
            Stats::SetBool("MPX_AWD_FM_TENNIS_5_SET_WINS", true);
            Stats::SetInt("MPX_MOST_ARM_WRESTLING_WINS", 25);
            Stats::SetBool("MPX_AWD_FMRACEWORLDRECHOLDER", true);
            Stats::SetInt("MPX_AWD_FM_RACES_FASTEST_LAP", 50);
            Stats::SetInt("MPX_AWD_WIN_AT_DARTS", 25);
            Stats::SetBool("MPX_AWD_FM_TENNIS_STASETWIN", true);
            Stats::SetInt("MPX_AWD_FM_SHOOTRANG_TG_WON", 25);
            Stats::SetInt("MPX_AWD_FM_GOLF_WON", 25);
            Stats::SetBool("MPX_AWD_FMWINALLRACEMODES", true);
            Stats::SetInt("MPX_AWD_FM_SHOOTRANG_CT_WON", 25);
            Stats::SetInt("MPX_AWD_WIN_LAST_TEAM_STANDINGS", 50);
            Stats::SetInt("MPX_AWD_WIN_CAPTURE_DONT_DYING", 25);
            Stats::SetInt("MPX_AWD_ONLY_PLAYER_ALIVE_LTS", 50);
            Stats::SetBool("MPX_AWD_FM_SHOOTRANG_GRAN_WON", true);
            Stats::SetInt("MPX_AWD_FM_SHOOTRANG_RT_WON", 25);
            Stats::SetInt("MPX_AWD_KILL_TEAM_YOURSELF_LTS", 25);
            Stats::SetInt("MPX_AWD_WIN_CAPTURES", 50);
            Stats::SetBool("MPX_AWD_FMWINEVERYGAMEMODE", true);


            // General
            Stats::SetInt("MPX_CR_DIFFERENT_DM", 25);
            Stats::SetBool("MPX_AWD_FM25DIFFERENTDM", true);
            Stats::SetInt("MPX_AWD_FMBASEJMP", 25);
            Stats::SetBool("MPX_AWD_FM_GOLF_HOLE_IN_1", true);
            Stats::SetInt("MPX_AWD_FM_TENNIS_ACE", 25);
            Stats::SetBool("MPX_AWD_FMATTGANGHQ", true);
            Stats::SetInt("MPX_CR_DIFFERENT_RACES", 25);
            Stats::SetBool("MPX_AWD_FM25DIFFERENTRACES", true);
            Stats::SetInt("MPX_AWD_PARACHUTE_JUMPS_20M", 25);
            Stats::SetBool("MPX_AWD_FM6DARTCHKOUT", true);
            Stats::SetInt("MPX_AWD_FMBBETWIN", 50000);
            Stats::SetInt("MPX_AWD_LAPDANCES", 25);
            Stats::SetInt("MPX_AWD_FM_GOLF_BIRDIES", 25);
            Stats::SetInt("MPX_AWD_PARACHUTE_JUMPS_50M", 25);
            Stats::SetBool("MPX_AWD_FM25DIFITEMSCLOTHES", true);
            Stats::SetInt("MPX_AWD_FM_CR_DM_MADE", 25);
            Stats::SetInt("MPX_AWD_DROPOFF_CAP_PACKAGES", 100);
            Stats::SetInt("MPX_AWD_PICKUP_CAP_PACKAGES", 100);
            Stats::SetInt("MPX_AWD_FM_CR_RACES_MADE", 25);
            Stats::SetInt("MPX_AWD_NO_HAIRCUTS", 25);
            Stats::SetBool("MPX_AWD_BUY_EVERY_GUN", true);
            Stats::SetInt("MP0_AWD_MENTALSTATE_TO_NORMAL", 50);
            Stats::SetBool("MP0_AWD_FMTATTOOALLBODYPARTS", true);
            Stats::SetInt("MPPLY_AWD_FM_CR_PLAYED_BY_PEEP", 100);
            Stats::SetBool("MP0_AWD_STORE_20_CAR_IN_GARAGES", true);
            Stats::SetInt("MP0_AWD_TRADE_IN_YOUR_PROPERTY", 25);
            Stats::SetInt("MP0_COMPLETEDAILYOBJ", 100);
            Stats::SetInt("MP0_COMPLETEDAILYOBJTOTAL", 100);
            Stats::SetInt("MP0_TOTALDAYCOMPLETED", 100);
            Stats::SetInt("MP0_TOTALWEEKCOMPLETED", 400);
            Stats::SetInt("MP0_TOTALMONTHCOMPLETED", 1800);
            Stats::SetInt("MP0_CONSECUTIVEDAYCOMPLETED", 30);
            Stats::SetInt("MP0_CONSECUTIVEWEEKCOMPLETED", 4);
            Stats::SetInt("MP0_CONSECUTIVEMONTHCOMPLETE", 1);
            Stats::SetInt("MP0_COMPLETEDAILYOBJSA", 100);
            Stats::SetInt("MP0_COMPLETEDAILYOBJTOTALSA", 100);
            Stats::SetInt("MP0_TOTALDAYCOMPLETEDSA", 100);
            Stats::SetInt("MP0_TOTALWEEKCOMPLETEDSA", 400);
            Stats::SetInt("MP0_TOTALMONTHCOMPLETEDSA", 1800);
            Stats::SetInt("MP0_CONSECUTIVEDAYCOMPLETEDSA", 30);
            Stats::SetInt("MP0_CONSECUTIVEWEEKCOMPLETEDSA", 4);
            Stats::SetInt("MP0_CONSECUTIVEMONTHCOMPLETESA", 1);
            Stats::SetInt("MP0_AWD_DAILYOBJCOMPLETEDSA", 100);
            Stats::SetInt("MP0_AWD_DAILYOBJCOMPLETED", 100);
            Stats::SetBool("MP0_AWD_DAILYOBJMONTHBONUS", true);
            Stats::SetBool("MP0_AWD_DAILYOBJWEEKBONUS", true);
            Stats::SetBool("MP0_AWD_DAILYOBJWEEKBONUSSA", true);
            Stats::SetBool("MP0_AWD_DAILYOBJMONTHBONUSSA", true);

            // Vehicle
            Stats::SetInt("MPX_CARS_EXPLODED", 500);
            Stats::SetInt("MPX_AWD_TIME_IN_HELICOPTER", 4);
            Stats::SetInt("MPX_MOST_SPINS_IN_ONE_JUMP", 5);
            Stats::SetBool("MPX_AWD_FMFURTHESTWHEELIE", true);
            Stats::SetBool("MPX_AWD_FMFULLYMODDEDCAR", true);
            Stats::SetInt("MPX_AWD_CARS_EXPORTED", 50);
            Stats::SetInt("MPX_AWD_FMDRIVEWITHOUTCRASH", 30);
            Stats::SetInt("MPX_AIR_LAUNCHES_OVER_40M", 25);
            Stats::SetInt("MPX_MOST_FLIPS_IN_ONE_JUMP", 5);
            Stats::SetInt("MPX_AWD_PASSENGERTIME", 4);

            // Combat
            Stats::SetInt("MPX_AWD_100_HEADSHOTS", 500);
            Stats::SetInt("MPX_AWD_FM_DM_KILLSTREAK", 100);
            Stats::SetBool("MPX_AWD_FMMOSTKILLSGANGHIDE", true);
            Stats::SetBool("MPX_AWD_FMMOSTKILLSSURVIVE", true);
            Stats::SetInt("MPX_AWD_FM_DM_STOLENKILL", 50);
            Stats::SetInt("MPX_KILLS_PLAYERS", 1000);
            Stats::SetInt("MPX_AWD_FMKILLBOUNTY", 25);
            Stats::SetInt("MPX_AWD_FM_DM_TOTALKILLS", 500);
            Stats::SetInt("MPX_AWD_FMREVENGEKILLSDM", 50);
            Stats::SetInt("MPX_PISTOL50_ENEMY_KILLS", 500);
            Stats::SetBool("MPX_AWD_FMKILLSTREAKSDM", true);
            Stats::SetInt("MPX_AWD_FM_DM_3KILLSAMEGUY", 50);
            Stats::SetInt("MPX_AWD_100_KILLS_SMG", 500);
            Stats::SetInt("MPX_CMBTMG_ENEMY_KILLS", 500);
            Stats::SetInt("MPX_UNARMED_ENEMY_KILLS", 50);
            Stats::SetInt("MPX_AWD_CAR_BOMBS_ENEMY_KILLS", 25);
            Stats::SetInt("MPX_AWD_25_KILLS_STICKYBOMBS", 50);
            Stats::SetInt("MPX_ASLTSHTGN_ENEMY_KILLS", 500);
            Stats::SetInt("MPX_ASLTRIFLE_ENEMY_KILLS", 500);
            Stats::SetInt("MPX_GRENADE_ENEMY_KILLS", 50);
            Stats::SetInt("MPX_AWD_KILL_CARRIER_CAPTURE", 100);
            Stats::SetInt("MPX_AWD_NIGHTVISION_KILLS", 100);
            Stats::SetInt("MPX_RPG_ENEMY_KILLS", 500);
            Stats::SetInt("MPX_SNIPERRFL_ENEMY_KILLS", 500);
            Stats::SetInt("MPX_AWD_KILL_PSYCHOPATHS", 100);

			// Apartment Awards
			Stats::SetInt("MPX_AWD_FINISH_HEISTS", 900);
            Stats::SetInt("MPX_MPPLY_WIN_GOLD_MEDAL_HEISTS", 900);
            Stats::SetInt("MPX_AWD_DO_HEIST_AS_MEMBER", 900);
            Stats::SetInt("MPX_AWD_DO_HEIST_AS_THE_LEADER", 900);
            Stats::SetInt("MPX_AWD_FINISH_HEIST_SETUP_JOB", 900);
            Stats::SetInt("MPX_AWD_FINISH_HEIST", 900);
            Stats::SetInt("MPX_HEIST_COMPLETION", 900);
            Stats::SetInt("MPX_HEISTS_ORGANISED", 900);
            Stats::SetInt("MPX_AWD_CONTROL_CROWDS", 900);
            Stats::SetInt("MPX_AWD_WIN_GOLD_MEDAL_HEISTS", 900);
            Stats::SetInt("MPX_AWD_COMPLETE_HEIST_NOT_DIE", 900);
            Stats::SetInt("MPX_HEIST_START", 900);
            Stats::SetInt("MPX_HEIST_END", 900);
            Stats::SetInt("MPX_CUTSCENE_MID_PRISON", 900);
            Stats::SetInt("MPX_CUTSCENE_MID_HUMANE", 900);
            Stats::SetInt("MPX_CUTSCENE_MID_NARC", 900);
            Stats::SetInt("MPX_CUTSCENE_MID_ORNATE", 900);
            Stats::SetInt("MPX_CR_FLEECA_PREP_1", 5000);
            Stats::SetInt("MPX_CR_FLEECA_PREP_2", 5000);
            Stats::SetInt("MPX_CR_FLEECA_FINALE", 5000);
            Stats::SetInt("MPX_CR_PRISON_PLANE", 5000);
            Stats::SetInt("MPX_CR_PRISON_BUS", 5000);
            Stats::SetInt("MPX_CR_PRISON_STATION", 5000);
            Stats::SetInt("MPX_CR_PRISON_UNFINISHED_BIZ", 5000);
            Stats::SetInt("MPX_CR_PRISON_FINALE", 5000);
            Stats::SetInt("MPX_CR_HUMANE_KEY_CODES", 5000);
            Stats::SetInt("MPX_CR_HUMANE_ARMORDILLOS", 5000);
            Stats::SetInt("MPX_CR_HUMANE_EMP", 5000);
            Stats::SetInt("MPX_CR_HUMANE_VALKYRIE", 5000);
            Stats::SetInt("MPX_CR_HUMANE_FINALE", 5000);
            Stats::SetInt("MPX_CR_NARC_COKE", 5000);
            Stats::SetInt("MPX_CR_NARC_TRASH_TRUCK", 5000);
            Stats::SetInt("MPX_CR_NARC_BIKERS", 5000);
            Stats::SetInt("MPX_CR_NARC_WEED", 5000);
            Stats::SetInt("MPX_CR_NARC_STEAL_METH", 5000);
            Stats::SetInt("MPX_CR_NARC_FINALE", 5000);
            Stats::SetInt("MPX_CR_PACIFIC_TRUCKS", 5000);
            Stats::SetInt("MPX_CR_PACIFIC_WITSEC", 5000);
            Stats::SetInt("MPX_CR_PACIFIC_HACK", 5000);
            Stats::SetInt("MPX_CR_PACIFIC_BIKES", 5000);
            Stats::SetInt("MPX_CR_PACIFIC_CONVOY", 5000);
            Stats::SetInt("MPX_CR_PACIFIC_FINALE", 5000);
            Stats::SetInt("MPX_MPPLY_HEIST_ACH_TRACKER", -1);
            Stats::SetBool("MPX_MPPLY_AWD_COMPLET_HEIST_MEM", true);
            Stats::SetBool("MPX_MPPLY_AWD_COMPLET_HEIST_1STPER", true);
            Stats::SetBool("MPX_MPPLY_AWD_FLEECA_FIN", true);
            Stats::SetBool("MPX_MPPLY_AWD_HST_ORDER", true);
            Stats::SetBool("MPX_MPPLY_AWD_HST_SAME_TEAM", true);
            Stats::SetBool("MPX_MPPLY_AWD_HST_ULT_CHAL", true);
            Stats::SetBool("MPX_MPPLY_AWD_HUMANE_FIN", true);
            Stats::SetBool("MPX_MPPLY_AWD_PACIFIC_FIN", true);
            Stats::SetBool("MPX_MPPLY_AWD_PRISON_FIN", true);
            Stats::SetBool("MPX_MPPLY_AWD_SERIESA_FIN", true);
            Stats::SetBool("MPX_AWD_FINISH_HEIST_NO_DAMAGE", true);
            Stats::SetBool("MPX_AWD_SPLIT_HEIST_TAKE_EVENLY", true);
            Stats::SetBool("MPX_AWD_ALL_ROLES_HEIST", true);
            Stats::SetBool("MPX_AWD_MATCHING_OUTFIT_HEIST", true);
            Stats::SetBool("MPX_HEIST_PLANNING_DONE_PRINT", true);
            Stats::SetBool("MPX_HEIST_PLANNING_DONE_HELP_0", true);
            Stats::SetBool("MPX_HEIST_PLANNING_DONE_HELP_1", true);
            Stats::SetBool("MPX_HEIST_PRE_PLAN_DONE_HELP_0", true);
            Stats::SetBool("MPX_HEIST_CUTS_DONE_FINALE", true);
            Stats::SetBool("MPX_HEIST_IS_TUTORIAL", false);
            Stats::SetBool("MPX_HEIST_STRAND_INTRO_DONE", true);
            Stats::SetBool("MPX_HEIST_CUTS_DONE_ORNATE", true);
            Stats::SetBool("MPX_HEIST_CUTS_DONE_PRISON", true);
            Stats::SetBool("MPX_HEIST_CUTS_DONE_BIOLAB", true);
            Stats::SetBool("MPX_HEIST_CUTS_DONE_NARCOTIC", true);
            Stats::SetBool("MPX_HEIST_CUTS_DONE_TUTORIAL", true);
            Stats::SetBool("MPX_HEIST_AWARD_DONE_PREP", true);
            Stats::SetBool("MPX_HEIST_AWARD_BOUGHT_IN", true);


			// Doomsday Awards
			Stats::SetInt("MPX_GANGOPS_FM_MISSION_PROG", -1);
            Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", -1);
            Stats::SetInt("MPX_MPPLY_GANGOPS_ALLINORDER", 100);
            Stats::SetInt("MPX_MPPLY_GANGOPS_LOYALTY", 100);
            Stats::SetInt("MPX_MPPLY_GANGOPS_CRIMMASMD", 100);
            Stats::SetInt("MPX_MPPLY_GANGOPS_LOYALTY2", 100);
            Stats::SetInt("MPX_MPPLY_GANGOPS_LOYALTY3", 100);
            Stats::SetInt("MPX_MPPLY_GANGOPS_CRIMMASMD2", 100);
            Stats::SetInt("MPX_MPPLY_GANGOPS_CRIMMASMD3", 100);
            Stats::SetInt("MPX_MPPLY_GANGOPS_SUPPORT", 100);
            Stats::SetInt("MPX_CR_GANGOP_MORGUE", 10);
            Stats::SetInt("MPX_CR_GANGOP_DELUXO", 10);
            Stats::SetInt("MPX_CR_GANGOP_SERVERFARM", 10);
            Stats::SetInt("MPX_CR_GANGOP_IAABASE_FIN", 10);
            Stats::SetInt("MPX_CR_GANGOP_STEALOSPREY", 10);
            Stats::SetInt("MPX_CR_GANGOP_FOUNDRY", 10);
            Stats::SetInt("MPX_CR_GANGOP_RIOTVAN", 10);
            Stats::SetInt("MPX_CR_GANGOP_SUBMARINECAR", 10);
            Stats::SetInt("MPX_CR_GANGOP_SUBMARINE_FIN", 10);
            Stats::SetInt("MPX_CR_GANGOP_PREDATOR", 10);
            Stats::SetInt("MPX_CR_GANGOP_BMLAUNCHER", 10);
            Stats::SetInt("MPX_CR_GANGOP_BCCUSTOM", 10);
            Stats::SetInt("MPX_CR_GANGOP_STEALTHTANKS", 10);
            Stats::SetInt("MPX_CR_GANGOP_SPYPLANE", 10);
            Stats::SetInt("MPX_CR_GANGOP_FINALE", 10);
            Stats::SetInt("MPX_CR_GANGOP_FINALE_P2", 10);
            Stats::SetInt("MPX_CR_GANGOP_FINALE_P3", 10);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_IAA", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_SUBMARINE", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_MISSILE", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_ALLINORDER", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_LOYALTY", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_LOYALTY2", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_LOYALTY3", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_CRIMMASMD", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_CRIMMASMD2", true);
            Stats::SetBool("MPX_MPPLY_AWD_GANGOPS_CRIMMASMD3", true);


			// Arena War Awards
			Stats::SetInt("MPX_ARN_BS_TRINKET_TICKERS", -1);
            Stats::SetInt("MPX_ARN_BS_TRINKET_SAVED", -1);
            Stats::SetInt("MPX_AWD_WATCH_YOUR_STEP", 50);
            Stats::SetInt("MPX_AWD_TOWER_OFFENSE", 50);
            Stats::SetInt("MPX_AWD_READY_FOR_WAR", 50);
            Stats::SetInt("MPX_AWD_THROUGH_A_LENS", 50);
            Stats::SetInt("MPX_AWD_SPINNER", 50);
            Stats::SetInt("MPX_AWD_YOUMEANBOOBYTRAPS", 50);
            Stats::SetInt("MPX_AWD_MASTER_BANDITO", 50);
            Stats::SetInt("MPX_AWD_SITTING_DUCK", 50);
            Stats::SetInt("MPX_AWD_CROWDPARTICIPATION", 50);
            Stats::SetInt("MPX_AWD_KILL_OR_BE_KILLED", 50);
            Stats::SetInt("MPX_AWD_MASSIVE_SHUNT", 50);
            Stats::SetInt("MPX_AWD_YOURE_OUTTA_HERE", 200);
            Stats::SetInt("MPX_AWD_WEVE_GOT_ONE", 50);
            Stats::SetInt("MPX_AWD_ARENA_WAGEWORKER", 1000000);
            Stats::SetInt("MPX_AWD_TIME_SERVED", 1000);
            Stats::SetInt("MPX_AWD_TOP_SCORE", 55000);
            Stats::SetInt("MPX_AWD_CAREER_WINNER", 1000);
            Stats::SetInt("MPX_ARENAWARS_SP", 209);
            Stats::SetInt("MPX_ARENAWARS_SKILL_LEVEL", 20);
            Stats::SetInt("MPX_ARENAWARS_SP_LIFETIME", 209);
            Stats::SetInt("MPX_ARENAWARS_AP_TIER", 1000);
            Stats::SetInt("MPX_ARENAWARS_AP_LIFETIME", 47551850);
            Stats::SetInt("MPX_ARENAWARS_CARRER_UNLK", 44);
            Stats::SetInt("MPX_ARN_W_THEME_SCIFI", 1000);
            Stats::SetInt("MPX_ARN_W_THEME_APOC", 1000);
            Stats::SetInt("MPX_ARN_W_THEME_CONS", 1000);
            Stats::SetInt("MPX_ARN_W_PASS_THE_BOMB", 1000);
            Stats::SetInt("MPX_ARN_W_DETONATION", 1000);
            Stats::SetInt("MPX_ARN_W_ARCADE_RACE", 1000);
            Stats::SetInt("MPX_ARN_W_CTF", 1000);
            Stats::SetInt("MPX_ARN_W_TAG_TEAM", 1000);
            Stats::SetInt("MPX_ARN_W_DESTR_DERBY", 1000);
            Stats::SetInt("MPX_ARN_W_CARNAGE", 1000);
            Stats::SetInt("MPX_ARN_W_MONSTER_JAM", 1000);
            Stats::SetInt("MPX_ARN_W_GAMES_MASTERS", 1000);
            Stats::SetInt("MPX_ARN_L_PASS_THE_BOMB", 500);
            Stats::SetInt("MPX_ARN_L_DETONATION", 500);
            Stats::SetInt("MPX_ARN_L_ARCADE_RACE", 500);
            Stats::SetInt("MPX_ARN_L_CTF", 500);
            Stats::SetInt("MPX_ARN_L_TAG_TEAM", 500);
            Stats::SetInt("MPX_ARN_L_DESTR_DERBY", 500);
            Stats::SetInt("MPX_ARN_L_CARNAGE", 500);
            Stats::SetInt("MPX_ARN_L_MONSTER_JAM", 500);
            Stats::SetInt("MPX_ARN_L_GAMES_MASTERS", 500);
            Stats::SetInt("MPX_NUMBER_OF_CHAMP_BOUGHT", 1000);
            Stats::SetInt("MPX_ARN_SPECTATOR_KILLS", 1000);
            Stats::SetInt("MPX_ARN_LIFETIME_KILLS", 1000);
            Stats::SetInt("MPX_ARN_LIFETIME_DEATHS", 500);
            Stats::SetInt("MPX_ARENAWARS_CARRER_WINS", 1000);
            Stats::SetInt("MPX_ARENAWARS_CARRER_WINT", 1000);
            Stats::SetInt("MPX_ARENAWARS_MATCHES_PLYD", 1000);
            Stats::SetInt("MPX_ARENAWARS_MATCHES_PLYDT", 1000);
            Stats::SetInt("MPX_ARN_SPEC_BOX_TIME_MS", 86400000);
            Stats::SetInt("MPX_ARN_SPECTATOR_DRONE", 1000);
            Stats::SetInt("MPX_ARN_SPECTATOR_CAMS", 1000);
            Stats::SetInt("MPX_ARN_SMOKE", 1000);
            Stats::SetInt("MPX_ARN_DRINK", 1000);
            Stats::SetInt("MPX_ARN_VEH_MONSTER", 31000);
            Stats::SetInt("MPX_ARN_VEH_MONSTER", 41000);
            Stats::SetInt("MPX_ARN_VEH_MONSTER", 51000);
            Stats::SetInt("MPX_ARN_VEH_CERBERUS", 1000);
            Stats::SetInt("MPX_ARN_VEH_CERBERUS2", 1000);
            Stats::SetInt("MPX_ARN_VEH_CERBERUS3", 1000);
            Stats::SetInt("MPX_ARN_VEH_BRUISER", 1000);
            Stats::SetInt("MPX_ARN_VEH_BRUISER2", 1000);
            Stats::SetInt("MPX_ARN_VEH_BRUISER3", 1000);
            Stats::SetInt("MPX_ARN_VEH_SLAMVAN4", 1000);
            Stats::SetInt("MPX_ARN_VEH_SLAMVAN5", 1000);
            Stats::SetInt("MPX_ARN_VEH_SLAMVAN6", 1000);
            Stats::SetInt("MPX_ARN_VEH_BRUTUS", 1000);
            Stats::SetInt("MPX_ARN_VEH_BRUTUS2", 1000);
            Stats::SetInt("MPX_ARN_VEH_BRUTUS3", 1000);
            Stats::SetInt("MPX_ARN_VEH_SCARAB", 1000);
            Stats::SetInt("MPX_ARN_VEH_SCARAB2", 1000);
            Stats::SetInt("MPX_ARN_VEH_SCARAB3", 1000);
            Stats::SetInt("MPX_ARN_VEH_DOMINATOR4", 1000);
            Stats::SetInt("MPX_ARN_VEH_DOMINATOR5", 1000);
            Stats::SetInt("MPX_ARN_VEH_DOMINATOR6", 1000);
            Stats::SetInt("MPX_ARN_VEH_IMPALER2", 1000);
            Stats::SetInt("MPX_ARN_VEH_IMPALER3", 1000);
            Stats::SetInt("MPX_ARN_VEH_IMPALER4", 1000);
            Stats::SetInt("MPX_ARN_VEH_ISSI4", 1000);
            Stats::SetInt("MPX_ARN_VEH_ISSI5", 1000);
            Stats::SetInt("MPX_ARN_VEH_ISSI", 61000);
            Stats::SetInt("MPX_ARN_VEH_IMPERATOR", 1000);
            Stats::SetInt("MPX_ARN_VEH_IMPERATOR2", 1000);
            Stats::SetInt("MPX_ARN_VEH_IMPERATOR3", 1000);
            Stats::SetInt("MPX_ARN_VEH_ZR380", 1000);
            Stats::SetInt("MPX_ARN_VEH_ZR3802", 1000);
            Stats::SetInt("MPX_ARN_VEH_ZR3803", 1000);
            Stats::SetInt("MPX_ARN_VEH_DEATHBIKE", 1000);
            Stats::SetInt("MPX_ARN_VEH_DEATHBIKE2", 1000);
            Stats::SetInt("MPX_ARN_VEH_DEATHBIKE3", 1000);
            Stats::SetBool("MPX_AWD_BEGINNER", true);
            Stats::SetBool("MPX_AWD_FIELD_FILLER", true);
            Stats::SetBool("MPX_AWD_ARMCHAIR_RACER", true);
            Stats::SetBool("MPX_AWD_LEARNER", true);
            Stats::SetBool("MPX_AWD_SUNDAY_DRIVER", true);
            Stats::SetBool("MPX_AWD_THE_ROOKIE", true);
            Stats::SetBool("MPX_AWD_BUMP_AND_RUN", true);
            Stats::SetBool("MPX_AWD_GEAR_HEAD", true);
            Stats::SetBool("MPX_AWD_DOOR_SLAMMER", true);
            Stats::SetBool("MPX_AWD_HOT_LAP", true);
            Stats::SetBool("MPX_AWD_ARENA_AMATEUR", true);
            Stats::SetBool("MPX_AWD_PAINT_TRADER", true);
            Stats::SetBool("MPX_AWD_SHUNTER", true);
            Stats::SetBool("MPX_AWD_JOCK", true);
            Stats::SetBool("MPX_AWD_WARRIOR", true);
            Stats::SetBool("MPX_AWD_T_BONE", true);
            Stats::SetBool("MPX_AWD_MAYHEM", true);
            Stats::SetBool("MPX_AWD_WRECKER", true);
            Stats::SetBool("MPX_AWD_CRASH_COURSE", true);
            Stats::SetBool("MPX_AWD_ARENA_LEGEND", true);
            Stats::SetBool("MPX_AWD_PEGASUS", true);
            Stats::SetBool("MPX_AWD_UNSTOPPABLE", true);
            Stats::SetBool("MPX_AWD_CONTACT_SPORT", true);


			// Nightclub Awards
			Stats::SetInt("MPX_AWD_DANCE_TO_SOLOMUN", 120);
            Stats::SetInt("MPX_AWD_DANCE_TO_TALEOFUS", 120);
            Stats::SetInt("MPX_AWD_DANCE_TO_DIXON", 120);
            Stats::SetInt("MPX_AWD_DANCE_TO_BLKMAD", 120);
            Stats::SetInt("MPX_AWD_CLUB_DRUNK", 200);
            Stats::SetInt("MPX_NIGHTCLUB_VIP_APPEAR", 700);
            Stats::SetInt("MPX_NIGHTCLUB_JOBS_DONE", 700);
            Stats::SetInt("MPX_NIGHTCLUB_EARNINGS", 20721002);
            Stats::SetInt("MPX_HUB_SALES_COMPLETED", 1001);
            Stats::SetInt("MPX_HUB_EARNINGS", 320721002);
            Stats::SetInt("MPX_DANCE_COMBO_DURATION_MINS", 3600000);
            Stats::SetInt("MPX_NIGHTCLUB_PLAYER_APPEAR", 9506);
            Stats::SetInt("MPX_LIFETIME_HUB_GOODS_SOLD", 784672);
            Stats::SetInt("MPX_LIFETIME_HUB_GOODS_MADE", 507822);
            Stats::SetInt("MPX_DANCEPERFECTOWNCLUB", 120);
            Stats::SetInt("MPX_NUMUNIQUEPLYSINCLUB", 120);
            Stats::SetInt("MPX_DANCETODIFFDJS", 4);
            Stats::SetInt("MPX_NIGHTCLUB_HOTSPOT_TIME_MS", 3600000);
            Stats::SetInt("MPX_NIGHTCLUB_CONT_TOTAL", 20);
            Stats::SetInt("MPX_NIGHTCLUB_CONT_MISSION", -1);
            Stats::SetInt("MPX_CLUB_CONTRABAND_MISSION", 1000);
            Stats::SetInt("MPX_HUB_CONTRABAND_MISSION", 1000);
            Stats::SetBool("MPX_AWD_CLUB_HOTSPOT", true);
            Stats::SetBool("MPX_AWD_CLUB_CLUBBER", true);
            Stats::SetBool("MPX_AWD_CLUB_COORD", true);

			Stats::SetPackedBool(15554, TRUE); // Battler Trophy Bronze
			Stats::SetPackedBool(15557, TRUE); // Battler Trophy Silver
			Stats::SetPackedBool(15560, TRUE); // Battler Trophy Gold
			Stats::SetPackedBool(15553, TRUE); // Number One Nightclub Trophy Bronze
			Stats::SetPackedBool(15556, TRUE); // Number One Nightclub Trophy Silver
			Stats::SetPackedBool(15559, TRUE); // Number One Nightclub Trophy Gold
			Stats::SetPackedBool(15552, TRUE); // Greatest Dancer Trophy Bronze
			Stats::SetPackedBool(15555, TRUE); // Greatest Dancer Trophy Silver
			Stats::SetPackedBool(15558, TRUE); // Greatest Dancer Trophy Gold

			// Casino Heist Awards
			Stats::SetBool("MPX_AWD_KINGOFQUB3D", true);
            Stats::SetBool("MPX_AWD_QUBISM", true);
            Stats::SetBool("MPX_AWD_QUIBITS", true);
            Stats::SetBool("MPX_AWD_GODOFQUB3D", true);
            Stats::SetBool("MPX_AWD_GOFOR11TH", true);
            Stats::SetBool("MPX_AWD_ELEVENELEVEN", true);
            Stats::SetBool("MPX_AWD_SCOPEOUT", true);
            Stats::SetBool("MPX_AWD_CREWEDUP", true);
            Stats::SetBool("MPX_AWD_MOVINGON", true);
            Stats::SetBool("MPX_AWD_PROMOCAMP", true);
            Stats::SetBool("MPX_AWD_GUNMAN", true);
            Stats::SetBool("MPX_AWD_SMASHNGRAB", true);
            Stats::SetBool("MPX_AWD_INPLAINSI", true);
            Stats::SetBool("MPX_AWD_UNDETECTED", true);
            Stats::SetBool("MPX_AWD_ALLROUND", true);
            Stats::SetBool("MPX_AWD_ELITETHEIF", true);
            Stats::SetBool("MPX_AWD_PRO", true);
            Stats::SetBool("MPX_AWD_SUPPORTACT", true);
            Stats::SetBool("MPX_AWD_SHAFTED", true);
            Stats::SetBool("MPX_AWD_COLLECTOR", true);
            Stats::SetBool("MPX_AWD_DEADEYE", true);
            Stats::SetBool("MPX_AWD_PISTOLSATDAWN", true);
            Stats::SetBool("MPX_AWD_TRAFFICAVOI", true);
            Stats::SetBool("MPX_AWD_CANTCATCHBRA", true);
            Stats::SetBool("MPX_AWD_WIZHARD", true);
            Stats::SetBool("MPX_AWD_APEESCAPE", true);
            Stats::SetBool("MPX_AWD_MONKEYKIND", true);
            Stats::SetBool("MPX_AWD_AQUAAPE", true);
            Stats::SetBool("MPX_AWD_KEEPFAITH", true);
            Stats::SetBool("MPX_AWD_TRUELOVE", true);
            Stats::SetBool("MPX_AWD_NEMESIS", true);
            Stats::SetBool("MPX_AWD_FRIENDZONED", true);
            Stats::SetInt("MPX_AWD_ASTROCHIMP", 3000000);
            Stats::SetInt("MPX_AWD_MASTERFUL", 40000);
            Stats::SetInt("MPX_AWD_PREPARATION", 40);
            Stats::SetInt("MPX_AWD_ASLEEPONJOB", 20);
            Stats::SetInt("MPX_AWD_DAICASHCRAB", 100000);
            Stats::SetInt("MPX_AWD_BIGBRO", 40);
            Stats::SetInt("MPX_AWD_SHARPSHOOTER", 40);
            Stats::SetInt("MPX_AWD_RACECHAMP", 40);
            Stats::SetInt("MPX_AWD_BATSWORD", 1000000);
            Stats::SetInt("MPX_AWD_COINPURSE", 950000);
			for (int i = 0; i < 10; i++){
			Stats::SetInt(("MPX_IAP_INITIALS_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MPX_DG_DEFENDER_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MPX_DG_DEFENDER_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MPX_DG_MONKEY_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MPX_DG_MONKEY_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MPX_DG_PENETRATOR_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MPX_DG_PENETRATOR_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MPX_GGSM_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MPX_GGSM_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MPX_TWR_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MPX_TWR_SCORE_" + std::to_string(i)).c_str(), 50);}
			Stats::SetInt("MPX_IAP_SCORE_0", 69644);
            Stats::SetInt("MPX_IAP_SCORE_1", 50333);
            Stats::SetInt("MPX_IAP_SCORE_2", 63512);
            Stats::SetInt("MPX_IAP_SCORE_3", 46136);
            Stats::SetInt("MPX_IAP_SCORE_4", 21638);
            Stats::SetInt("MPX_IAP_SCORE_5", 2133);
            Stats::SetInt("MPX_IAP_SCORE_6", 1215);
            Stats::SetInt("MPX_IAP_SCORE_7", 2444);
            Stats::SetInt("MPX_IAP_SCORE_8", 38023);
            Stats::SetInt("MPX_IAP_SCORE_9", 2233);
            Stats::SetInt("MPX_SCGW_SCORE_1", 50);
            Stats::SetInt("MPX_SCGW_SCORE_2", 50);
            Stats::SetInt("MPX_SCGW_SCORE_3", 50);
            Stats::SetInt("MPX_SCGW_SCORE_4", 50);
            Stats::SetInt("MPX_SCGW_SCORE_5", 50);
            Stats::SetInt("MPX_SCGW_SCORE_6", 50);
            Stats::SetInt("MPX_SCGW_SCORE_7", 50);
            Stats::SetInt("MPX_SCGW_SCORE_8", 50);
            Stats::SetInt("MPX_SCGW_SCORE_9", 50);
            Stats::SetInt("SCGW_NUM_WINS_GANG_0", 50);
            Stats::SetInt("SCGW_NUM_WINS_GANG_1", 50);
            Stats::SetInt("SCGW_NUM_WINS_GANG_2", 50);
            Stats::SetInt("SCGW_NUM_WINS_GANG_3", 50);
            Stats::SetInt("IAP_MAX_MOON_DIST", INT_MAX);
            Stats::SetBool("SCGW_WON_NO_DEATHS", true);
            Stats::SetBool("IAP_CHALLENGE_0", true);
            Stats::SetBool("IAP_CHALLENGE_1", true);
            Stats::SetBool("IAP_CHALLENGE_2", true);
            Stats::SetBool("IAP_CHALLENGE_3", true);
            Stats::SetBool("IAP_CHALLENGE_4", true);
            Stats::SetBool("IAP_GOLD_TANK", true);
            Stats::SetInt("CH_ARC_CAB_CLAW_TROPHY", -1);
            Stats::SetInt("CH_ARC_CAB_LOVE_TROPHY", -1);
            Stats::SetInt("CAS_HEIST_NOTS", -1);
            Stats::SetInt("MPX_CAS_HEIST_NOTS", -1);
            Stats::SetInt("MPX_CH_ARC_CAB_CLAW_TROPHY", -1);
            Stats::SetInt("MPX_CH_ARC_CAB_LOVE_TROPHY", -1);
            Stats::SetInt("MPX_SIGNAL_JAMMERS_COLLECTED", 50);
            Stats::SetInt("MPX_AWD_ODD_JOBS", 52);
            Stats::SetInt("MPX_H3_BOARD_DIALOGUE0", -1);
            Stats::SetInt("MPX_H3_BOARD_DIALOGUE1", -1);
            Stats::SetInt("MPX_H3_BOARD_DIALOGUE2", -1);
            Stats::SetInt("MPX_H3_VEHICLESUSED", -1);
            Stats::SetBool("MPX_AWD_FIRST_TIME1", true);
            Stats::SetBool("MPX_AWD_FIRST_TIME2", true);
            Stats::SetBool("MPX_AWD_FIRST_TIME3", true);
            Stats::SetBool("MPX_AWD_FIRST_TIME4", true);
            Stats::SetBool("MPX_AWD_FIRST_TIME5", true);
            Stats::SetBool("MPX_AWD_FIRST_TIME6", true);
            Stats::SetBool("MPX_AWD_ALL_IN_ORDER", true);
            Stats::SetBool("MPX_AWD_SUPPORTING_ROLE", true);
            Stats::SetBool("MPX_AWD_LEADER", true);
            Stats::SetBool("MPX_AWD_ODD_JOBS", true);
            Stats::SetBool("MPX_AWD_SURVIVALIST", true);
            Stats::SetBool("MPX_AWD_SCOPEOUT", true);
            Stats::SetBool("MPX_AWD_CREWEDUP", true);
            Stats::SetBool("MPX_AWD_MOVINGON", true);
            Stats::SetBool("MPX_AWD_PROMOCAMP", true);
            Stats::SetBool("MPX_AWD_GUNMAN", true);
            Stats::SetBool("MPX_AWD_SMASHNGRAB", true);
            Stats::SetBool("MPX_AWD_INPLAINSI", true);
            Stats::SetBool("MPX_AWD_UNDETECTED", true);
            Stats::SetBool("MPX_AWD_ALLROUND", true);
            Stats::SetBool("MPX_AWD_ELITETHEIF", true);
            Stats::SetBool("MPX_AWD_PRO", true);
            Stats::SetBool("MPX_AWD_SUPPORTACT", true);
            Stats::SetBool("MPX_AWD_SHAFTED", true);
            Stats::SetBool("MPX_AWD_COLLECTOR", true);
            Stats::SetBool("MPX_AWD_DEADEYE", true);
            Stats::SetBool("MPX_AWD_PISTOLSATDAWN", true);
            Stats::SetBool("MPX_AWD_TRAFFICAVOI", true);
            Stats::SetBool("MPX_AWD_CANTCATCHBRA", true);
            Stats::SetBool("MPX_AWD_WIZHARD", true);
            Stats::SetBool("MPX_AWD_APEESCAPE", true);
            Stats::SetBool("MPX_AWD_MONKEYKIND", true);
            Stats::SetBool("MPX_AWD_AQUAAPE", true);
            Stats::SetBool("MPX_AWD_KEEPFAITH", true);
            Stats::SetBool("MPX_AWD_TRUELOVE", true);
            Stats::SetBool("MPX_AWD_NEMESIS", true);
            Stats::SetBool("MPX_AWD_FRIENDZONED", true);
            Stats::SetBool("MPX_VCM_FLOW_CS_RSC_SEEN", true);
            Stats::SetBool("MPX_VCM_FLOW_CS_BWL_SEEN", true);
            Stats::SetBool("MPX_VCM_FLOW_CS_MTG_SEEN", true);
            Stats::SetBool("MPX_VCM_FLOW_CS_OIL_SEEN", true);
            Stats::SetBool("MPX_VCM_FLOW_CS_DEF_SEEN", true);
            Stats::SetBool("MPX_VCM_FLOW_CS_FIN_SEEN", true);
            Stats::SetBool("MPX_CAS_VEHICLE_REWARD", false);
            Stats::SetBool("MPX_HELP_FURIA", true);
            Stats::SetBool("MPX_HELP_MINITAN", true);
            Stats::SetBool("MPX_HELP_YOSEMITE2", true);
            Stats::SetBool("MPX_HELP_ZHABA", true);
            Stats::SetBool("MPX_HELP_IMORGEN", true);
            Stats::SetBool("MPX_HELP_SULTAN2", true);
            Stats::SetBool("MPX_HELP_VAGRANT", true);
            Stats::SetBool("MPX_HELP_VSTR", true);
            Stats::SetBool("MPX_HELP_STRYDER", true);
            Stats::SetBool("MPX_HELP_SUGOI", true);
            Stats::SetBool("MPX_HELP_KANJO", true);
            Stats::SetBool("MPX_HELP_FORMULA", true);
            Stats::SetBool("MPX_HELP_FORMULA2", true);
            Stats::SetBool("MPX_HELP_JB7002", true);

			Stats::SetPackedBool(27184, TRUE); // Oil Barrels (Invade and Persuade II) (Arcade Trophy)
			Stats::SetPackedBool(27185, TRUE);
			Stats::SetPackedBool(27186, TRUE);
			Stats::SetPackedBool(27187, TRUE);
			Stats::SetPackedBool(27188, TRUE);
			Stats::SetPackedBool(27189, TRUE); // Spray Paint (Street Crimes: Gang Wars Edition) (Arcade Trophy)
			Stats::SetPackedBool(27190, TRUE);
			Stats::SetPackedBool(27191, TRUE);
			Stats::SetPackedBool(27192, TRUE);
			Stats::SetPackedBool(27193, TRUE);
			Stats::SetPackedBool(27247, TRUE); // Madam Nazar (Arcade Trophy)
			Stats::SetPackedBool(28176, TRUE); // Plushie Grindy Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28177, TRUE); // Plushie Saki Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28178, TRUE); // Plushie Humpy Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28179, TRUE); // Plushie Smoker Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28180, TRUE); // Plushie [removed]ie Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28181, TRUE); // Plushie Muffy Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28182, TRUE); // Plushie Wasabi Kitty Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28183, TRUE); // Plushie Princess Tee (incl. Arcade & Penthouse Decoration)
			Stats::SetPackedBool(28184, TRUE); // Plushie Master Tee (incl. Arcade & Penthouse Decoration)

			// Los Santos Summer Special
			Stats::SetBool("MPX_AWD_KINGOFQUB3D", true);
            Stats::SetBool("MPX_AWD_QUBISM", true);
            Stats::SetBool("MPX_AWD_QUIBITS", true);
            Stats::SetBool("MPX_AWD_GODOFQUB3D", true);
            Stats::SetBool("MPX_AWD_GOFOR11TH", true);
            Stats::SetBool("MPX_AWD_ELEVENELEVEN", true);
			
			// Cayo Perico Awards
			Stats::SetBool("MPX_AWD_INTELGATHER", true);
            Stats::SetBool("MPX_AWD_COMPOUNDINFILT", true);
            Stats::SetBool("MPX_AWD_LOOT_FINDER", true);
            Stats::SetBool("MPX_AWD_MAX_DISRUPT", true);
            Stats::SetBool("MPX_AWD_THE_ISLAND_HEIST", true);
            Stats::SetBool("MPX_AWD_GOING_ALONE", true);
            Stats::SetBool("MPX_AWD_TEAM_WORK", true);
            Stats::SetBool("MPX_AWD_MIXING_UP", true);
            Stats::SetBool("MPX_AWD_PRO_THIEF", true);
            Stats::SetBool("MPX_AWD_CAT_BURGLAR", true);
            Stats::SetBool("MPX_AWD_ONE_OF_THEM", true);
            Stats::SetBool("MPX_AWD_GOLDEN_GUN", true);
            Stats::SetBool("MPX_AWD_ELITE_THIEF", true);
            Stats::SetBool("MPX_AWD_PROFESSIONAL", true);
            Stats::SetBool("MPX_AWD_HELPING_OUT", true);
            Stats::SetBool("MPX_AWD_COURIER", true);
            Stats::SetBool("MPX_AWD_PARTY_VIBES", true);
            Stats::SetBool("MPX_AWD_HELPING_HAND", true);
            Stats::SetInt("MPX_AWD_SUNSET", 60);
            Stats::SetInt("MPX_AWD_TREASURE_HUNTER", 60);
            Stats::SetInt("MPX_AWD_WRECK_DIVING", 1000000);
            Stats::SetInt("MPX_AWD_KEINEMUSIK", 60);
            Stats::SetInt("MPX_AWD_PALMS_TRAX", 60);
            Stats::SetInt("MPX_AWD_MOODYMANN", 60);
            Stats::SetInt("MPX_AWD_FILL_YOUR_BAGS", 20000000);
            Stats::SetInt("MPX_AWD_WELL_PREPARED", 50);

			// Los Santos Tuners Awards
			Stats::SetBool("MPX_AWD_CAR_CLUB", true);
            Stats::SetBool("MPX_AWD_PRO_CAR_EXPORT", true);
            Stats::SetBool("MPX_AWD_UNION_DEPOSITORY", true);
            Stats::SetBool("MPX_AWD_MILITARY_CONVOY", true);
            Stats::SetBool("MPX_AWD_FLEECA_BANK", true);
            Stats::SetBool("MPX_AWD_FREIGHT_TRAIN", true);
            Stats::SetBool("MPX_AWD_BOLINGBROKE_ASS", true);
            Stats::SetBool("MPX_AWD_IAA_RAID", true);
            Stats::SetBool("MPX_AWD_METH_JOB", true);
            Stats::SetBool("MPX_AWD_BUNKER_RAID", true);
            Stats::SetBool("MPX_AWD_STRAIGHT_TO_VIDEO", true);
            Stats::SetBool("MPX_AWD_MONKEY_C_MONKEY_DO", true);
            Stats::SetBool("MPX_AWD_TRAINED_TO_KILL", true);
            Stats::SetBool("MPX_AWD_DIRECTOR", true);
            Stats::SetInt("MPX_AWD_CAR_CLUB_MEM", 100);
            Stats::SetInt("MPX_AWD_SPRINTRACER", 50);
            Stats::SetInt("MPX_AWD_STREETRACER", 50);
            Stats::SetInt("MPX_AWD_PURSUITRACER", 50);
            Stats::SetInt("MPX_AWD_TEST_CAR", 240);
            Stats::SetInt("MPX_AWD_AUTO_SHOP", 50);
            Stats::SetInt("MPX_AWD_CAR_EXPORT", 100);
            Stats::SetInt("MPX_AWD_GROUNDWORK", 40);
            Stats::SetInt("MPX_AWD_ROBBERY_CONTRACT", 100);
            Stats::SetInt("MPX_AWD_FACES_OF_DEATH", 30);

			//The Contract Awards
			Stats::SetBool("MPX_AWD_TEEING_OFF", true);
            Stats::SetBool("MPX_AWD_PARTY_NIGHT", true);
            Stats::SetBool("MPX_AWD_BILLIONAIRE_GAMES", true);
            Stats::SetBool("MPX_AWD_HOOD_PASS", true);
            Stats::SetBool("MPX_AWD_STUDIO_TOUR", true);
            Stats::SetBool("MPX_AWD_DONT_MESS_DRE", true);
            Stats::SetBool("MPX_AWD_BACKUP", true);
            Stats::SetBool("MPX_AWD_SHORTFRANK_1", true);
            Stats::SetBool("MPX_AWD_SHORTFRANK_2", true);
            Stats::SetBool("MPX_AWD_SHORTFRANK_3", true);
            Stats::SetBool("MPX_AWD_CONTR_KILLER", true);
            Stats::SetBool("MPX_AWD_DOGS_BEST_FRIEND", true);
            Stats::SetBool("MPX_AWD_MUSIC_STUDIO", true);
            Stats::SetBool("MPX_AWD_SHORTLAMAR_1", true);
            Stats::SetBool("MPX_AWD_SHORTLAMAR_2", true);
            Stats::SetBool("MPX_AWD_SHORTLAMAR_3", true);
            Stats::SetInt("MPX_AWD_CONTRACTOR", 50);
            Stats::SetInt("MPX_AWD_COLD_CALLER", 50);
            Stats::SetInt("MPX_AWD_PRODUCER", 60);
            Stats::SetInt("MPX_FIXERTELEPHONEHITSCOMPL", 10);
            Stats::SetInt("MPX_PAYPHONE_BONUS_KILL_METHOD", 10);
            Stats::SetInt("MPX_FIXER_COUNT", 501);
            Stats::SetInt("MPX_FIXER_SC_VEH_RECOVERED", 501);
            Stats::SetInt("MPX_FIXER_SC_VAL_RECOVERED", 501);
            Stats::SetInt("MPX_FIXER_SC_GANG_TERMINATED", 501);
            Stats::SetInt("MPX_FIXER_SC_VIP_RESCUED", 501);
            Stats::SetInt("MPX_FIXER_SC_ASSETS_PROTECTED", 501);
            Stats::SetInt("MPX_FIXER_SC_EQ_DESTROYED", 501);
            Stats::SetInt("MPX_FIXER_EARNINGS", 300000);
            Stats::SetBool("MPX_BS_FRANKLIN_DIALOGUE_0", true);
            Stats::SetBool("MPX_BS_FRANKLIN_DIALOGUE_1", true);
            Stats::SetBool("MPX_BS_FRANKLIN_DIALOGUE_2", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_SETUP", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_STRAND", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_PARTY", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_PARTY_2", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_PARTY_F", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_BILL", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_BILL_2", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_BILL_F", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD_2", true);
            Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD_F", true);


			// Los Santos Drug Wars Awards
			Stats::SetBool("MP0_AWD_ACELIQUOR", true);
			Stats::SetBool("MP0_AWD_TRUCKAMBUSH", true);
			Stats::SetBool("MP0_AWD_LOSTCAMPREV", true);
			Stats::SetBool("MP0_AWD_ACIDTRIP", true);
			Stats::SetBool("MP0_AWD_HIPPYRIVALS", true);
			Stats::SetBool("MP0_AWD_TRAINCRASH", true);
			Stats::SetBool("MP0_AWD_BACKUPB", true);
			Stats::SetBool("MP0_AWD_GETSTARTED", true);
			Stats::SetBool("MP0_AWD_CHEMREACTION", true);
			Stats::SetBool("MP0_AWD_WAREHODEFEND", true);
			Stats::SetBool("MP0_AWD_ATTACKINVEST", true);
			Stats::SetBool("MP0_AWD_RESCUECOOK", true);
			Stats::SetBool("MP0_AWD_DRUGTRIPREHAB", true);
			Stats::SetBool("MP0_AWD_CARGOPLANE", true);
			Stats::SetBool("MP0_AWD_BACKUPB2", true);
			Stats::SetBool("MP0_AWD_TAXISTAR", true);
			Stats::SetInt("MP0_AWD_RUNRABBITRUN", 5);
			Stats::SetInt("MP0_AWD_CALLME", 50);
			Stats::SetInt("MP0_AWD_CHEMCOMPOUNDS", 50);
			Stats::SetInt("MP0_AWD_STASHHORAID", 50);
			Stats::SetInt("MP0_AWD_DEADDROP", 50);
			Stats::SetInt("MP0_AWD_GOODSAMARITAN", 5);
			Stats::SetInt("MP0_AWD_OWNWORSTENEMY", 60);
			Stats::SetInt("MP0_AWD_TAXIDRIVER", 50);

			// The Chop Shop Awards
			Stats::SetBool("MPX_AWD_ACELIQUOR", true);
            Stats::SetBool("MPX_AWD_TRUCKAMBUSH", true);
            Stats::SetBool("MPX_AWD_LOSTCAMPREV", true);
            Stats::SetBool("MPX_AWD_ACIDTRIP", true);
            Stats::SetBool("MPX_AWD_HIPPYRIVALS", true);
            Stats::SetBool("MPX_AWD_TRAINCRASH", true);
            Stats::SetBool("MPX_AWD_BACKUPB", true);
            Stats::SetBool("MPX_AWD_GETSTARTED", true);
            Stats::SetBool("MPX_AWD_CHEMREACTION", true);
            Stats::SetBool("MPX_AWD_WAREHODEFEND", true);
            Stats::SetBool("MPX_AWD_ATTACKINVEST", true);
            Stats::SetBool("MPX_AWD_RESCUECOOK", true);
            Stats::SetBool("MPX_AWD_DRUGTRIPREHAB", true);
            Stats::SetBool("MPX_AWD_CARGOPLANE", true);
            Stats::SetBool("MPX_AWD_BACKUPB2", true);
            Stats::SetBool("MPX_AWD_TAXISTAR", true);
            Stats::SetInt("MPX_AWD_RUNRABBITRUN", 5);
            Stats::SetInt("MPX_AWD_CALLME", 50);
            Stats::SetInt("MPX_AWD_CHEMCOMPOUNDS", 50);
            Stats::SetInt("MPX_AWD_STASHHORAID", 50);
            Stats::SetInt("MPX_AWD_DEADDROP", 50);
            Stats::SetInt("MPX_AWD_GOODSAMARITAN", 5);
            Stats::SetInt("MPX_AWD_OWNWORSTENEMY", 60);
            Stats::SetInt("MPX_AWD_TAXIDRIVER", 50);


			// Bottom Dollar Bounties Awards
			Stats::SetBool("MPX_AWD_HIVALBOUNT1", true);
            Stats::SetBool("MPX_AWD_HIVALBOUNT2", true);
            Stats::SetBool("MPX_AWD_HIVALBOUNT3", true);
            Stats::SetBool("MPX_AWD_HIVALBOUNT4", true);
            Stats::SetBool("MPX_AWD_HIVALBOUNT5", true);
            Stats::SetBool("MPX_AWD_HIVALBOUNT6", true);
            Stats::SetBool("MPX_AWD_ASSONATTACKSWIN", true);
            Stats::SetBool("MPX_AWD_ASSONDEFENDWIN", true);
            Stats::SetBool("MPX_AWD_DISEASECONTROL", true);
            Stats::SetInt("MPX_AWD_BOUNTIES", 50); 
            Stats::SetInt("MPX_AWD_STANBOUNTIES", 50);
            Stats::SetInt("MPX_AWD_BOUNTEARNS", 5000000); 
            Stats::SetInt("MPX_AWD_BAILOFFICSTAFF", 1000000);
            Stats::SetInt("MPX_AWD_DISPATCHWORK", 50);
            Stats::SetInt("MPX_AWD_PIZZATHIS", 50);
            Stats::SetInt("MPX_AWD_ASSONBONUSOBJ", 20);
            Stats::SetInt("MPX_AWD_ASSONHARDDRIVE", 50);
            Stats::SetInt("MPX_AWD_FROSTBITE", 15);


			// Agent Sabotage Awards
			Stats::SetBool("MPX_AWD_FINEART", true);
            Stats::SetBool("MPX_AWD_BRUTEFORCE", true);
            Stats::SetBool("MPX_AWD_PROJECTBREAK", true);
            Stats::SetBool("MPX_AWD_BLACKBOXFILE", true);
            Stats::SetBool("MPX_AWD_BONUSPOINTS", true);
            Stats::SetBool("MPX_AWD_UPRUNNING", true);
            Stats::SetBool("MPX_AWD_MOGUL", true);
            Stats::SetBool("MPX_AWD_INTEL", true);
            Stats::SetBool("MPX_AWD_IRONMULE", true);
            Stats::SetBool("MPX_AWD_AMMUNITION", true);
            Stats::SetBool("MPX_AWD_DIRDELIVERY", true);
            Stats::SetBool("MPX_AWD_TITANJOB", true);
            Stats::SetBool("MPX_AWD_PERMANENTCON", true);
            Stats::SetInt("MPX_AWD_DARNELLBROSINC", 50);
            Stats::SetInt("MPX_AWD_GET_READY", 50);
            Stats::SetInt("MPX_AWD_CASHINHAND", 5000000);
            Stats::SetInt("MPX_AWD_BROTHERLYLOVE", 50000);
            Stats::SetInt("MPX_AWD_NOTOUTDPT", 5);  
            Stats::SetInt("MPX_AWD_FULSTOCKED", 8);
            Stats::SetInt("MPX_AWD_ARMSINARMS", 50);


            // Money Fronts

            Stats::SetInt("MPX_AWD_JUNKSEARCH", 50);
            Stats::SetInt("MPX_AWD_CASASS", 50);
            Stats::SetInt("MPX_AWD_LOCKUPINT", 50);
            Stats::SetInt("MPX_AWD_ESCORTFLATBED", 50);
            Stats::SetInt("MPX_AWD_LEFT4DEAD", 50);
            Stats::SetInt("MPX_AWD_TRACKER", 50);
            Stats::SetInt("MPX_AWD_CLEARCOMP", 50);
            Stats::SetInt("MPX_AWD_CASHBONUS", 50);
            Stats::SetInt("MPX_AWD_BUSINEXPAND", 50);
            Stats::SetInt("MPX_AWD_LOSTPRODUC", 50);
            Stats::SetInt("MPX_AWD_EMERGENCYSERV", 50);
            Stats::SetInt("MPX_AWD_SECUREDEL", 50);
            Stats::SetInt("MPX_AWD_TWOOFAKIND", 50);
            Stats::SetInt("MPX_AWD_DOGSDINNER", 50);
            Stats::SetInt("MPX_AWD_HEATAROUDC", 50);
            Stats::SetInt("MPX_AWD_TYCOON", 50);
            Stats::SetInt("MPX_AWD_CASHCLEAN", 50);
            Stats::SetInt("MPX_AWD_MEDICOURI", 50);
            Stats::SetInt("MPX_AWD_TRANSPORT", 50);
            Stats::SetInt("MPX_AWD_SUNBURNED", 50);
            Stats::SetInt("MPX_AWD_UNDEADPARTY", 50);



			//Character Stats
			Stats::SetInt("MPX_AWD_MENTALSTATE_TO_NORMAL", 25);
            Stats::SetInt("MPX_AWD_TRADE_IN_YOUR_PROPERTY", 25);
            Stats::SetInt("MPX_AWD_100_KILLS_PISTOL", 100);
            Stats::SetInt("MPX_AWD_100_KILLS_SNIPER", 100);
            Stats::SetInt("MPX_AWD_50_KILLS_GRENADES", 50);
            Stats::SetInt("MPX_AWD_100_KILLS_SHOTGUN", 100);
            Stats::SetInt("MPX_AWD_100_KILLS_SMG", 100);
            Stats::SetInt("MPX_AWD_50_KILLS_ROCKETLAUNCH", 50);
            Stats::SetInt("MPX_AWD_25_KILLS_STICKYBOMBS", 50);
            Stats::SetInt("MPX_AWD_20_KILLS_MELEE", 20);
            Stats::SetInt("MPX_AWD_50_VEHICLES_BLOWNUP", 50);
            Stats::SetInt("MPX_AWD_ENEMYDRIVEBYKILLS", 10);
            Stats::SetInt("MPX_AWD_VEHICLES_JACKEDR", 100);
            Stats::SetInt("MPX_AWD_HOLD_UP_SHOPS", 19);
            Stats::SetInt("MPX_AWD_COPS_KILLED", 200);
            Stats::SetInt("MPX_PISTOL_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_CMBTPISTOL_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_APPISTOL_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_MICROSMG_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_SMG_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_ASLTRIFLE_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_CRBNRIFLE_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_ADVRIFLE_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_MG_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_CMBTMG_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_ASLTSMG_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_PUMP_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_ASLTSHTGN_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_SNIPERRFL_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_HVYSNIPER_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_GRNLAUNCH_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_RPG_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_MINIGUNS_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_SAWNOFF_ENEMY_KILLS", 600);
            Stats::SetInt("MPX_CHAR_FM_CARMOD_1_UNLCK", -1);
            Stats::SetInt("MPX_CHAR_FM_CARMOD_2_UNLCK", -1);
            Stats::SetInt("MPX_CHAR_FM_CARMOD_3_UNLCK", -1);
            Stats::SetInt("MPX_CHAR_FM_CARMOD_4_UNLCK", -1);
            Stats::SetInt("MPX_CHAR_FM_CARMOD_5_UNLCK", -1);
            Stats::SetInt("MPX_CHAR_FM_CARMOD_6_UNLCK", -1);
            Stats::SetInt("MPX_CHAR_FM_CARMOD_7_UNLCK", -1);
            Stats::SetInt("MPX_AWD_FMRALLYWONDRIVE", 1);
            Stats::SetInt("MPX_AWD_FMRALLYWONNAV", 1);
            Stats::SetInt("MPX_AWD_FMWINSEARACE", 1);
            Stats::SetInt("MPX_AWD_FMWINAIRRACE", 1);
            Stats::SetInt("MPX_NUMBER_TURBO_STARTS_IN_RACE", 50);
            Stats::SetInt("MPX_USJS_COMPLETED", 50);
            Stats::SetInt("MPX_RACES_WON", 50);
            Stats::SetInt("MPPLY_TOTAL_RACES_WON", 50); // Global stat, no MPx prefix
            Stats::SetInt("MPX_AWD_FM_RACES_FASTEST_LAP", 50);
            Stats::SetInt("MPX_NUMBER_SLIPSTREAMS_IN_RACE", 100);
            Stats::SetInt("MPX_PLAYER_HEADSHOTS", 500);

		}
	};
    class UnlockAllTattoos : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
		    Stats::SetInt("MP0_AWD_CAR_BOMBS_ENEMY_KILLS", 25); // Trust No One
		    Stats::SetInt("MP0_AWD_HOLD_UP_SHOPS", 20); // Clown, Clown and Gun, Clown Dual Wield & Clown Dual Wield Dollar
		    Stats::SetInt("MP0_AWD_FMBBETWIN", 50000); // Hustler
		    Stats::SetInt("MP0_AWD_100_HEADSHOTS", 500);// Skull
		    Stats::SetInt("MP0_AWD_FM_DM_WINS", 50);// Burning Heart
		    Stats::SetInt("MP0_AWD_RACES_WON", 50); // Racing Brunette
		    Stats::SetInt("MP0_AWD_FMREVENGEKILLSDM", 50);// Dragon and Dagger
		    Stats::SetInt("MP0_AWD_FM_DM_TOTALKILLS", 500);// Melting Skull
		    Stats::SetInt("MP0_LAP_DANCED_BOUGHT", 25);// Hottie
		    Stats::SetInt("MP0_AWD_FM_TDM_MVP", 50);// Grim Reaper
		    Stats::SetInt("MP0_AWD_FMKILLBOUNTY", 25);// Skull and Sword
		    Stats::SetInt("MP0_SNIPERRFL_ENEMY_KILLS", 100);// Broken Skull
		    Stats::SetBool("MP0_AWD_FMWINEVERYGAMEMODE", true);// Angel
		    Stats::SetBool("MP0_AWD_FMMOSTKILLSSURVIVE", true);// The Wages of Sin
		    Stats::SetBool("MP0_AWD_FMRACEWORLDRECHOLDER", true);// Racing Blonde
		    Stats::SetBool("MP0_AWD_FMATTGANGHQ", true);// Grim Reaper Smoking Gun
		    Stats::SetBool("MP0_AWD_FMKILL3ANDWINGTARACE", true); // Ride or Die
		    Stats::SetBool("MP0_AWD_FMKILLSTREAKSDM", true); // Flaming Skull
		    Stats::SetInt("MP0_KILLS_PLAYERS", 250);// Blank Scroll
		    Stats::SetInt("MP0_KILLS_PLAYERS", 500);// Embellished Scroll
		    Stats::SetInt("MP0_KILLS_PLAYERS", 1000);// Seven Deadly Sins
		    Stats::SetBool("MP0_AWD_FMFULLYMODDEDCAR", true); // Los Santos Customs
			Stats::SetInt("MP0_TATTOO_FM_CURRENT_32", -1);
		    Stats::SetPackedBool(15887, TRUE); // Lucky 7s Tattoo - Male
		    Stats::SetPackedBool(15894, TRUE); // The Royals Tattoo - Male
		    Stats::SetPackedBool(15898, TRUE); // Lucky 7s Tattoo - Female
		    Stats::SetPackedBool(15905, TRUE); // The Royals Tattoo - Female
		    Stats::SetPackedBool(15737, TRUE); //Alien Tatto - Male
		    Stats::SetPackedBool(15748, TRUE); //Alien Tatto - Female
			for (int i = 0; i <= 53; i++) {
				std::string statName = "MP0_TATTOO_FM_UNLOCKS_" + std::to_string(i);
				Stats::SetInt(statName.c_str(), -1);
			}
			
	    }
	};
    	class UnlockSpecialItems : public Command
		{
		   using Command::Command;

		   virtual void OnCall() override
		   {
			    Stats::SetInt("AWD_TAXIDRIVER", 100);
			    STATS::STAT_SET_MASKED_INT("MPX_DLC22022PSTAT_INT536"_J, 10, 16, 8, true);
				// Chrome Rims
			    Stats::SetInt("MPX_AWD_WIN_CAPTURES", 50);
			    Stats::SetInt("MPX_AWD_DROPOFF_CAP_PACKAGES", 100);
			    Stats::SetInt("MPX_AWD_KILL_CARRIER_CAPTURE", 100);
			    Stats::SetInt("MPX_AWD_NIGHTVISION_KILLS", 100);
			    Stats::SetInt("MPX_AWD_WIN_LAST_TEAM_STANDINGS", 50);
			    Stats::SetInt("MPX_AWD_ONLY_PLAYER_ALIVE_LTS", 50);
			    Stats::SetInt("MPPLY_XMAS23_PLATES0", -1); // eCola and Sprunk plate types unlock
				for (int i = 0; i <= 20; ++i){
				Stats::SetInt(("MPPLY_XMASLIVERIES" + std::to_string(i)).c_str(), -1);}
			    Stats::SetPackedBool(36788, TRUE); // Dildodude Camo | Micro SMG
			    Stats::SetPackedBool(36787, TRUE); // Dildodude Camo | Pump Shotgun
			    Stats::SetPackedBool(41657, TRUE); // Employee of the Month Finish | Micro SMG
			    Stats::SetPackedBool(42069, TRUE); // Santa's Helper Finish | Heavy Sniper
			    Stats::SetPackedBool(36786, TRUE); // Season's Greetings | Pistol Mk II
			    Stats::SetPackedBool(42122, TRUE); // Skull Santa Finish | Special Carbine
			    Stats::SetPackedBool(42068, TRUE); // Snowman Finish | Combat Pistol
			    Stats::SetPackedBool(41658, TRUE); // Suede Bucks Finish | Carbine Rifle
			    Stats::SetPackedBool(41659, TRUE); // Uncle T Finish | RPG
				Stats::SetInt("MPPLY_XMAS23_PLATES0", -1);
			    *ScriptGlobal(262145).At(33811).As<int*>() = 1;
			    Stats::SetPackedBool(25134, TRUE); // Apocalypse Scarab Livery
			    Stats::SetPackedBool(25137, TRUE); // Future Shock Scarab Livery
			    Stats::SetPackedBool(25138, TRUE); // Nightmare Scarab Livery
				Stats::SetPackedBool(25155, TRUE); // Apocalypse ZR380 - Livery set
			    Stats::SetPackedBool(25156, TRUE); // Future Shock ZR380 - Livery set
			    Stats::SetPackedBool(25157, TRUE); // Nightmare ZR380 - Livery set
			    Stats::SetPackedBool(25168, TRUE); // Apocalypse Scarab - Body Spikes set
			    Stats::SetPackedBool(25169, TRUE); // Future Shock Scarab - Body Spikes set
			    Stats::SetPackedBool(25170, TRUE); // Nightmare Scarab - Body Spikes set
			    Stats::SetPackedBool(25209, TRUE); // All variants of ZR380 - Body Spikes
			    Stats::SetPackedBool(25212, TRUE); // All variants of ZR380 - Light Armor
			    Stats::SetPackedBool(25213, TRUE); // All variants of ZR380 - Reinforced Armor
			    Stats::SetPackedBool(25214, TRUE); // All variants of ZR380 - Heavy Armor
			    Stats::SetPackedBool(25485, TRUE); // All variants of ZR380 - Side Exhausts
			    Stats::SetPackedBool(25486, TRUE); // All variants of ZR380 - Spike Exhausts
			    Stats::SetPackedBool(25487, TRUE); // Apocalypse & Nightmare ZR380 - Mismatch
			    Stats::SetPackedBool(25488, TRUE); // Future Shock ZR380 - Ray Gun Exhausts
			    Stats::SetPackedBool(25489, TRUE); // Future Shock ZR380 - Sprint Car Wing
			    Stats::SetPackedBool(25490, TRUE); // Future Shock ZR380 - Armor Plating Mk. 3
			    Stats::SetPackedBool(25491, TRUE); // Future Shock ZR380 - Rear Phantom Covers
				Stats::SetPackedBool(25173, TRUE); // All variants of Scarab - Light Armor
			    Stats::SetPackedBool(25174, TRUE); // All variants of Scarab - Reinforced Armor
			    Stats::SetPackedBool(25175, TRUE); // All variants of Scarab - Heavy Armor
			    Stats::SetPackedBool(25431, TRUE); // Future Shock Scarab - Primary Full Armor
			    Stats::SetPackedBool(25432, TRUE); // All variants of Scarab - Secondary Full Armor
			    Stats::SetPackedBool(25433, TRUE); // All variants of Scarab - Carbon Full Armor
			    Stats::SetPackedBool(25434, TRUE); // Future Shock Scarab - Heavy Duty Cooling / Apocalypse & Nightmare Scarab - Air Filtration Vents & Long Range Equipment
			    Stats::SetPackedBool(25435, TRUE); // Apocalypse & Nightmare Scarab - Rusty Full Armor
			    Stats::SetPackedBool(25436, TRUE); // Apocalypse & Nightmare Scarab - Rear War Poles
			    Stats::SetPackedBool(25437, TRUE); // Apocalypse & Nightmare Scarab - Rear Spears
			    Stats::SetPackedBool(25438, TRUE); // Apocalypse & Nightmare Scarab - Skull Cross
			    Stats::SetPackedBool(25439, TRUE); // Apocalypse & Nightmare Scarab - Skull Cross w/ War Poles
			    Stats::SetPackedBool(25440, TRUE); // Apocalypse & Nightmare Scarab - Skull Cross w/ Spears
			    Stats::SetPackedBool(25441, TRUE); // Apocalypse & Nightmare Scarab - Load'a War Poles
			    Stats::SetPackedBool(25442, TRUE); // Apocalypse & Nightmare Scarab - Load'a Spears
			    Stats::SetPackedBool(25443, TRUE); // Apocalypse & Nightmare Scarab - Scarab Mega Cover set
			    Stats::SetPackedBool(25444, TRUE); // Apocalypse & Nightmare Scarab - Armored Mega Cover set
			    Stats::SetPackedBool(25445, TRUE); // Apocalypse & Nightmare Scarab - Cage
			    Stats::SetPackedBool(25446, TRUE); // Apocalypse & Nightmare Scarab - Plated Cage
			    Stats::SetPackedBool(25447, TRUE); // Future Shock Scarab - Livery Armor
			    Stats::SetPackedBool(25448, TRUE); // Future Shock Scarab - Primary Full Armor
			    Stats::SetPackedBool(25449, TRUE); // Future Shock Scarab - Livery Full Armor
			    Stats::SetPackedBool(25450, TRUE); // Future Shock Scarab - Carbon Full Armor
			    Stats::SetPackedBool(25451, TRUE); // Future Shock Scarab - Matte Full Armor
			    Stats::SetPackedBool(25452, TRUE); // Future Shock Scarab - Futuristic Panel Armor
			    Stats::SetPackedBool(25453, TRUE); // Future Shock Scarab - Plated Livery Full Armor
			    Stats::SetPackedBool(25149, TRUE); // Apocalypse Imperator - Livery set
			    Stats::SetPackedBool(25150, TRUE); // Future Shock Imperator - Livery set
			    Stats::SetPackedBool(25154, TRUE); // Nightmare Imperator - Livery set
			    Stats::SetPackedBool(25198, TRUE); // All variants of Imperator - Body Spikes
			    Stats::SetPackedBool(25202, TRUE); // All variants of Imperator - Light Armor
			    Stats::SetPackedBool(25203, TRUE); // All variants of Imperator - Reinforced Armor
			    Stats::SetPackedBool(25204, TRUE); // All variants of Imperator - Heavy Armor
			    Stats::SetPackedBool(25473, TRUE); // All variants of Imperator - Shakotan Exhaust
				Stats::SetPackedBool(25158, TRUE); // Apocalypse Issi - Livery set
			    Stats::SetPackedBool(25159, TRUE); // Future Shock Issi - Livery set
			    Stats::SetPackedBool(25163, TRUE); // Nightmare Issi - Livery set
			    Stats::SetPackedBool(25217, TRUE); // All variants of Issi - Body Spikes
			    Stats::SetPackedBool(25221, TRUE); // All variants of Issi - Light Armor
			    Stats::SetPackedBool(25222, TRUE); // All variants of Issi - Reinforced Armor
			    Stats::SetPackedBool(25223, TRUE); // All variants of Issi - Heavy Armor
			    Stats::SetPackedBool(25492, TRUE); // All variants of Issi - Heavy Duty Ram Bar
			    Stats::SetPackedBool(25493, TRUE); // Apocalypse & Nightmare Issi - Spear
			    Stats::SetPackedBool(25494, TRUE); // Apocalypse & Nightmare Issi - Left War Poles
			    Stats::SetPackedBool(25495, TRUE); // Apocalypse & Nightmare Issi - Dolly Spearton
			    Stats::SetPackedBool(25496, TRUE); // Apocalypse & Nightmare Issi - Right War Poles
			    Stats::SetPackedBool(25497, TRUE); // Apocalypse & Nightmare Issi - Skull Cross
			    Stats::SetPackedBool(25498, TRUE); // Apocalypse & Nightmare Issi - Dolly Spearton Set
			    Stats::SetPackedBool(25499, TRUE); // Apocalypse & Nightmare Issi - Dual War Poles
			    Stats::SetPackedBool(25500, TRUE); // Apocalypse & Nightmare Issi - Dolly Spearton W/ War Pole
			    Stats::SetPackedBool(25501, TRUE); // Apocalypse & Nightmare Issi - Skull Cross W/ Spear
			    Stats::SetPackedBool(25502, TRUE); // Apocalypse & Nightmare Issi - Skull Cross W/ War Pole
			    Stats::SetPackedBool(25503, TRUE); // Apocalypse & Nightmare Issi - Skull Cross W/ Dolly
			    Stats::SetPackedBool(25504, TRUE); // Apocalypse & Nightmare Issi - Left Spear
			    Stats::SetPackedBool(25505, TRUE); // Apocalypse & Nightmare Issi - Right Spear
			    Stats::SetPackedBool(25506, TRUE); // Apocalypse & Nightmare Issi - Left Skull Axe
			    Stats::SetPackedBool(25507, TRUE); // Apocalypse & Nightmare Issi - Right Axe
			    Stats::SetPackedBool(25508, TRUE); // Apocalypse & Nightmare Issi - Dual Spears
			    Stats::SetPackedBool(25509, TRUE); // Apocalypse & Nightmare Issi - Spear & Axe
			    Stats::SetPackedBool(25510, TRUE); // Apocalypse & Nightmare Issi - Axe & Spear
				Stats::SetPackedBool(25128, TRUE); // All variants of Cerberus - Reinforced Armor
			    Stats::SetPackedBool(25129, TRUE); // All variants of Cerberus - Heavy Armor
			    Stats::SetPackedBool(25190, TRUE); // Apocalypse & Nightmare Cerberus - Bastioned Ram-bars
			    Stats::SetPackedBool(25194, TRUE); // All variants of Cerberus - Bolstered Hood Cage
			    Stats::SetPackedBool(25195, TRUE); // All variants of Cerberus - Reinforced Riot Hood
			    Stats::SetPackedBool(25196, TRUE); // All variants of Cerberus - Juggernaut Hood
			    Stats::SetPackedBool(25197, TRUE); // Apocalypse & Nightmare Cerberus - War Spearheads
			    Stats::SetPackedBool(25199, TRUE); // Apocalypse & Nightmare Cerberus - War Spear Kit
			    Stats::SetPackedBool(25200, TRUE); // Apocalypse & Nightmare Cerberus - Nade Spearheads
			    Stats::SetPackedBool(25201, TRUE); // Apocalypse & Nightmare Cerberus - Nade Spear Kit
			    Stats::SetPackedBool(25205, TRUE); // Apocalypse & Nightmare Cerberus - Skull Spearheads
			    Stats::SetPackedBool(25206, TRUE); // Apocalypse & Nightmare Cerberus - Skull Spear Kit
			    Stats::SetPackedBool(25207, TRUE); // Apocalypse & Nightmare Cerberus - Arrow Spearheads
			    Stats::SetPackedBool(25208, TRUE); // Apocalypse & Nightmare Cerberus - Arrow Spear Kit
			    Stats::SetPackedBool(25210, TRUE); // Apocalypse & Nightmare Cerberus - Tridents
			    Stats::SetPackedBool(25211, TRUE); // Apocalypse & Nightmare Cerberus - Wasteland Ritual
			    Stats::SetPackedBool(25215, TRUE); // Future Shock Cerberus - Panel Detail
			    Stats::SetPackedBool(25216, TRUE); // Future Shock Cerberus - Crane Pipes
			    Stats::SetPackedBool(25218, TRUE); // Future Shock Cerberus - Hedgehog
			    Stats::SetPackedBool(25219, TRUE); // Future Shock Cerberus - Hedgehog MK2
			    Stats::SetPackedBool(25131, TRUE); // Apocalypse Brutus - Livery set
			    Stats::SetPackedBool(25132, TRUE); // Future Shock Brutus - Livery set
			    Stats::SetPackedBool(25133, TRUE); // Nightmare Brutus - Livery set
			    Stats::SetPackedBool(25160, TRUE); // All variants of Brutus - Light Armor
			    Stats::SetPackedBool(25161, TRUE); // All variants of Brutus - Reinforced Armor
			    Stats::SetPackedBool(25162, TRUE); // All variants of Brutus - Heavy Armor
				Stats::SetPackedBool(24980, TRUE); // Blue Lights
			    Stats::SetPackedBool(24981, TRUE); // Electric Blue Lights
			    Stats::SetPackedBool(24982, TRUE); // Mint Green Lights
			    Stats::SetPackedBool(24983, TRUE); // Lime Green Lights
			    Stats::SetPackedBool(24984, TRUE); // Yellow Lights
			    Stats::SetPackedBool(24985, TRUE); // Golden Shower Lights
			    Stats::SetPackedBool(24986, TRUE); // Orange Lights
			    Stats::SetPackedBool(24987, TRUE); // Red Lights
			    Stats::SetPackedBool(24988, TRUE); // Pony Pink Lights
			    Stats::SetPackedBool(24989, TRUE); // Hot Pink Lights
			    Stats::SetPackedBool(24990, TRUE); // Purple Lights
			    Stats::SetPackedBool(24991, TRUE); // Blacklight Lights
			    Stats::SetPackedBool(25231, TRUE); // Kinetic Mines
			    Stats::SetPackedBool(25233, TRUE); // Spike Mines
			    Stats::SetPackedBool(25234, TRUE); // Slick Mines
			    Stats::SetPackedBool(25235, TRUE); // Sticky Mines
			    Stats::SetPackedBool(25236, TRUE); // EMP Mines
			    Stats::SetPackedBool(25394, TRUE); // Shunt Boost
			    Stats::SetPackedBool(25395, TRUE); // Boost Upgrade 20%
			    Stats::SetPackedBool(25396, TRUE); // Boost Upgrade 60%
			    Stats::SetPackedBool(25397, TRUE); // Boost Upgrade 100%
			    Stats::SetPackedBool(25398, TRUE); // Jump Upgrade 20%
			    Stats::SetPackedBool(25399, TRUE); // Jump Upgrade 60%
			    Stats::SetPackedBool(25400, TRUE); // Jump Upgrade 100%
			    Stats::SetPackedBool(24971, TRUE); // Apocalypse Sasquatch - Livery set
			    Stats::SetPackedBool(25113, TRUE); // Future Shock Sasquatch - Livery set
			    Stats::SetPackedBool(25114, TRUE); // Nightmare Sasquatch - Livery set
			    Stats::SetPackedBool(25117, TRUE); // All variants of Sasquatch - Light Armor
			    Stats::SetPackedBool(25118, TRUE); // All variants of Sasquatch - Reinforced Armor
			    Stats::SetPackedBool(25119, TRUE); // All variants of Sasquatch - Heavy Armor
			    Stats::SetPackedBool(25167, TRUE); // All variants of Sasquatch - Heavy Armored Front
			    Stats::SetPackedBool(25171, TRUE); // All variants of Sasquatch - Heavy Armored Hood
			    Stats::SetPackedBool(25172, TRUE); // All variants of Sasquatch - Mohawk Exhausts
			    Stats::SetPackedBool(25176, TRUE); // All variants of Sasquatch - Dual Mohawk Exhausts
			    Stats::SetPackedBool(25177, TRUE); // Apocalypse & Nightmare Sasquatch - Rear Spears Left
			    Stats::SetPackedBool(25181, TRUE); // Apocalypse & Nightmare Sasquatch - Rear Spears Right
			    Stats::SetPackedBool(25182, TRUE); // Apocalypse & Nightmare Sasquatch - Skull Cross
			    Stats::SetPackedBool(25186, TRUE); // Apocalypse & Nightmare Sasquatch - Ram Skull Cross
			    Stats::SetPackedBool(25187, TRUE); // Apocalypse & Nightmare Sasquatch - Blonde Doll Cross
			    Stats::SetPackedBool(25189, TRUE); // Apocalypse & Nightmare Sasquatch - Brunette Doll Cross
			    Stats::SetPackedBool(25121, TRUE); // Apocalypse Bruiser - Livery set
			    Stats::SetPackedBool(25122, TRUE); // Future Shock Bruiser - Livery set
			    Stats::SetPackedBool(25123, TRUE); // Nightmare Bruiser - Livery set
			    Stats::SetPackedBool(25136, TRUE); // All variants of Bruiser - Body Spikes
			    Stats::SetPackedBool(25139, TRUE); // All variants of Bruiser - Light Armor
			    Stats::SetPackedBool(25140, TRUE); // All variants of Bruiser - Reinforced Armor
			    Stats::SetPackedBool(25141, TRUE); // All variants of Bruiser - Heavy Armor
			    Stats::SetPackedBool(25220, TRUE); // Future Shock Bruiser - Heavy Plated Armored Grille / Apocalypse & Nightmare Bruiser - Diamond Heavy Armor Grille
			    Stats::SetPackedBool(25224, TRUE); // All variants of Bruiser - Twin Oval Exhaust
			    Stats::SetPackedBool(25226, TRUE); // All variants of Bruiser - Long Triple Rear Exhausts
			    Stats::SetPackedBool(25227, TRUE); // All variants of Bruiser - Front & Rear Triple Exhausts
			    Stats::SetPackedBool(25232, TRUE); // Apocalypse Bruiser - Skull & Cross / Nightmare Bruiser - Painted Skull & Cross
			    Stats::SetPackedBool(25372, TRUE); // Apocalypse Bruiser - Double Cross Ram Skull / Nightmare Bruiser - Painted Ram Skull & Cross
			    Stats::SetPackedBool(25376, TRUE); // Apocalypse Bruiser - Cross & Skull Large Blade Kit / Nightmare Bruiser - Painted Skull Large Blade Kit
			    Stats::SetPackedBool(25380, TRUE); // Apocalypse Bruiser - Ram Skull Nade Kit / Nightmare Bruiser - Painted Ram Skull Nade Kit
			    Stats::SetPackedBool(25381, TRUE); // Apocalypse Bruiser - Ram Skull Medieval Kit / Nightmare Bruiser - Painted Skull Medieval Kit
			    Stats::SetPackedBool(25384, TRUE); // Apocalypse Bruiser - Ram Skull Medieval Madness / Nightmare Bruiser - Painted Skull Medieval Madness
			    Stats::SetPackedBool(25385, TRUE); // Apocalypse Bruiser - Barrels & Junk
			    Stats::SetPackedBool(25387, TRUE); // Apocalypse Bruiser - Skeleton Cage
				Stats::SetPackedBool(25388, TRUE); // Future Shock Bruiser - Light Cover
			    Stats::SetPackedBool(25389, TRUE); // Future Shock Bruiser - Spare Tire
			    Stats::SetPackedBool(25407, TRUE); // Future Shock Bruiser - Crates
			    Stats::SetPackedBool(25408, TRUE); // Nightmare Bruiser - Large Burger
			    Stats::SetPackedBool(25409, TRUE); // Nightmare Bruiser - Large Doughnuts
			    Stats::SetPackedBool(25410, TRUE); // Nightmare Bruiser - Large eCola Cans
			    Stats::SetPackedBool(25124, TRUE); // Apocalypse Slamvan - Livery set
			    Stats::SetPackedBool(25126, TRUE); // Future Shock Slamvan - Livery set
			    Stats::SetPackedBool(25130, TRUE); // Nightmare Slamvan - Livery set
			    Stats::SetPackedBool(25148, TRUE); // All variants of Slamvan - Body Spikes
			    Stats::SetPackedBool(25151, TRUE); // All variants of Slamvan - Light Armor
			    Stats::SetPackedBool(25152, TRUE); // All variants of Slamvan - Reinforced Armor
			    Stats::SetPackedBool(25153, TRUE); // All variants of Slamvan - Heavy Armor
			    Stats::SetPackedBool(25411, TRUE); // All variants of Slamvan - Rear Bumper Reinforced Armor
			    Stats::SetPackedBool(25412, TRUE); // All variants of Slamvan - Rear Bumper Heavy Armor
			    Stats::SetPackedBool(25413, TRUE); // Apocalypse Slamvan - Basic Spears
			    Stats::SetPackedBool(25414, TRUE); // Apocalypse Slamvan - Battle Cross
			    Stats::SetPackedBool(25415, TRUE); // Apocalypse Slamvan - War Cross
			    Stats::SetPackedBool(25416, TRUE); // Apocalypse Slamvan - Battle Spears
			    Stats::SetPackedBool(25417, TRUE); // Apocalypse Slamvan - War Spears
			    Stats::SetPackedBool(25418, TRUE); // Nightmare Slamvan - Knife Spears
			    Stats::SetPackedBool(25419, TRUE); // Nightmare Slamvan - Fork & Knife
			    Stats::SetPackedBool(25142, TRUE); // Apocalypse Dominator - Livery set
			    Stats::SetPackedBool(25143, TRUE); // Future Shock Dominator - Livery set
			    Stats::SetPackedBool(25144, TRUE); // Nightmare Dominator - Livery set
			    Stats::SetPackedBool(25179, TRUE); // All variants of Dominator - Body Spikes
			    Stats::SetPackedBool(25183, TRUE); // All variants of Dominator - Light Armor
			    Stats::SetPackedBool(25184, TRUE); // All variants of Dominator - Reinforced Armor
			    Stats::SetPackedBool(25185, TRUE); // All variants of Dominator - Heavy Armor
			    Stats::SetPackedBool(25454, TRUE); // All variants of Dominator - Triple Front Exhausts
			    Stats::SetPackedBool(25455, TRUE); // All variants of Dominator - Horn Exhausts
			    Stats::SetPackedBool(25456, TRUE); // All variants of Dominator - Triple Rear Exhausts
			    Stats::SetPackedBool(25457, TRUE); // Apocalypse & Nightmare Dominator - Rear Pointing War Poles
			    Stats::SetPackedBool(25458, TRUE); // Apocalypse & Nightmare Dominator - Front Facing Axes
			    Stats::SetPackedBool(25459, TRUE); // Apocalypse & Nightmare Dominator - Front Facing Spears
			    Stats::SetPackedBool(25460, TRUE); // Apocalypse & Nightmare Dominator - Unholy Cross
			    Stats::SetPackedBool(25461, TRUE); // Apocalypse & Nightmare Dominator - Brutal Unholy Cross
			    Stats::SetPackedBool(25462, TRUE); // Apocalypse & Nightmare Dominator - Bunch of War Poles
			    Stats::SetPackedBool(25463, TRUE); // Apocalypse & Nightmare Dominator - Front Pointing War Poles
			    Stats::SetPackedBool(25464, TRUE); // Apocalypse & Nightmare Dominator - Skull Hood
			    Stats::SetPackedBool(25145, TRUE); // Apocalypse Impaler - Livery set
			    Stats::SetPackedBool(25146, TRUE); // Future Shock Impaler - Livery set
			    Stats::SetPackedBool(25147, TRUE); // Nightmare Impaler - Livery set
			    Stats::SetPackedBool(25188, TRUE); // All variants of Impaler - Body Spikes
			    Stats::SetPackedBool(25191, TRUE); // All variants of Impaler - Light Armor
			    Stats::SetPackedBool(25192, TRUE); // All variants of Impaler - Reinforced Armor
			    Stats::SetPackedBool(25193, TRUE); // All variants of Impaler - Heavy Armor
				Stats::SetPackedBool(15381, TRUE); // APC SAM Battery
			    Stats::SetPackedBool(15382, TRUE); // Ballistic Equipment
			    Stats::SetPackedBool(15428, TRUE); // Half-track 20mm Quad Autocannon
			    Stats::SetPackedBool(15429, TRUE); // Weaponized Tampa Dual Remote Minigun
			    Stats::SetPackedBool(15430, TRUE); // Weaponized Tampa Rear-Firing Mortar
			    Stats::SetPackedBool(15431, TRUE); // Weaponized Tampa Front Missile Launchers
			    Stats::SetPackedBool(15432, TRUE); // Dune FAV 40mm Grenade Launcher
			    Stats::SetPackedBool(15433, TRUE); // Dune FAV 7.62mm Minigun
			    Stats::SetPackedBool(15434, TRUE); // Insurgent Pick-Up Custom .50 Cal Minigun
			    Stats::SetPackedBool(15435, TRUE); // Insurgent Pick-Up Custom Heavy Armor Plating
			    Stats::SetPackedBool(15436, TRUE); // Technical Custom 7.62mm Minigun
			    Stats::SetPackedBool(15437, TRUE); // Technical Custom Ram-bar
			    Stats::SetPackedBool(15438, TRUE); // Technical Custom Brute-bar
			    Stats::SetPackedBool(15439, TRUE); // Technical Custom Heavy Chassis Armor
			    Stats::SetPackedBool(15447, TRUE); // Oppressor Missiles
			    Stats::SetPackedBool(15448, TRUE); // Fractal Livery Set
			    Stats::SetPackedBool(15449, TRUE); // Digital Livery Set
			    Stats::SetPackedBool(15450, TRUE); // Geometric Livery Set
			    Stats::SetPackedBool(15451, TRUE); // Nature Reserve Livery
			    Stats::SetPackedBool(15452, TRUE); // Naval Battle Livery
			    Stats::SetPackedBool(15453, TRUE); // Anti-Aircraft Trailer Dual 20mm Flak
			    Stats::SetPackedBool(15454, TRUE); // Anti-Aircraft Trailer Homing Missile Battery
			    Stats::SetPackedBool(15455, TRUE); // Mobile Operations Center Rear Turrets
			    Stats::SetPackedBool(15456, TRUE); // Incendiary Rounds
			    Stats::SetPackedBool(15457, TRUE); // Hollow Point Rounds
			    Stats::SetPackedBool(15458, TRUE); // Armor Piercing Rounds
			    Stats::SetPackedBool(15459, TRUE); // Full Metal Jacket Rounds
			    Stats::SetPackedBool(15460, TRUE); // Explosive Rounds
			    Stats::SetPackedBool(15461, TRUE); // Pistol Mk II Mounted Scope
			    Stats::SetPackedBool(15462, TRUE); // Pistol Mk II Compensator
			    Stats::SetPackedBool(15463, TRUE); // SMG Mk II Holographic Sight
			    Stats::SetPackedBool(15464, TRUE); // SMG Mk II Heavy Barrel
			    Stats::SetPackedBool(15465, TRUE); // Heavy Sniper Mk II Night Vision Scope
			    Stats::SetPackedBool(15466, TRUE); // Heavy Sniper Mk II Thermal Scope
			    Stats::SetPackedBool(15467, TRUE); // Heavy Sniper Mk II Heavy Barrel
			    Stats::SetPackedBool(15468, TRUE); // Combat MG Mk II Holographic Sight
			    Stats::SetPackedBool(15469, TRUE); // Combat MG Mk II Heavy Barrel
			    Stats::SetPackedBool(15470, TRUE); // Assault Rifle Mk II Holographic Sight
			    Stats::SetPackedBool(15471, TRUE); // Assault Rifle Mk II Heavy Barrel
			    Stats::SetPackedBool(15472, TRUE); // Carbine Rifle Mk II Holographic Sight
			    Stats::SetPackedBool(15473, TRUE); // Carbine Rifle Mk II Heavy Barrel
			    Stats::SetPackedBool(15474, TRUE); // Proximity Mines
			    Stats::SetPackedBool(15491, TRUE); // Weaponized Tampa Heavy Chassis Armor
			    Stats::SetPackedBool(15492, TRUE); // Brushstroke Camo Mk II Weapon Livery
			    Stats::SetPackedBool(15493, TRUE); // Skull Mk II Weapon Livery
			    Stats::SetPackedBool(15494, TRUE); // Sessanta Nove Mk II Weapon Livery
			    Stats::SetPackedBool(15495, TRUE); // Perseus Mk II Weapon Livery
			    Stats::SetPackedBool(15496, TRUE); // Leopard Mk II Weapon Livery
			    Stats::SetPackedBool(15497, TRUE); // Zebra Mk II Weapon Livery
			    Stats::SetPackedBool(15498, TRUE); // Geometric Mk II Weapon Livery
			    Stats::SetPackedBool(15499, TRUE); // Boom! Mk II Weapon Livery
				Stats::SetPackedBool(31831, TRUE); // Dinka SPL (Wheel Mod)
			    Stats::SetPackedBool(31846, TRUE); // Retro Turbofan (Wheel Mod)
			    Stats::SetPackedBool(31861, TRUE); // Conical Turbofan (Wheel Mod)
			    Stats::SetPackedBool(31876, TRUE); // Ice Storm (Wheel Mod)
			    Stats::SetPackedBool(31891, TRUE); // Super Turbine (Wheel Mod)
			    Stats::SetPackedBool(31904, TRUE); // Modern Mesh (Wheel Mod)
			    Stats::SetPackedBool(31909, TRUE); // Forged Star (Wheel Mod)
			    Stats::SetPackedBool(31914, TRUE); // Showflake (Wheel Mod)
			    Stats::SetPackedBool(31919, TRUE); // Giga Mesh (Wheel Mod)
			    Stats::SetPackedBool(31924, TRUE); // Mesh Meister (Wheel Mod)
			    Stats::SetPackedBool(31836, TRUE); // Euros - Speed Trail (Livery)
			    Stats::SetPackedBool(31906, TRUE); // Euros - Drift Tribe (Livery)
			    Stats::SetPackedBool(31943, TRUE); // Euros - King Scorpion (Livery)
			    Stats::SetPackedBool(31968, TRUE); // Euros - Sprunk Light (Livery)
			    Stats::SetPackedBool(31993, TRUE); // Euros - Candybox Gold (Livery)
			    Stats::SetPackedBool(31901, TRUE); // Tailgater S - Crevis Race (Livery)
			    Stats::SetPackedBool(31941, TRUE); // Tailgater S - Redwood (Livery)
			    Stats::SetPackedBool(31966, TRUE); // Tailgater S - Disruption Logistics (Livery)
			    Stats::SetPackedBool(31991, TRUE); // Tailgater S - Colored Camo Livery (Livery)
			    Stats::SetPackedBool(32016, TRUE); // Tailgater S - Army Camo Solid (Livery)
			    Stats::SetPackedBool(31866, TRUE); // ZR350 - Atomic Drift Team (Livery)
			    Stats::SetPackedBool(31926, TRUE); // ZR350 - Kisama Chevrons (Livery)
			    Stats::SetPackedBool(31953, TRUE); // ZR350 - Winning is Winning (Livery)
			    Stats::SetPackedBool(31978, TRUE); // ZR350 - Annis Racing Tribal (Livery)
			    Stats::SetPackedBool(32003, TRUE); // ZR350 - Annis Racing Tribal Alt (Livery)
			    Stats::SetPackedBool(31856, TRUE); // Jester RR - 10 Minute Car (Livery)
			    Stats::SetPackedBool(31921, TRUE); // Jester RR - Yogarishima (Livery)
			    Stats::SetPackedBool(31951, TRUE); // Jester RR - Fuque (Livery)
			    Stats::SetPackedBool(31976, TRUE); // Jester RR - Xero Gas Rally (Livery)
			    Stats::SetPackedBool(32001, TRUE); // Jester RR - Split Siberia (Livery)
			    Stats::SetPackedBool(31881, TRUE); // Calico GTF - Fukaru Rally (Livery)
			    Stats::SetPackedBool(31933, TRUE); // Calico GTF - Disruption Rally (Livery)
			    Stats::SetPackedBool(31958, TRUE); // Calico GTF - Redwood Rally (Livery)
			    Stats::SetPackedBool(31983, TRUE); // Calico GTF - Prolaps Rally (Livery)
			    Stats::SetPackedBool(32008, TRUE); // Calico GTF - Xero Gas Rally (Livery)
			    Stats::SetPackedBool(31886, TRUE); // Remus - Blue Lightning (Livery)
			    Stats::SetPackedBool(31936, TRUE); // Remus - Annis Tech (Livery)
			    Stats::SetPackedBool(31961, TRUE); // Remus - Atomic Motorsport (Livery)
			    Stats::SetPackedBool(31986, TRUE); // Remus - Shiny Wasabi Kitty (Livery)
			    Stats::SetPackedBool(32011, TRUE); // Remus - Fukaru Motorsport (Livery)
			    Stats::SetPackedBool(31841, TRUE); // Futo GTX - Chokusen Dorifuto (Livery)
			    Stats::SetPackedBool(31911, TRUE); // Futo GTX - Drift King (Livery)
			    Stats::SetPackedBool(31946, TRUE); // Futo GTX - Tandem Battle (Livery)
			    Stats::SetPackedBool(31971, TRUE); // Futo GTX - Itasha Drift (Livery)
			    Stats::SetPackedBool(31996, TRUE); // Futo GTX - Stance Andreas (Livery)
			    Stats::SetPackedBool(31851, TRUE); // RT3000 - Stance Andreas (Livery)
			    Stats::SetPackedBool(31916, TRUE); // RT3000 - Atomic Motorsport (Livery)
			    Stats::SetPackedBool(31948, TRUE); // RT3000 - Dinka Performance (Livery)
			    Stats::SetPackedBool(31973, TRUE); // RT3000 - Shiny Wasabi Kitty (Livery)
			    Stats::SetPackedBool(31998, TRUE); // RT3000 - Total Fire (Livery)
			    Stats::SetPackedBool(31871, TRUE); // Warrener HKR - Classic Vulcar (Livery)
			    Stats::SetPackedBool(31931, TRUE); // Warrener HKR - Classic Vulcar Alt (Livery)
			    Stats::SetPackedBool(31956, TRUE); // Warrener HKR - Redwood Racing (Livery)
			    Stats::SetPackedBool(31981, TRUE); // Warrener HKR - Vulcar Turbo (Livery)
			    Stats::SetPackedBool(32006, TRUE); // Warrener HKR - Vulcar Turbo Alt (Livery)
			    Stats::SetPackedBool(31896, TRUE); // Dominator GTT - Oldschool Oval (Livery)
			    Stats::SetPackedBool(31938, TRUE); // Dominator GTT - Resto Mod Racer (Livery)
			    Stats::SetPackedBool(31963, TRUE); // Dominator GTT - Flame On (Livery)
			    Stats::SetPackedBool(31988, TRUE); // Dominator GTT - The Patriot (Livery)
			    Stats::SetPackedBool(32013, TRUE); // Dominator GTT - 70s Street Machine (Livery)
		    }
	    };
        class UnlockAllParachutes : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetPackedBool(3609,TRUE);
				Stats::SetPackedBool(31791, TRUE);
				Stats::SetPackedBool(31792, TRUE);
				Stats::SetPackedBool(31793, TRUE);
				Stats::SetPackedBool(31794, TRUE);
				Stats::SetPackedBool(31795, TRUE);
				Stats::SetPackedBool(31796, TRUE);
				Stats::SetPackedBool(34378, TRUE);
				Stats::SetPackedBool(34379, TRUE);
			    Stats::SetPackedBool(31791, TRUE); // Sprunk Chute Bag
			    Stats::SetPackedBool(31792, TRUE); // eCola Chute Bag
			    Stats::SetPackedBool(31793, TRUE); // Halloween Chute Bag

		    }
	    };
        class FastRunReloadUnlock : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
				Stats::SetInt("MPX_CHAR_FM_ABILITY_1_UNLCK", -1);
				Stats::SetInt("MPX_CHAR_ABILITY_1_UNLCK", -1);
				Stats::SetInt("MPX_CHAR_FM_ABILITY_2_UNLCK", -1);
				Stats::SetInt("MPX_CHAR_ABILITY_2_UNLCK", -1);
				Stats::SetInt("MPX_CHAR_FM_ABILITY_3_UNLCK", -1);
				Stats::SetInt("MPX_CHAR_ABILITY_3_UNLCK", -1);
		    }
	    };
        class UnlockAchievements : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    for (int i = 0; i <= 77; i++)
			    {
				    PLAYER::GIVE_ACHIEVEMENT_TO_PLAYER(i);
			    }
		    }
	    };
        class UnlockMasks : public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {	    
			    auto base = ScriptGlobal(262145);
			    for (int i = 34625; i <= 34643; ++i)
			    {
				    *base.At(i).As<int*>() = 1;
			    }
			    *ScriptGlobal(262145).At(12027).As<int*>() = 1;
			    Stats::SetPackedBool(51222, TRUE); // Black Demon Goat Mask
			    Stats::SetPackedBool(51223, TRUE); // Red Demon Goat Mask
			    Stats::SetPackedBool(51224, TRUE); // Tan Demon Goat Mask
			    Stats::SetPackedBool(51225, TRUE); // Black Creepy Cat Mask
			    Stats::SetPackedBool(51226, TRUE); // Gray Creepy Cat Mask
			    Stats::SetPackedBool(51227, TRUE); // Brown Creepy Cat Mask
			    Stats::SetPackedBool(51228, TRUE); // Gray Hooded Skull Mask
			    Stats::SetPackedBool(51229, TRUE); // Red Hooded Skull Mask
			    Stats::SetPackedBool(51230, TRUE); // Blue Hooded Skull Mask
			    Stats::SetPackedBool(51231, TRUE); // Red Flaming Skull Mask
			    Stats::SetPackedBool(51232, TRUE); // Green Flaming Skull Mask
			    Stats::SetPackedBool(51233, TRUE); // Orange Flaming Skull Mask
				Stats::SetPackedBool(25178, TRUE); // Optics Headset Mask set
			    Stats::SetPackedBool(25225, TRUE); // Cluckin' Bell Mask
			    Stats::SetPackedBool(25259, TRUE); // Death Bird Mask set
			    Stats::SetPackedBool(25260, TRUE); // Stalker Mask set
			    Stats::SetPackedBool(25261, TRUE); // Raider Mask set
			    Stats::SetPackedBool(25262, TRUE); // Marauder Mask set
			    Stats::SetPackedBool(25263, TRUE); // Paco the Taco Mask
			    Stats::SetPackedBool(31783, TRUE); // Bearsy Mask
			    Stats::SetPackedBool(25264, TRUE); // Burger Shot Mask
			    Stats::SetPackedBool(25371, TRUE); // Burger Shot Food Cap set
			    Stats::SetPackedBool(25373, TRUE); // Burger Shot Logo Cap
			    Stats::SetPackedBool(25374, TRUE); // Burger Shot Bullseye Cap
			    Stats::SetPackedBool(25375, TRUE); // Cluckin' Bell Logo Cap set
			    Stats::SetPackedBool(25377, TRUE); // Cluckin' Bell Logos Cap
			    Stats::SetPackedBool(25378, TRUE); // Hotdogs Cap set
			    Stats::SetPackedBool(25379, TRUE); // Taco Bomb Cap set
			    Stats::SetPackedBool(25382, TRUE); // Lucky Plucker Cap set
			    Stats::SetPackedBool(25383, TRUE); // Lucky Plucker Logos Cap set
			    Stats::SetPackedBool(25386, TRUE); // [removed]wasser Cap set
			    Stats::SetPackedBool(25390, TRUE); // Taco Canvas Hat
			    Stats::SetPackedBool(25373, TRUE); // Burger Shot Logo Cap
			    Stats::SetPackedBool(25374, TRUE); // Burger Shot Bullseye Cap
			    Stats::SetPackedBool(25375, TRUE); // Yellow/Blue Cluckin"Bell Cap
			    Stats::SetPackedBool(25377, TRUE); // Cluckin"Bell Logos Cap
			    Stats::SetPackedBool(25378, TRUE); // Pink/Purple/Black Hotdogs Cap
			    Stats::SetPackedBool(25379, TRUE); // Green/White/- Taco Bomb Cap
			    Stats::SetPackedBool(25382, TRUE); // Red/White Lucky Plucker Cap
			    Stats::SetPackedBool(25383, TRUE); // Lucky Plucker White/Red Pattern Cap
			    Stats::SetPackedBool(25386, TRUE); // Black/White Pisswasser Cap
			    Stats::SetPackedBool(25390, TRUE); // Taco Canvas Hat
			    Stats::SetPackedBool(25391, TRUE); // Burger Shot Canvas Hat
			    Stats::SetPackedBool(25392, TRUE); // Cluckin"Bell Canvas Hat
			    Stats::SetPackedBool(25393, TRUE); // Hotdogs Canvas Hat
			    Stats::SetPackedBool(25391, TRUE); // Burger Shot Canvas Hat
			    Stats::SetPackedBool(25392, TRUE); // Cluckin' Bell Canvas Hat
			    Stats::SetPackedBool(25393, TRUE); // Hotdogs Canvas Hat
				Stats::SetPackedBool(27087, TRUE); // Unicorn (Mask)
			    Stats::SetPackedBool(27088, TRUE); // Gingerbread (Mask)
				Stats::SetPackedBool(31826, TRUE); // Emperor Forwards Cap / Emperor Backwards Cap
			    Stats::SetPackedBool(31842, TRUE); // Karin Forwards Cap / Karin Backwards Cap
			    Stats::SetPackedBool(31860, TRUE); // Omnis Forwards Cap / Omnis Backwards Cap
			    Stats::SetPackedBool(31877, TRUE); // Annis Forwards Cap / Annis Backwards Cap
			    Stats::SetPackedBool(31893, TRUE); // Vapid Forwards Cap / Vapid Backwards Cap
			    Stats::SetPackedBool(31910, TRUE); // Light Dinka Forwards Cap / Light Dinka Backwards Cap
			    Stats::SetPackedBool(31927, TRUE); // Dark Dinka Forwards Cap / Dark Dinka Backwards Cap
			    Stats::SetPackedBool(31950, TRUE); // White Güffy Forwards Cap / White Güffy Backwards Cap
			    Stats::SetPackedBool(31975, TRUE); // Black Güffy Forwards Cap / Black Güffy Backwards Cap
			    Stats::SetPackedBool(31997, TRUE); // Hellion Forwards Cap / Hellion Backwards Cap
			    Stats::SetPackedBool(32017, TRUE); // Lampadati Forwards Cap / Lampadati Backwards Cap
			    Stats::SetPackedBool(32094, TRUE); // Broker Forwards Cap / Broker Backwards Cap
			    Stats::SetPackedBool(3599, TRUE);  // Supa Wet Beer Hat
			    Stats::SetPackedBool(25368, TRUE); // All Flaming Skull Boots
			    Stats::SetPackedBool(25369, TRUE); // All Skull Harness Boots
			    Stats::SetPackedBool(25370, TRUE); // All Plated Boots
			    Stats::SetPackedBool(25371, TRUE); // Burger Shot Fries/Burgers Cap
			    Stats::SetPackedBool(3598, TRUE);  // Blarneys Beer Hat
			    Stats::SetPackedBool(3597, TRUE);  // Patriot Beer Hat
			    Stats::SetPackedBool(3596, TRUE);  // J Lager Beer Hat
			    Stats::SetPackedBool(3595, TRUE);  // Benedict Beer Hat
			    Stats::SetPackedBool(3594, TRUE);  // [removed]wasser Beer Hat
			    Stats::SetPackedBool(4256, TRUE);  // Davis Fitted Cap
			    Stats::SetPackedBool(4255, TRUE);  // SA Fitted Cap
			    Stats::SetPackedBool(4254, TRUE);  // Strawberry Fitted Cap
			    Stats::SetPackedBool(4253, TRUE);  // Eastside Fitted Cap
			    Stats::SetPackedBool(4252, TRUE);  // Westside Fitted Cap
			    Stats::SetPackedBool(4251, TRUE);  // Benny's Fitted Cap
			    Stats::SetPackedBool(4250, TRUE);  // Boars Fitted Cap
			    Stats::SetPackedBool(4249, TRUE);  // Low Santos Fitted Cap
			    Stats::SetPackedBool(4248, TRUE);  // Magnetics Block Fitted Cap
			    Stats::SetPackedBool(4247, TRUE);  // Magnetics Script Fitted Cap
			    Stats::SetPackedBool(30293, TRUE); // Pink Dot Tech Mask
			    Stats::SetPackedBool(30292, TRUE); // Blue Dot Tech Mask
			    Stats::SetPackedBool(30291, TRUE); // Orange Dot Tech Mask
			    Stats::SetPackedBool(30290, TRUE); // Green Dot Tech Mask
			    Stats::SetPackedBool(15401, TRUE); // Warstock Cap
			    Stats::SetPackedBool(15388, TRUE); // Black Ammu-Nation Cap
			    Stats::SetPackedBool(15391, TRUE); // Black Coil Cap
			    Stats::SetPackedBool(15413, TRUE); // Wine Coil Cap
			    Stats::SetPackedBool(15397, TRUE); // Black Vom Feurer Cap
			    Stats::SetPackedBool(15411, TRUE); // White Vom Feurer Cap
			    Stats::SetPackedBool(15408, TRUE); // White Shrewsbury Cap
			    Stats::SetPackedBool(15400, TRUE); // Red Hawk & Little Cap
			    Stats::SetPackedBool(30587, TRUE); // Enus Yeti Cap
			    Stats::SetPackedBool(30588, TRUE); // 720 Cap
			    Stats::SetPackedBool(30589, TRUE); // Exsorbeo 720 Cap
			    Stats::SetPackedBool(30590, TRUE); // Guffy Double Logo Cap
			    Stats::SetPackedBool(30591, TRUE); // Rockstar Cap
			    Stats::SetPackedBool(31766, TRUE); // Sprunk Cap
			    Stats::SetPackedBool(31767, TRUE); // eCola Cap
			    Stats::SetPackedBool(36780, TRUE); // Green Reindeer Beer Hat
			    Stats::SetPackedBool(36781, TRUE); // Yellow Holly Beer Hat
			    Stats::SetPackedBool(30684, TRUE); // Vibrant Stitch Emissive Mask
			    Stats::SetPackedBool(30683, TRUE); // Neon Stitch Emissive Mask
			    Stats::SetPackedBool(30687, TRUE); // Neon Skull Emissive Mask
			    Stats::SetPackedBool(30691, TRUE); // Dark X-Ray Emissive Mask
			    Stats::SetPackedBool(30690, TRUE); // Orange Skull Emissive Mask
			    Stats::SetPackedBool(32298, TRUE); // Clownfish
			    Stats::SetPackedBool(32303, TRUE); // Brown Sea Lion
			    Stats::SetPackedBool(34429, TRUE); // Orange Tech Demon
			    Stats::SetPackedBool(34424, TRUE); // War
			    Stats::SetPackedBool(34421, TRUE); // Conquest
			    Stats::SetPackedBool(34416, TRUE); // Brown Vintage Frank
			    Stats::SetPackedBool(34704, TRUE); // Dark Green Vintage Vampire
			    Stats::SetPackedBool(34423, TRUE); // Famine
			    Stats::SetPackedBool(34419, TRUE); // Green Vintage Mummy
			    Stats::SetPackedBool(34422, TRUE); // Death
			    Stats::SetPackedBool(34418, TRUE); // Pale Vintage Mummy
			    Stats::SetPackedBool(34415, TRUE); // Green Vintage Frank
			    Stats::SetPackedBool(34437, TRUE); // Orange & Gray Tech Demon
			    Stats::SetPackedBool(36758, TRUE); // Traditional Painted Rabbit
			    Stats::SetPackedBool(36761, TRUE); // Twilight Painted Rabbit
			    Stats::SetPackedBool(30611, TRUE); // Blue & Magenta Glow Shades
			    Stats::SetPackedBool(30609, TRUE); // Blue Glow Shades
			    Stats::SetPackedBool(30614, TRUE); // Pink & Yellow Glow Shades
			    Stats::SetPackedBool(30605, TRUE); // Red Glow Shades
			    Stats::SetPackedBool(30615, TRUE); // Red & Yellow Shades
			    Stats::SetPackedBool(30639, TRUE); // Sunset Tint Oversize Shades
			    Stats::SetPackedBool(30657, TRUE); // Green Checked Round Shades
			    Stats::SetPackedBool(30640, TRUE); // Black Tint Oversize Shades
			    Stats::SetPackedBool(30672, TRUE); // All White Square Shades
			    Stats::SetPackedBool(30643, TRUE); // Green Tint Oversize Shades
			    Stats::SetPackedBool(34469, TRUE); // White Beat Off Earphones
			    Stats::SetPackedBool(34477, TRUE); // Black Beat Off Earphones
			    Stats::SetPackedBool(30598, TRUE); // Red & Blue Bangles
			    Stats::SetPackedBool(30594, TRUE); // Pink Bangles
			    Stats::SetPackedBool(30602, TRUE); // Sunset Bangles
			    Stats::SetPackedBool(36766, TRUE); // Heartbreak Pendant*
			    Stats::SetPackedBool(30626, TRUE); // Neon Glow Necklace
			    Stats::SetPackedBool(30621, TRUE); // Green Glow Necklace
			    Stats::SetPackedBool(30627, TRUE); // Party Glow Necklace
			    Stats::SetPackedBool(30625, TRUE); // Hot Glow Necklace
			    Stats::SetPackedBool(36777, TRUE); // Gold New Year Glasses
			    Stats::SetPackedBool(36778, TRUE); // Silver New Year Glasses
			    Stats::SetPackedBool(36779, TRUE); // Rainbow New Year Glasses
			    Stats::SetPackedBool(34390, TRUE); // Manor Geo Cap
			    Stats::SetPackedBool(34391, TRUE); // Apricot Perseus Cap
			    Stats::SetPackedBool(34392, TRUE); // Still Slipping Tie-dye Cap
			    Stats::SetPackedBool(34393, TRUE); // Lemon Festive Beer Hat
			    Stats::SetPackedBool(34730, TRUE); // Green Festive Beer Hat
			    Stats::SetPackedBool(34731, TRUE); // Red Snowflake Beer Hat
			    Stats::SetPackedBool(34732, TRUE); // Blue Snowflake Beer Hat
			    Stats::SetPackedBool(34733, TRUE); // Red Holly Beer Hat
			    Stats::SetPackedBool(34734, TRUE); // Pisswasser Festive Beer Hat
			    Stats::SetPackedBool(34735, TRUE); // Blarneys Festive Beer Hat
			    Stats::SetPackedBool(34736, TRUE); // Red Reindeer Beer Hat
			    Stats::SetPackedBool(34737, TRUE); // Borfmas Beer Hat
			    Stats::SetPackedBool(54628, TRUE); // Blue Two-Tone Denim Cowboy Hat
			    Stats::SetPackedBool(54624, TRUE); // Honkers Tie-Dye Hat
			    Stats::SetPackedBool(30613, TRUE); // Blue & Yellow Glow Shades
			    Stats::SetPackedBool(30616, TRUE); // Blue Glow Necklace
			    Stats::SetPackedBool(30631, TRUE); // Session Glow Necklace
			    Stats::SetPackedBool(30645, TRUE); // Red Tint Oversize Shades
			    Stats::SetPackedBool(30652, TRUE); // Yellow Checked Round Shades
			    Stats::SetPackedBool(34445, TRUE); // Pink Floral Tech Demon
			    Stats::SetPackedBool(42192, TRUE); // Cinco de Mayo Mask
			    Stats::SetPackedBool(42202, TRUE); // Heartbreakers Cap
			    Stats::SetPackedBool(42210, TRUE); // Black Los Stantos Cap
			    Stats::SetPackedBool(30593, TRUE); // Red Bangles
			    Stats::SetPackedBool(42212, TRUE); // Black LS Customs Cap, Gaiter
			    Stats::SetPackedBool(54622, TRUE); // LS Panic Varsity Cap
			    Stats::SetPackedBool(54630, TRUE); // LD Organics 420 Cap

		    }
	    };
        class UnlockFlightSchool : public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {
			    for (int i = 0; i < 10; ++i)
			    {
				    Stats::SetInt(("MPPLY_PILOT_SCHOOL_MEDAL_" + std::to_string(i)).c_str(), -1);
				    Stats::SetInt(("MPX_PILOT_SCHOOL_MEDAL_" + std::to_string(i)).c_str(), -1);
				    Stats::SetBool(("MPX_PILOT_ASPASSEDLESSON_" + std::to_string(i)).c_str(), true);
			    }
			    Stats::SetInt("MPPLY_NUM_CAPTURES_CREATED", 100);
		    }
	    };
        class NightClubPopularity : public Command
		{
			using Command::Command;
			virtual void OnCall() override
			{
			    Stats::SetInt("MPX_CLUB_POPULARITY", 1000); // Nightclub Popularity
			}
	    };
        class UnlockCollectables: public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {
			    for (int i = 28099; i <= 28148; ++i) //Signal Jammers
			    {
				    Stats::SetPackedBool(i, TRUE);
			    }
				for (int i = 34262; i <= 34361; ++i) // LD_ORGANICS
			    {
				    Stats::SetPackedBool(i, TRUE);
			    }
				for (int i = 26811; i <= 26964; ++i) // ACTION FIGURES
				{
				    Stats::SetPackedBool(i, TRUE);
			    }
				for (int i = 36630; i <= 36654; ++i) //Snowman
			    {
				    Stats::SetPackedBool(i, TRUE);
			    }

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
			     *ScriptGlobal(1673814).At(1).At(6).As<int*>() = 1; // Acid Lab
			     *ScriptGlobal(1673814).At(1).At(5).As<int*>() = 1; // Cash
			     *ScriptGlobal(1673814).At(1).At(1).As<int*>() = 1; // Document Forge
			     *ScriptGlobal(1673814).At(1).At(2).As<int*>() = 1; // Weed Farm
			     *ScriptGlobal(1673814).At(1).At(3).As<int*>() = 1; // Meth Lab
			     *ScriptGlobal(1673814).At(1).At(4).As<int*>() = 1; // Cocaine Lockup
		     }
	    };
	    class EnforceEasiestMission : public LoopedCommand
		{
			using LoopedCommand::LoopedCommand;

			virtual void OnTick() override
			{
				// Find the MC sell mission script
                auto thread = Scripts::FindScriptThread("gb_biker_contraband_sell"_J);
				if (!thread)
				    return;

               // Enhanced GTA V:
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




    static BunkerResearch _BunkerResearch{"bunkerresearch", "Unlock Bunker Research", "Unlocks all Bunker Research Items"};
	static UnlockClothing _UnlockClothing{"unlockclothing", "Unlock Clothing", "Unlocks some Clothing"};
	static UnlockAllAwards _UnlockAllAwards{"unlockallawards", "Unlock Awards", "Unlocks all Awards"};
	static UnlockAllTattoos _UnlockAllTattoos{"unlockalltattoos", "Unlock Tattoos", "Unlocks Some Tattoos"};
	static UnlockSpecialItems _UnlockSpecialItems{"unlockspecialitems", "Unlock Special Items", "Unlocks Special items like livery, Vech mods and Guns"};
	static UnlockAchievements _UnlockAchievements{"unlockachievements", "Unlock SC Achievements", "Unlocks all Social Club Achievements"};
	static UnlockAllParachutes _UnlockAllParachutes{"unlockallparachutes", "Unlock All Parachutes", "Unlocks all Parachutes"};
	static FastRunReloadUnlock _FastRunReloadUnlock{"fastrunreloadunlock", "Unlock Fast Run", "Unlocks Fast Run"};
	static UnlockMasks _UnlockMasks{"unlockmasks", "Unlock Masks", "Unlocks Some Masks"};
	static UnlockFlightSchool _UnlockFlightSchool{"unlockflightschool", "Unlock Flight School", "Unlocks Flight School"};
	static UnlockCollectables _UnlockCollectables{"unlockcollectables", "Unlock Collectables", "Unlocks Some Collectables"};
	static NightClubPopularity _NightClubPopularity{"nightclubpopularity", "Max Nightclub Popularity", "Sets Nightclub Popularity to 1000"};
    static SupplyCooldownBypass _SupplyCooldownBypass{"removeresupplycooldown", "Remove ReSupply Cooldown", "Removes Resupply Cooldown"};
    static ResupplyBusiness _resupplybusiness {"resupplybusiness", "Resupply Business", "Resupply all Business"};
	static EnforceEasiestMission _EnforceEasiestMission{"enforceeasiestmission", "Enforce Easiest Mission", "Enforces the easiest mission type for Biker Sell Missions"};
}