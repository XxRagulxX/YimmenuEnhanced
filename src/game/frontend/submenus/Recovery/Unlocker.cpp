#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "core/util/Joaat.hpp"
#include "game/backend/Tunables.hpp"
#include "src/types/script/globals/SC_MEMBERSHIP_DATA.hpp"
#include "core/commands/LoopedCommand.hpp"

namespace YimMenu::Features
{
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
	class unlock_clothing : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			const std::vector<int> clothing_ids = {

				// AreanaWar Clothing 
			    25244, // Yellow/Blue Robot Bodysuit
			    25245, // Blue/Red Hero Bodysuit
			    25246, // Green/Purple Shapes Bodysuit
			    25247, // Blue&Pink/Red&Green Contours Bodysuit
			    25248, // Green/Purple Martian Bodysuit
			    25249, // Blue/Red Reptile Bodysuit
			    25250, // Blue/Pink Galaxy Bodysuit
			    25000, // Red&Blue/Blue&Green Nebula Bodysuit
			    25251, // All Space Creature Suits
			    25252, // All Space Cyclops Suits
			    25253, // All Space Horro Suits
			    25254, // All Retro Suits
			    25255, // All Astronaut Suits
			    25256, // All Space Traveler Suits
			    25257, // Pogo Space Monkey
			    25258, // Republican Space Ranger
			    25265, // Green/Yellow/White/Black Space Rangers Tee
			    25266, // Green/Black Space Ranger Logo Tee
			    25267, // Yellow/White Phases Tee
			    25268, // Pink/Blue Rocket Splash Tee
			    24977, // Pink/Black Spacesuit Alien Tee
			    25269, // Pink/Blue/Purple Moons Tee
			    25270, // Red/Green/Blue Isn"t Free Tee
			    25271, // All Raider Tops
			    25272, // All Leather Feather Tops
			    25273, // All Mercenary Tops
			    25274, // Benedict Light Beer Hoodie
			    25275, // Taco Bomb Hoodie
			    25276, // Cluckin"Bell Logo Bomb Hoodie
			    25277, // Patriot Beer Hoodie
			    25278, // Pisswasser Hoodie
			    25279, // Burger Shot Hoodie
			    25280, // Corn Dog Hoodie
			    25281, // Donut Hoodie
			    25282, // Lucky Plucker Hoodie
			    25283, // Logger Light Hoodie
			    25284, // Pizza Hoodie
			    25285, // Fries Hoodie
			    25286, // Mushrooms Hoodie
			    25287, // Redwood Hoodie
			    25288, // eCola Infectious Hoodie
			    25289, // Cluckin"Bell Logo Hoodie
			    25290, // Lemons Hoodie
			    25291, // Tacos Hoodie
			    25292, // Burger Shot Pattern Sweater
			    25293, // Burger Shot Logo Sweater
			    25294, // Burger Shot Sweater
			    25295, // Green/White Sprunk Sweater
			    25296, // Wigwam Sweater
			    25297, // Taco Bomb Chili Sweater
			    25298, // Green/Yellow Bomb Sweater
			    25299, // Cluckin"Bell Logo Bomb Sweater
			    25300, // Blue Cluckin"Bell Sweater
			    25301, // Black Cluckin"Bell Sweater
			    25302, // Infectious/Red eCola Sweater
			    25303, // Orange/Red MeTV Sweater
			    25304, // Magenta/Cyan Heat Sweater
			    25305, // Degenatron Sweater
			    25306, // Red/Black Pisswasser Sweater
			    25307, // Bolt Burger Sweater
			    25308, // Lucky Plucker Logo Bomb Sweater
			    25309, // Lucky Plucker Sweater
			    25310, // Dark Red/Red/Black/Blue Burger Shot Hockey Shirt
			    25311, // Black/Blue Cluckin" Bell Hockey Shirt
			    25312, // Wigwam Hockey Shirt
			    25313, // Redwood Hockey Shirt
			    25314, // Bean Machine Hockey Shirt
			    25315, // Red eCola Hockey Shirt
			    25316, // Black eCola Hockey Shirt
			    25317, // Blue/Black Phat Chips Hockey Shirt
			    25318, // Green/Dark Green Sprunk Hockey Shirt
			    25319, // Sprunk Classic Hockey Shirt
			    25320, // Burger Shot Black Tee
			    25321, // Burger Shot Logo Tee
			    25322, // Cluckin"Bell Logo Tee
			    25323, // Cluckin"Bell Black Tee
			    25324, // Cluckin"Bell Filled Logo Tee
			    25325, // eCola Black Tee
			    25326, // Lucky Plucker Tee
			    25327, // Pisswasser Tee
			    25328, // Sprunk Tee
			    25329, // Taco Bomb Chili Tee
			    25330, // Taco Bomb Black Tee
			    25331, // Up-n-Atom Hamburgers Tee
			    25332, // Up-n-Atom Tee
			    25333, // Wigwam Tee
			    25334, // Degenatron ROYGBIV Tee
			    25335, // CNT Tee
			    25336, // Qub3d Tee
			    25337, // Righteous Slaughter Tee
			    25338, // Space Monkey Full Tee
			    25339, // Space Monkey Pixel Tee
			    25340, // Space Monkey Enemy Tee
			    25341, // Burger Shot Tee
			    25342, // Heat Rises Tee
			    25343, // Space Monkey Logo Tee
			    25344, // Space Monkey Suit Tee
			    25345, // Space Monkey Face Tee
			    25346, // Space Monkey Mosaic Tee
			    25347, // Bolt Burger Logo Tee
			    24970, // Bolt Burger Hunger Tee
			    25348, // Exsorbeo 720 Tee
			    25349, // Heat Blue Logo Tee
			    25350, // Heat Blue Ball Logo Tee
			    25351, // Heat Blue Pop Art Logo Tee
			    25352, // MeTV Blue 90s Tee
			    25353, // MeTV Blue Safari Tee
			    25354, // Burger Shot Target Tee
			    25355, // eCola Infectious Tee
			    25356, // Up-n-Atom White Tee
			    25357, // Jock Cranley Patriot Tee
			    25358, // CCC TV Tee
			    25359, // Degenatron Logo Tee
			    25360, // eCola White Tee
			    25361, // eCola Pass It On Tee
			    25362, // TW@ Tee
			    25363, // All Chain Pants
			    25364, // All Chain Shorts
			    25365, // All Stitch Pants
			    25366, // All Raider Pants // Raider Shoes+Pants
			    25366, // All Raider Boots // Raider Shoes+Pants
			    25367, // All Light Ups
			    25368, // All Flaming Skull Boots
			    25369, // All Skull Harness Boots
			    25370, // All Plated Boots
			    25371, // Burger Shot Fries/Burgers Cap
			    25373, // Burger Shot Logo Cap
			    25374, // Burger Shot Bullseye Cap
			    25375, // Yellow/Blue Cluckin"Bell Cap
			    25377, // Cluckin"Bell Logos Cap
			    25378, // Pink/Purple/Black Hotdogs Cap
			    25379, // Green/White/- Taco Bomb Cap
			    25382, // Red/White Lucky Plucker Cap
			    25383, // Lucky Plucker White/Red Pattern Cap
			    25386, // Black/White Pisswasser Cap
			    25390, // Taco Canvas Hat
			    25391, // Burger Shot Canvas Hat
			    25392, // Cluckin"Bell Canvas Hat
			    25393, // Hotdogs Canvas Hat

				//Casino Clothing
				28225, // Refuse Collectors
			    28226, // Undertakers
			    28227, // Valet Outfits
			    28229, // Prision Guards
			    28230, // FIB Suits
			    28232, // Gruppe Sechs Gear
			    28233, // Bugstars Uniforms
			    28234, // Maintenance
			    28235, // Yung Ancestors
			    28236, // Firefighter Gear
			    28237, // Orderly Armor
			    28238, // Upscale Armor
			    28239, // Evening Armor
			    28240, // Reinforced: Padded Combat
			    28241, // Reinforced: Bulk Combat
			    28242, // Reinforced: Compact Combat
			    28243, // Balaclava Crook
			    28244, // Classic Crook
			    28245, // High-end Crook
			    28246, // Infiltration: Upgraded Tech
			    28247, // Infiltration: Advanced Tech
			    28248, // Infiltration: Modernized Tech
			};
			for (int id : clothing_ids)
			{
				Stats::SetPackedBool(id, TRUE);
			}
		}
	};
	class Genderchange : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetInt("ALLOW_GENDER_CHANGE", 1);
		}
	};
	class CareerProgress_Rewards : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			const std::vector<int> CareerProgress_ids = {
			    // OSCAR GUZMAN FLIES AGAIN
			    51280, // Complete Up and Running for Oscar Guzman Flies Again
			    51285, // Complete Oscar Guzman Flies Again
			    51278, // Complete an Oscar Guzman Flies Again mission without dying
			    51279, // Complete Oscar Guzman Flies Again in under 60 minutes

			    // THE CLUCKIN" BELL FARM RAID
			    28272, // Steal the setup funds for The Cluckin" Bell Farm Raid
			    28287, // Complete The Cluckin" Bell Farm Raid
			    28286, // Complete a Cluckin" Bell Farm Raid mission without dying
			    28285, // Complete Scene of the Crime without being spotted
			    28282, // Complete The Cluckin" Bell Farm Raid in less than 45 minutes as a leader
			    41566, // Complete a Project Overthrow mission without dying
			    41706, // Complete a Project Overthrow mission on Hard difficulty

			    // SAN ANDREAS MERCENARIES
			    41566, // Complete a Project Overthrow mission without dying
			    41706, // Complete a Project Overthrow mission on Hard difficulty

			    // OPERATION PAPER TRAIL
			    41707, // Complete an Operation Paper Trail mission on Hard difficulty

				// A SUPERYACHT LIFE
			    41379, // Complete a Superyacht Life mission without dying
			    41708, // Complete a Superyacht Life mission on Hard difficulty

				// GERALD"S LAST PLAY
			    41410, // Complete a Last Play mission without dying
			    41709, // Complete a Last Play mission on Hard difficulty

				// PREMIUM DELUXE REPO WORK
			    41435, // Complete a Repo Work mission without dying
			    41705, // Complete a Repo Work mission on Hard difficulty

				// MADRAZO DISPATCH SERVICES
			    41506, // Complete a Dispatch Mission without dying
			    41710, // Complete a Dispatch Mission on Hard difficulty

				// LOWRIDERS
			    41539, // Complete a Lowrider mission without dying
			    41711, // Complete a Lowrider mission on Hard difficulty

				// AGENTS OF SABOTAGE
			    9539,  // Meet with Pavel
			    9549,  // Complete the Priority File 2 weeks in a row
			    9542,  // Complete all mission challenges for a File

				// BOTTOM DOLLAR BOUNTIES
			    9537, // Meet with Maude Eccles
			    7639, // Secure or eliminate a bounty target

				// THE CHOP SHOP
			    42038, // Meet with Yusuf Amir
			    42041, // Complete a Salvage Yard Robbery
			    42044, // Sell a vehicle
			    42045, // Salvage a vehicle
			    42042, // Complete all Salvage Yard Robberies
			    42046, // Complete all bonus challenges for a Salvage Yard Robbery

				// LOS SANTOS DRUG WARS
			    42037, // Set up an Acid Lab


				// THE CONTRACT
			    28257, // Set up the Agency
			    41507, // Earn $5,000,000 from Security Contracts

				// AFTER HOURS
			    22067, // Set up a Nightclub
			    15533, // Hire a second Resident DJ
			    36868, // Source Goods for your Nightclub Basement
			    36944, // Eject a troublemaker from your Nightclub
			    41989, // Fill up your Nightclub safe

				// SMUGGLER"S RUN
				15966,  // Set up a Hangar
			    41676, // Send a staff member to source Air-Freight Cargo
			    32398, // Turn a Pegasus vehicle into a Personal Aircraft
			    41987, // Fill your Hangar with Air-Freight Cargo
			    36924, // Sell 50 crates of the same type of Air-Freight Cargo in one sale

				// GUNRUNNING
			    36870, // Deliver excess weapon parts to Ammu-Nation

				// IMPORT / EXPORT
			    41988, // Fill a Vehicle Warehouse with 40 stolen vehicles

				// BIKERS
			    36871, // Become President of a Motorcycle Club
			    36872, // Hire a player to join your Motorcycle Club
			    36873, // Deliver a customer bike
			    42001, // Set up any Biker business
			    36874, // Complete a Resupply mission for any Biker business

				// FURTHER ADVENTURES IN FINANCE AND FELONY
			    36888, // Become CEO of an Organization
			    36889, // Hire a player to join your Organization
			    36890, // Export Mixed Goods to the Docks
			    36891, // Sell 111 crates of Cargo in one Sell mission

				// LOS SANTOS TUNERS
			    31737, // Visit and become a member of the LS Car Meet
			    41870, // Take a vehicle into the LS Car Meet Test Track
			    31753, // Set up an Auto Shop
			    32397, // Complete a Prize Ride Challenge

				// THE DIAMOND CASINO & RESORT
			    27089, // Visit The Diamond Casino & Resort
			    27090, // Purchase a Penthouse and visit Agatha Baker
			    36916, // Recover the bonus item after completing Cashing Out
			    41868, // Take out Avery"s bodyguards without being spotted in Cashing Out

				// THE CAYO PERICO HEIST
			    30309, // Meet Miguel Madrazo inside The Music Locker
			    30522, // Set up a Kosatka
			    41677, // Complete The Cayo Perico Heist on Hard difficulty

				// THE DIAMOND CASINO HEIST
			    28270, // Set up an Arcade
			    36842, // Scope the contents of the Casino Vault
			    32399, // Play an arcade game
			    42025, // Complete The Diamond Casino Heist in under 10 minutes on Hard difficulty
			    42086, // Unlock 15 Platinum Awards for The Diamond Casino Heist


				// THE DOOMSDAY HEIST
			    18139, // Set up a Facility and meet Lester Crest
			    36861, // Set up The Data Breaches
			    41712, // Complete The Data Breaches as a leader
			    36862, // Set up The Bogdan Problem
			    41713, // Complete The Bogdan Problem as a leader
			    36863, // Set up The Doomsday Scenario
			    41714, // Complete The Doomsday Scenario as a leader
			    41685, // Complete all 3 Acts using only pistols and vehicles
			    41690, // Complete all 3 Acts using only pistols and vehicles
			    41696, // Complete all 3 Acts using only pistols and vehicles

				// ORIGINAL HEISTS
			    36867, // Own a high-end or custom Apartment
			    36933, // Set up The Fleeca Job
			    41700, // Complete a Setup for The Fleeca Job as a leader
			    41715, // Complete The Fleeca Job as a leader
			    41716, // Complete Prison Break as a leader
			    41717, // Complete The Humane Labs Raid as a leader
			    41718, // Complete Series A Funding as a leader
			    41719, // Complete The Pacific Standard Job as a leader
			    36917, // Complete the Elite Challenge for each heist
			    42000, // Complete the Criminal Mastermind challenge

				// ARENA WAR
			    25009, // Set up an Arena Workshop

				// ADVERSARY MODE
			    36840, // Participate in the Featured Series
			    36921, // Win 5 Adversary Modes in a row

				// SURVIVALS
			    41672, // Survive 5 waves in Survival without dying
			    41673, // Get 100 headshots in a game of Survival
			    41332, // Complete 10 waves in Survival mode playing solo
			    41331, // Reach wave 16 playing Endless Waves

				// RACING
			    42023, // Participate in any Race

				// DEATHMATCHES
			    36922, // Win 5 Deathmatches in a row

				// VEHICLE ENTHUSIAST
			    41864, // Own a Garage with at least 10 spaces
			    42014, // Customize a vehicle in Los Santos Customs
			    41865, // Own a Pegasus vehicle
			    41863, // Test drive or purchase a vehicle from Premium Deluxe Motorsport or Luxury Autos
			    41840, // Upgrade a vehicle to its custom variant at Benny"s Original Motor Works
			    41839, // Upgrade a vehicle with HSW Performance Upgrades at Hao"s Special Works inside the LS Car Meet
			    41841, // Upgrade a vehicle into an Arena Contender at an Arena Workshop
			    41838, // Customize a vehicle with Imani tech at an Agency
			    41866, // Own 100 vehicles including 1 Special Vehicle

				// WEAPONS EXPERT
			    36934, // Own 5 different weapons
			    36935, // Equip Body Armor
			    36936, // Add an attachment to a weapon
			    36937, // Customize your weapon loadout at a Gun Locker
			    36938, // Customize a weapon at a Weapon Workshop
			    36920, // Request and collect a Merryweather Ammo Drop
			    36941, // Own 50 weapons
			    36942, // Visit the Gun Van every day for 10 days
			};

			// Set individual bools
			for (int id : CareerProgress_ids)
			{
				Stats::SetPackedBool(id, TRUE);
			}

			// set individual ints
			Stats::SetInt("MP0_PROG_HUB_MFH_EARNINGS", 5000000); // Earn $5,000,000 from Oscar Guzman Flies Again
			Stats::SetInt("MP0_PROG_HUB_CBR_EARNINGS", 5000000); // Earn $5,000,000 from The Cluckin" Bell Farm Raid
			Stats::SetInt("MP0_SUM23_AVOP_PROGRESS", 4095);   // Complete a Project Overthrow mission for Charlie Reed
			Stats::SetInt("MP0_ULP_MISSION_PROGRESS", 16383); // Complete an Operation Paper Trail mission for Agent ULP
			Stats::SetInt("MP0_YACHT_MISSION_FLOW", 65520);   // Complete a Superyacht Life mission for Brendan Darcy
			Stats::SetInt("MP0_HACKER_DEN_OWNED", 1);         // Acquire the Garment Factory
			Stats::SetInt("MP0_HACKER24_GEN_BS", 8160);  // Complete all the Files
			Stats::SetInt("MP0_PROG_HUB_DEN24_SAFEEARNINGS", 100000); // Earn $100,000 in additional Garment Factory earnings
			Stats::SetInt("MP0_BAIL_OFFICE_OWNED", 1);   // Set up a Bail Office
			Stats::SetInt("MP0_PROG_HUB_BOUNTY_EARNINGS", 5000000); // Earn $5,000,000 from securing or eliminating bounty targets
			Stats::SetInt("MP0_PROG_HUB_BOUNTIES_ALIVE_BS", 31); // Secure all bounty targets alive
			Stats::SetInt("MP0_BAIL_PROPERTY_EARNINGS", 1000000); // Earn $1,000,000 in additional income from your Bail Office Agents
			Stats::SetInt("MP0_SALVAGE_YARD_OWNED", 1); // Set up a Salvage Yard
			Stats::SetInt("MP0_PROG_HUB_SALV23_EARN_SALV", 2500000); // Earn $250,000 from salvaging vehicles
			Stats::SetInt("MP0_PROG_HUB_SALV23_EARN_PERF", 5); // Sell 5 vehicles in perfect condition from Salvage Yard Robberies
			Stats::SetInt("MP0_PROG_HUB_SALV23_EARN_SELL", 10000000); // Earn $10,000,000 from selling stolen vehicles
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 131071);            // Complete all missions for The First Dose

			Stats::SetInt("MP0_LFETIME_BIKER_BUY_COMPLET6", 100); // Complete 10 Source Supplies missions for the Acid Lab
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 1984);          // Complete all missions for The Last Dose
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 4063232);       // Complete all missions for The Last Dose
			Stats::SetInt("MP0_XM22_FLOW", 32505856);             // Complete all Fooligan Jobs
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS6", 10000000); // Earn $1,000,000 selling Acid
			Stats::SetInt("MP0_XM22_FLOW", 0);                          // Unlock all custom acid names
			Stats::SetInt("MP0_LFETIME_BIKER_BUY_COMPLET6", 10);        // Unlock all custom acid names
			Stats::SetInt("MP0_LFETIME_BIKER_SELL_COMPLET6", 10);       // Unlock all custom acid names
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 5);                   // Unlock all custom acid names
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 10);                  // Unlock all custom acid names
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 26);                  // Unlock all custom acid names
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS6", 1000000);  // Unlock all custom acid names
			Stats::SetInt("MP0_PROG_HUB_LSDW_FJ_NO_DEATHS", 25);        // Complete 25 Fooligan Jobs without dying
			Stats::SetInt("MP0_PROG_HUB_DAX_CLONE_KILLS", 100); // Take out 100 hostile versions of yourself in The Last Dose - Checking In

			Stats::SetInt("MP0_FIXER_COUNT", 100);                 // Complete a Security Contract
			Stats::SetInt("MP0_FIXER_GENERAL_BS", 0);              // Meet the VIP
			Stats::SetInt("MP0_AWD_COLD_CALLER", 10);              // Complete 10 Payphone Hits
			Stats::SetInt("MP0_FIXER_GENERAL_BS", 2);              // Complete the VIP Contract
			Stats::SetInt("MP0_PROG_HUB_FXER_PAY_HIT_BONUS", 100); // Complete 25 Payphone Hits with the Assassination Bonus
			Stats::SetInt("MP0_PROG_HUB_FIXER_SEC_CON_SPEC", 100); // Complete 100 Security Contracts on Specialist or Specialist+ difficulty
			Stats::SetInt("MP0_FIXER_EARNINGS", 5000000); // Earn $5,000,000 from Security Contracts
			Stats::SetInt("MP0_AWD_SHORTFRANK_1", TRUE); // Complete all Short Trips playing as Franklin and Lamar
			Stats::SetInt("MP0_AWD_SHORTFRANK_2", TRUE);  // Complete all Short Trips playing as Franklin and Lamar
			Stats::SetInt("MP0_AWD_SHORTFRANK_3", TRUE); // Complete all Short Trips playing as Franklin and Lamar

			Stats::SetInt("MP0_NIGHTCLUB_JOBS_DONE", 25); // Complete a Club Management mission
			Stats::SetInt("MP0_PROG_HUB_DANCE_DUR", 5);   // Dance for 5 minutes inside a Nightclub
			Stats::SetInt("MP0_NIGHTCLUB_VIP_APPEAR", 25);        // Have 25 celebrity appearances at your Nightclub
			Stats::SetInt("MP0_PROG_HUB_NCLUB_POP_MAX_TME", 600); // Keep your Nightclub popularity at 100% for 10 hours
			Stats::SetInt("MP0_HUB_EARNINGS", 50000000);          // Earn a total of $50,000,000 or more

			Stats::SetInt("MP0_LFETIME_HANGAR_BUY_COMPLET", 100); // Complete a Source Cargo mission
			Stats::SetInt("MP0_LFETIME_HANGAR_SEL_COMPLET", 1); // Complete an Air-Freight Cargo Sell mission
			Stats::SetInt("MP0_PROG_HUB_SMUGGLER_CRATES", 1000); // Sell 1,000 crates of Air-Freight Cargo
			Stats::SetInt("MP0_LFETIME_HANGAR_EARNINGS", 50000000); // Earn $50,000,000 selling Air-Freight Cargo

			Stats::SetInt("MP0_WVM_FLOW_BITSET_MISSIONS0", 1);   // Complete a Mobile Operation
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC5", 1); // Complete a Sell mission
			Stats::SetInt("MP0_LFETIME_BIKER_SELL_COMPLET5", 1); // Complete a Sell mission
			Stats::SetInt("MP0_SR_WEAPON_BIT_SET", 262142); // Complete all Challenges for 1 weapon at the Bunker Shooting Range
			Stats::SetInt("MP0_LFETIME_BIKER_BUY_COMPLET5", 25); // Complete 25 Resupply missions
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS5", 25000000); // Earn $25,000,000 selling Weapons

			Stats::SetInt("MP0_OWNED_IE_WAREHOUSE", 1);           // Own a Vehicle Warehouse
			Stats::SetInt("MP0_LFETIME_IE_EXPORT_COMPLETED", 25); // Complete a Vehicle Cargo mission
			Stats::SetInt("MP0_PROG_HUB_VEH_CARGO_SELL_PER", 50); // Sell 1 vehicle in perfect condition
			Stats::SetInt("MP0_PROG_HUB_VEH_CARGO_SPECIAL", 5);   // Sell 5 vehicles to Specialist Dealers
			Stats::SetInt("MP0_LFETIME_IE_MISSION_EARNINGS", 25000000); // Earn $25,000,000 selling Vehicle Cargo

			Stats::SetInt("MP0_LIFETIME_BKR_SELL_COMPLETBC", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC1", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC2", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC3", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC4", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_BAR_RESUPPLY_CR", 10);            // Resupply the Clubhouse bar 10 times
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS0", 25000000); // Earn $25,000,000 selling Product
			Stats::SetInt("MP0_PROG_HUB_BIK_CUST_DEL_CASH", 2500000);   // Earn $2,500,000 delivering customer bikes
			Stats::SetInt("MP0_PROG_HUB_CLBH_BAR_EARNINGS", 500000);    // Earn $500,000 from your Clubhouse bar
			Stats::SetInt("MP0_PROG_HUB_BIK_CONTRACT_COUNT", 50);       // Complete 50 Clubhouse Contracts

			Stats::SetInt("MP0_WARHOUSESLOT0", 1);         // Own a Special Cargo Warehouse
			Stats::SetInt("MP0_LIFETIME_BUY_COMPLETE", 1); // Source Cargo for your Warehouse
			Stats::SetInt("MP0_PROG_HUB_FAIFAF_CRATES_COL", 250);    // Source 250 crates of Cargo
			Stats::SetInt("MP0_LIFETIME_CONTRA_EARNINGS", 50000000); // Earn $50,000,000 selling Cargo

			Stats::SetInt("MP0_CAR_CLUB_MEMBERSHIP", 1); // Visit and become a member of the LS Car Meet
			Stats::SetInt("MP0_TUNER_COMP_BS", 255);    // Complete any Robbery Contract
			Stats::SetInt("MP0_AWD_AUTO_SHOP", 10);     // Service and deliver 10 customer vehicles
			Stats::SetInt("MP0_AWD_CAR_CLUB_MEM", 100); // Reach LS Car Meet reputation level 10
			Stats::SetInt("MP0_AWD_GROUNDWORK", 1); // Deliver all 10 Exotic Exports vehicles in a day
			Stats::SetInt("MP0_TUNER_COUNT", 25);       // Complete 25 Robbery Contracts
			Stats::SetInt("MP0_PROG_HUB_TUNER_CUS_DEL_CASH", 5000000); // Earn $5,000,000 delivering customer vehicles

			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 6);  // Complete Loose Cheng
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 12); // Complete Loose Cheng
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 12); // Complete Loose Cheng
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 11); // Complete Cashing Out
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 17); // Complete Cashing Out
			Stats::SetInt("MP0_AWD_ODD_JOBS", 100);     // Complete Casino Work for Agatha Baker
			Stats::SetInt("MP0_H4_MISSIONS", 0);         // Find where the Madrazo files are being held
			Stats::SetInt("MP0_H4_PROGRESS", 1);         // Complete The Cayo Perico Heist as a leader
			Stats::SetInt("MP0_H4_H4_DJ_MISSIONS", 127); // Help Tom Connors or English Dave with a DJ request
			Stats::SetInt("MP0_TREASURE_HUNTER", 10);    // Find 10 treasure chests on Cayo Perico
			Stats::SetInt("MP0_PROG_HUB_CAYO_PRP_NO_DEATHS", 25); // Complete 25 prep work missions without dying
			Stats::SetInt("MP0_H4_PROGRESS", 4032);      // Steal 5 variations of the primary target
			Stats::SetInt("MP0_CR_SUBMARINE", 1);        // Complete The Cayo Perico Heist using all approaches
			Stats::SetInt("MP0_CR_STRATEGIC_BOMBER", 1); // Complete The Cayo Perico Heist using all approaches
			Stats::SetInt("MP0_CR_SMUGGLER_PLANE", 1);   // Complete The Cayo Perico Heist using all approaches
			Stats::SetInt("MP0_CR_STEALTH_HELI", 1);     // Complete The Cayo Perico Heist using all approaches
			Stats::SetInt("MP0_CR_PATROL_BOAT", 1);      // Complete The Cayo Perico Heist using all approaches
			Stats::SetInt("MP0_CR_SMUGGLER_BOAT", 1);    // Complete The Cayo Perico Heist using all approaches
			Stats::SetInt("MP0_PROG_HUB_CAYO_H_EARNINGS", 50000000); // Steal $50,000,000 in primary and secondary targets

			Stats::SetInt("MP0_CAS_HEIST_FLOW", 1); // Meet Lester Crest at Mirror Park
			Stats::SetInt("MP0_CAS_HEIST_FLOW", 10);  // Complete The Diamond Casino Heist as a leader
			Stats::SetInt("MP0_AWD_PREPARATION", 25); // Complete 25 prep missions
			Stats::SetInt("MP0_CAS_HEIST_FLOW", 14336); // Complete The Diamond Casino Heist using all approaches
			Stats::SetInt("MP0_PROG_HUB_CASINO_H_EARNINGS", 50000000); // Steal $50,000,000 from the vault
			Stats::SetInt("MP0_AWD_DAICASHCRAB", 100000);              // Steal $100,000 from the Daily Vault
			Stats::SetInt("MP0_GANGOPS_FLOW_BITSET_MISS0", 7); // Complete any Setup for The Data Breaches
			Stats::SetInt("MP0_PROG_HUB_DOOM_PRP_NO_DEATHS", 14); // Complete 14 prep missions without dying
			Stats::SetInt("MP0_PROG_HUB_DOOMSDAY_ACTS", 15);      // Complete 15 Acts as a leader
			Stats::SetInt("MP0_PROG_HUB_HEIST_EARNINGS", 50000000); // Earn $50,000,000 across all heists

			Stats::SetInt("MP0_ARENAWARS_AP_TIER", 50); // Reach Sponsorship Tier 25
			Stats::SetInt("MP0_PROG_HUB_ADV_WINS", 50); // Win 5 Adversary Modes
			Stats::SetInt("MP0_PROG_HUB_SURVIVALS_PLAYED", 1); // Play a Survival mode
			Stats::SetInt("MP0_PROG_HUB_SURV_WAVES", 50);    // Clear 50 waves in Survival
			Stats::SetInt("MP0_AWD_FMHORDWAVESSURVIVE", 10); // Survive 10 waves in Survival without dying
			Stats::SetInt("MP0_PROG_HUB_SURV_WAVES", 250); // Clear 250 waves in Survival

			Stats::SetInt("MP0_RACES_WON", 50);                         // Win 5 Races against another player
			Stats::SetInt("MP0_PROG_HUB_T_TRIAL_PAR_TIME", 67108863);   // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_T_TRL_PAR_TIME_RC", 67108863);  // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_T_TRL_PAR_TIME_HSW", 67108863); // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_T_TRL_PAR_TIME_BKE", 67108863); // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_FST_LPS_RSTAR_RAC", 50); // Achieve the fastest lap 50 times on any Rockstar-created Race

			Stats::SetInt("MP0_DM_END", 1);                       // Participate in any Deathmatch
			Stats::SetInt("MP0_PROG_HUB_DM_TDM_PLAYS", 1);        // Participate in a Team Deathmatch
			Stats::SetInt("MP0_AWD_FM_DM_WINS", 50);              // Win 5 Deathmatches
			Stats::SetInt("MP0_PROG_HUB_DM_COMMUNITY_PLAYS", 10); // Play 10 Deathmatches in the Community Series
			Stats::SetInt("MP0_PROG_HUB_DTHM_KILL_5_WO_DIE", 25); // Kill 5 players without dying 25 times during Deathmatches

			Stats::SetInt("MP0_HUB_VEH_ENTH_OWNED_VEHS", 99); // Own 100 vehicles including 1 Special Vehicle
			Stats::SetInt("MP0_VEHICLES_CUSTOMISED", 50);     // Customize 50 vehicles

			Stats::SetInt("MP0_PROG_HUB_10_CHAL_ANSR", 10); // Win 10 Challenges against another player in the Ammu-Nation Shooting Range

		    // set Individual packed ints
		    Stats::SetPackedInt(28272, 1); // Steal setup funds
			Stats::SetPackedInt(24903, 25); // Complete 25 Files
			Stats::SetPackedInt(24904, 2);  // Complete 2 Files without losing a life
			Stats::SetPackedInt(24905, 9); //  Unlock 9 platinum awards for Agents of Sabotage
			Stats::SetPackedInt(7669, 5); // Secure or eliminate 5 Standard bounty targets
			Stats::SetPackedInt(7672, 2); // Secure or eliminate 2 Most Wanted bounty targets
			Stats::SetPackedInt(7670, 10); //  Secure or eliminate 10 bounty targets without losing a life
			Stats::SetPackedInt(7674, 3); //  Secure or eliminate a Most Wanted bounty target 3 days in a row
			Stats::SetPackedInt(7671, 25); //  Secure or eliminate 25 bounty targets
			Stats::SetPackedInt(26809, 10); //  Unlock 10 platinum awards for Bottom Dollar Bounties
			Stats::SetPackedInt(51052, 10); // Unlock 10 Platinum Awards for The Chop Shop
			Stats::SetPackedInt(41241, 5);  // Unlock all custom acid names
			Stats::SetPackedInt(42084, 24); // Unlock all Platinum Awards for Los Santos Drug Wars
			Stats::SetPackedInt(42085, 10); // Unlock 10 Platinum Awards for The Contract
			Stats::SetPackedInt(42089, 8);  // Unlock 8 Platinum Awards for After Hours
			Stats::SetPackedInt(9359, 25);  // Complete a research project
			Stats::SetPackedInt(30226, 10); // Unlock 10 Platinum Awards for Los Santos Tuners
			Stats::SetPackedInt(42093, 11); // Unlock 11 Platinum Awards for The Diamond Casino & Resort
			Stats::SetPackedInt(42094, 15); // Unlock 15 Platinum Awards for The Cayo Perico Heist
			Stats::SetPackedInt(42087, 10); // Unlock 10 Platinum Awards for The Doomsday Heist
			Stats::SetPackedInt(42100, 5);  // Complete all heists with the same crew
			Stats::SetPackedInt(42090, 15); // Unlock 15 Platinum Awards for heists
			Stats::SetPackedInt(22063, 20); // Reach skill level 5
			Stats::SetPackedInt(42088, 15); // Unlock 15 Platinum Awards for Arena Wars
			Stats::SetPackedInt(42000, 20); // Earn skill level 20 in Arena Wars
			Stats::SetPackedInt(41246, 20); // Win 20 Races in the Community Series
			Stats::SetPackedInt(42092, 5);  // Earn 5 gold medals in the Flight School challenges
			Stats::SetPackedInt(42091, 10); // Unlock 10 Platinum Awards for Vehicles
			Stats::SetPackedInt(41242, 8);  // Own 1 of each weapon type

			// Set ranged bools
			auto setRange = [](int start, int end) {
				for (int i = start; i <= end; ++i)
				{
					Stats::SetPackedBool(i, TRUE); 
				}
			};

			// Oscar Guzman
			setRange(51286, 51291); // Complete an Oscar Guzman Flies Again mission on Hard
			setRange(51292, 51297); // Complete all Oscar Guzman Flies Again missions on Hard without using snacks or armor

			// Cluckin" Bell
			setRange(28283, 28284); // Complete Scene of the Crime using both approaches
			setRange(28273, 28281); // Complete Scene of the Crime using all available setup equipment

			// San Andreas Mercenaries
			setRange(41567, 41572); // Complete all Project Overthrow missions on Hard difficulty
			setRange(41573, 41578); // Complete all Project Overthrow missions on Hard difficulty without using snacks or armor
			setRange(41579, 41584); // Complete all Project Overthrow missions taking less than 50% damage
			setRange(41585, 41590); // Complete all Project Overthrow missions with over 80% accuracy

			// Operation Paper Trail
			setRange(41333, 41338); // Complete an Operation Paper Trail mission without dying
			setRange(41339, 41344); // Complete all Operation Paper Trail missions on Hard difficulty
			setRange(41345, 41350); // Complete all Operation Paper Trail missions on Hard difficulty without using snacks or armor
			setRange(41351, 41356); // Complete all Operation Paper Trail missions taking less than 50% damage
			setRange(41357, 41362); // Complete all Operation Paper Trail missions with over 80% accuracy

			// A SUPERYACHT LIFE
			setRange(41380, 41385); // Complete all Superyacht Life missions on Hard difficulty
			setRange(41386, 41391); // Complete all Superyacht Life missions on Hard difficulty without using snacks or armor
			setRange(41392, 41397); // Complete all Superyacht Life missions taking less than 50% damage
			setRange(41398, 41403); // Complete all Superyacht Life missions with over 80% accuracy

			// GERALD"S LAST PLAY
			setRange(41404, 41409); // Complete a Last Play mission for Gerald
			setRange(41411, 41416); // Complete all Last Play missions on Hard difficulty
			setRange(41417, 41422); // Complete all Last Play missions on Hard difficulty without using snacks or armor
			setRange(41423, 41428); // Complete all Last Play missions taking less than 50% damage
			setRange(41429, 41434); // Complete all Last Play missions with over 80% accuracy

			// PREMIUM DELUXE REPO WORK
			setRange(41436, 41443); // Complete a Repo Work mission for Simeon Yetarian
			setRange(41444, 41451); // Complete all Repo Work missions on Hard difficulty
			setRange(41452, 41459); // Complete all Repo Work missions on Hard difficulty without using snacks or armor
			setRange(41460, 41467); // Complete all Repo Work missions taking less than 50% damage
			setRange(41468, 41475); // Complete all Repo Work missions with over 80% accuracy

			// MADRAZO DISPATCH SERVICES
			setRange(41476, 41481); // Complete a Dispatch Mission for Martin Madrazo
			setRange(41482, 41487); // Complete all Dispatch Missions on Hard difficulty
			setRange(41488, 41493); // Complete all Dispatch Missions on Hard difficulty without using snacks or armor
			setRange(41494, 41499); // Complete all Dispatch Missions taking less than 50% damage
			setRange(41500, 41505); // Complete all Dispatch Missions with over 80% accuracy

			// LOWRIDERS
			setRange(42015, 42022); // Complete a Lowrider mission for Lamar
			setRange(41507, 41514); // Complete all Lowrider missions on Hard difficulty
			setRange(41515, 41522); // Complete all Lowrider missions on Hard difficulty without using snacks or armor
			setRange(41523, 41530); // Complete all Lowrider missions taking less than 50% damage
			setRange(41531, 41538); // Complete all Lowrider missions with over 80% accuracy

			// AGENTS OF SABOTAGE
			setRange(9543, 9546); // Complete all mission challenges for all Files

			// THE CHOP SHOP
			setRange(22082, 22083); // Hire a second Resident DJ

			// LOS SANTOS DRUG WARS
			setRange(41660, 41670); // Complete all missions in The First Dose and The Last Dose without dying

			// AFTER HOURS
			setRange(22067, 22067);       // Complete 25 Club Management missions
			setRange(36868, 36944);       // Source Goods and eject a troublemaker from your Nightclub
			setRange(41989, 41989);       // Fill up your Nightclub safe
			setRange(42089, 42089);       // Unlock 8 Platinum Awards for After Hours
			setRange(50000000, 50000000); // Earn $50,000,000 or more

			// SMUGGLER"S RUN
			setRange(36925, 36932); // Sell all types of Air-Freight Cargo

			// GUNRUNNING
			setRange(42002, 42013); // Upgrade 5 weapons to Mk II
			setRange(36831, 36838); // Complete all Mobile Operations on Hard difficulty in under 10 minutes

			// IMPORT / EXPORT
			setRange(42029, 42036); // Complete a Special Vehicle Work
			setRange(41874, 41883); // Source all vehicles for one Collector
			setRange(41540, 41547); // Complete all Special Vehicle Works on Hard difficulty

			// BIKERS
			setRange(36875, 36887); // Complete a Clubhouse Contract

			// FURTHER ADVENTURES IN FINANCE AND FELONY
			setRange(36892, 36915); // Complete a VIP Work
			setRange(7559, 7553);   // Source all types of Cargo
			setRange(36860, 36865); // Source all types of Special Items

			// THE DIAMOND CASINO & RESORT
			setRange(36844, 36859); // Complete 13 different Casino Work missions
			setRange(41548, 41553); // Complete all Casino Story Missions on Hard difficulty
			setRange(41560, 41565); // Complete all Casino Story Missions on Hard difficulty while taking less than 50% damage
			setRange(41554, 41559); // Complete all Casino Story Missions on Hard difficulty using only pistols
			setRange(41678, 41681); // Steal all variations of loot from the vault on Hard difficulty, without being spotted

			// THE DOOMSDAY HEIST
			setRange(41697, 41699); // Complete the Elite Challenges for all 3 Acts
			setRange(41701, 41704); // Complete the Elite Challenge for each heist

			// ARENA WAR
			setRange(41647, 41655); // Win an Arena Mode

			// ADVERSARY MODE
			setRange(41594, 41646); // Participate in any Adversary Mode
			setRange(41656, 41646); // Participate in 25 different Adversary Modes
			setRange(51339, 41646); // Participate in 25 different Adversary Modes

			// RACING
			setRange(41363, 42151); // Win a Race in 5 different race types

			//DEATHMATCHES
			setRange(41842, 41862); // Own a vehicle in each of the 15 different vehicle classes

		}
	};

    class cayo_awards_unlock : public Command
		{
		using Command::Command;

		virtual void OnCall() override
		{

			// Cayo Perico Awards
			Stats::SetBool("MP0_AWD_INTELGATHER", true);
			Stats::SetBool("MP0_AWD_COMPOUNDINFILT", true);
			Stats::SetBool("MP0_AWD_LOOT_FINDER", true);
			Stats::SetBool("MP0_AWD_MAX_DISRUPT", true);
			Stats::SetBool("MP0_AWD_THE_ISLAND_HEIST", true);
			Stats::SetBool("MP0_AWD_GOING_ALONE", true);
			Stats::SetBool("MP0_AWD_TEAM_WORK", true);
			Stats::SetBool("MP0_AWD_MIXING_UP", true);
			Stats::SetBool("MP0_AWD_PRO_THIEF", true);
			Stats::SetBool("MP0_AWD_CAT_BURGLAR", true);
			Stats::SetBool("MP0_AWD_ONE_OF_THEM", true);
			Stats::SetBool("MP0_AWD_GOLDEN_GUN", true);
			Stats::SetBool("MP0_AWD_ELITE_THIEF", true);
			Stats::SetBool("MP0_AWD_PROFESSIONAL", true);
			Stats::SetBool("MP0_AWD_HELPING_OUT", true);
			Stats::SetBool("MP0_AWD_COURIER", true);
			Stats::SetBool("MP0_AWD_PARTY_VIBES", true);
			Stats::SetBool("MP0_AWD_HELPING_HAND", true);
			/*Stats::SetInt("AWD_LOSTANDFOUND", 45);*/
			std::cout << "Set AWD_SUNSET to 60\n";
			Stats::SetInt("MP0_AWD_SUNSET", 60);
			Stats::SetInt("MP0_AWD_TREASURE_HUNTER", 60);
			Stats::SetInt("MP0_AWD_WRECK_DIVING", 1000000);
			Stats::SetInt("MP0_AWD_KEINEMUSIK", 60);
			Stats::SetInt("MP0_AWD_PALMS_TRAX", 60);
			Stats::SetInt("MP0_AWD_MOODYMANN", 60);
			Stats::SetInt("MP0_AWD_FILL_YOUR_BAGS", 20000000);
			Stats::SetInt("MP0_AWD_WELL_PREPARED", 50);

			// Agent Sabotage Awards
			Stats::SetBool("MP0_AWD_FINEART", true);
			Stats::SetBool("MP0_AWD_BRUTEFORCE", true);
			Stats::SetBool("MP0_AWD_PROJECTBREAK", true);
			Stats::SetBool("MP0_AWD_BLACKBOXFILE", true);
			Stats::SetBool("MP0_AWD_BONUSPOINTS", true);
			Stats::SetBool("MP0_AWD_UPRUNNING", true);
			Stats::SetBool("MP0_AWD_MOGUL", true);
			Stats::SetBool("MP0_AWD_INTEL", true);
			Stats::SetBool("MP0_AWD_IRONMULE", true);
			Stats::SetBool("MP0_AWD_AMMUNITION", true);
			Stats::SetBool("MP0_AWD_DIRDELIVERY", true);
			Stats::SetBool("MP0_AWD_TITANJOB", true);
			Stats::SetBool("MP0_AWD_PERMANENTCON", true);
			Stats::SetInt("MP0_AWD_DARNELLBROSINC", 50);
			Stats::SetInt("MP0_AWD_GET_READY", 50);
			Stats::SetInt("MP0_AWD_CASHINHAND", 5000000);
			Stats::SetInt("MP0_AWD_BROTHERLYLOVE", 50000);
			Stats::SetInt("MP0_AWD_NOTOUTDPT", 5);  
			Stats::SetInt("MP0_AWD_FULSTOCKED", 8);
			Stats::SetInt("MP0_AWD_ARMSINARMS", 50);

			// Bottom Dollar Bounties Awards
			Stats::SetBool("MP0_AWD_HIVALBOUNT1", true);
			Stats::SetBool("MP0_AWD_HIVALBOUNT2", true);
			Stats::SetBool("MP0_AWD_HIVALBOUNT3", true);
			Stats::SetBool("MP0_AWD_HIVALBOUNT4", true);
			Stats::SetBool("MP0_AWD_HIVALBOUNT5", true);
			Stats::SetBool("MP0_AWD_HIVALBOUNT6", true);
			Stats::SetBool("MP0_AWD_ASSONATTACKSWIN", true);
			Stats::SetBool("MP0_AWD_ASSONDEFENDWIN", true);
			Stats::SetBool("MP0_AWD_DISEASECONTROL", true);
			Stats::SetInt("MP0_AWD_BOUNTIES", 50); 
			Stats::SetInt("MP0_AWD_STANBOUNTIES", 50);
			Stats::SetInt("MP0_AWD_BOUNTEARNS", 5000000); 
			Stats::SetInt("MP0_AWD_BAILOFFICSTAFF", 1000000);
			Stats::SetInt("MP0_AWD_DISPATCHWORK", 50);
			Stats::SetInt("MP0_AWD_PIZZATHIS", 50);
			Stats::SetInt("MP0_AWD_ASSONBONUSOBJ", 20);
			Stats::SetInt("MP0_AWD_ASSONHARDDRIVE", 50);
			Stats::SetInt("MP0_AWD_FROSTBITE", 15);

			// The Chop Shop Awards
			Stats::SetBool("MP0_AWD_MAZE_BANK_ROBBERY", true);
			Stats::SetBool("MP0_AWD_CARGO_SHIP_ROBBERY", true);
			Stats::SetBool("MP0_AWD_DIAMOND_CASINO_ROBBERY", true);
			Stats::SetBool("MP0_AWD_MISSION_ROW_ROBBERY", true);
			Stats::SetBool("MP0_AWD_SUBMARINE_ROBBERY", true);
			Stats::SetBool("MP0_AWD_PERFECT_RUN", true);
			Stats::SetBool("MP0_AWD_EXTRA_MILE", true);
			Stats::SetBool("MP0_AWD_BOLINGBROKE", true);
			Stats::SetBool("MP0_AWD_GETTING_SET_UP", true);
			Stats::SetBool("MP0_AWD_CHICKEN_FACTORY_RAID", true);
			Stats::SetBool("MP0_AWD_HELPING_HAND2", true);
			Stats::SetBool("MP0_AWD_SURPRISE_ATTACK", true);
			Stats::SetBool("MP0_AWD_ALL_OUT_RAID", true);
			Stats::SetBool("MP0_AWD_WEAPON_ARSENAL", true);
			Stats::SetBool("MP0_AWD_GETAWAY_VEHICLES", true);
			Stats::SetInt("MP0_AWD_VEHICLE_ROBBERIES", 50);
			Stats::SetInt("MP0_AWD_PREP_WORK", 50);
			Stats::SetInt("MP0_AWD_CAR_DEALER", 5000000); 
			Stats::SetInt("MP0_AWD_SECOND_HAND_PARTS", 5000000); 
			Stats::SetInt("MP0_AWD_TOW_TRUCK_SERVICE", 50);


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

			//The Contract Awards
			Stats::SetBool("MP0_AWD_TEEING_OFF", true);
			Stats::SetBool("MP0_AWD_PARTY_NIGHT", true);
			Stats::SetBool("MP0_AWD_BILLIONAIRE_GAMES", true);
			Stats::SetBool("MP0_AWD_HOOD_PASS", true);
			Stats::SetBool("MP0_AWD_STUDIO_TOUR", true);
			Stats::SetBool("MP0_AWD_DONT_MESS_DRE", true);
			Stats::SetBool("MP0_AWD_BACKUP", true);
			Stats::SetBool("MP0_AWD_SHORTFRANK_1", true);
			Stats::SetBool("MP0_AWD_SHORTFRANK_2", true);
			Stats::SetBool("MP0_AWD_SHORTFRANK_3", true);
			Stats::SetBool("MP0_AWD_CONTR_KILLER", true);
			Stats::SetBool("MP0_AWD_DOGS_BEST_FRIEND", true);
			Stats::SetBool("MP0_AWD_MUSIC_STUDIO", true);
			Stats::SetBool("MP0_AWD_SHORTLAMAR_1", true);
			Stats::SetBool("MP0_AWD_SHORTLAMAR_2", true);
			Stats::SetBool("MP0_AWD_SHORTLAMAR_3", true);
			Stats::SetInt("MP0_AWD_CONTRACTOR", 50);
			Stats::SetInt("MP0_AWD_COLD_CALLER", 50);
			Stats::SetInt("MP0_AWD_PRODUCER", 60);
			Stats::SetInt("MP0_AWD_CONTRACTOR", 50);
			Stats::SetInt("MP0_AWD_COLD_CALLER", 50);
			Stats::SetInt("MP0_AWD_PRODUCER", 60);
			Stats::SetInt("MP0_FIXERTELEPHONEHITSCOMPL", 10);
			Stats::SetInt("MP0_PAYPHONE_BONUS_KILL_METHOD", 10);
			Stats::SetInt("MP0_FIXER_COUNT", 501);
			Stats::SetInt("MP0_FIXER_SC_VEH_RECOVERED", 501);
			Stats::SetInt("MP0_FIXER_SC_VAL_RECOVERED", 501);
			Stats::SetInt("MP0_FIXER_SC_GANG_TERMINATED", 501);
			Stats::SetInt("MP0_FIXER_SC_VIP_RESCUED", 501);
			Stats::SetInt("MP0_FIXER_SC_ASSETS_PROTECTED", 501);
			Stats::SetInt("MP0_FIXER_SC_EQ_DESTROYED", 501);
			Stats::SetInt("MP0_FIXER_EARNINGS", 300000);
			Stats::SetBool("MP0_AWD_TEEING_OFF", true);
			Stats::SetBool("MP0_AWD_PARTY_NIGHT", true);
			Stats::SetBool("MP0_AWD_BILLIONAIRE_GAMES", true);
			Stats::SetBool("MP0_AWD_HOOD_PASS", true);
			Stats::SetBool("MP0_AWD_STUDIO_TOUR", true);
			Stats::SetBool("MP0_AWD_DONT_MESS_DRE", true);
			Stats::SetBool("MP0_AWD_BACKUP", true);
			Stats::SetBool("MP0_AWD_SHORTFRANK_1", true);
			Stats::SetBool("MP0_AWD_SHORTFRANK_2", true);
			Stats::SetBool("MP0_AWD_SHORTFRANK_3", true);
			Stats::SetBool("MP0_AWD_CONTR_KILLER", true);
			Stats::SetBool("MP0_AWD_DOGS_BEST_FRIEND", true);
			Stats::SetBool("MP0_AWD_MUSIC_STUDIO", true);
			Stats::SetBool("MP0_AWD_SHORTLAMAR_1", true);
			Stats::SetBool("MP0_AWD_SHORTLAMAR_2", true);
			Stats::SetBool("MP0_AWD_SHORTLAMAR_3", true);
			Stats::SetBool("MP0_BS_FRANKLIN_DIALOGUE_0", true);
			Stats::SetBool("MP0_BS_FRANKLIN_DIALOGUE_1", true);
			Stats::SetBool("MP0_BS_FRANKLIN_DIALOGUE_2", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_SETUP", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_STRAND", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_PARTY", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_PARTY_2", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_PARTY_F", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_BILL", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_BILL_2", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_BILL_F", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_HOOD", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_HOOD_2", true);
			Stats::SetBool("MP0_BS_IMANI_D_APP_HOOD_F", true);

			// Los Santos Tuners Awards
			Stats::SetBool("MP0_AWD_CAR_CLUB", true);
			Stats::SetBool("MP0_AWD_PRO_CAR_EXPORT", true);
			Stats::SetBool("MP0_AWD_UNION_DEPOSITORY", true);
			Stats::SetBool("MP0_AWD_MILITARY_CONVOY", true);
			Stats::SetBool("MP0_AWD_FLEECA_BANK", true);
			Stats::SetBool("MP0_AWD_FREIGHT_TRAIN", true);
			Stats::SetBool("MP0_AWD_BOLINGBROKE_ASS", true);
			Stats::SetBool("MP0_AWD_IAA_RAID", true);
			Stats::SetBool("MP0_AWD_METH_JOB", true);
			Stats::SetBool("MP0_AWD_BUNKER_RAID", true);
			Stats::SetBool("MP0_AWD_STRAIGHT_TO_VIDEO", true);
			Stats::SetBool("MP0_AWD_MONKEY_C_MONKEY_DO", true);
			Stats::SetBool("MP0_AWD_TRAINED_TO_KILL", true);
			Stats::SetBool("MP0_AWD_DIRECTOR", true);                
			Stats::SetInt("MP0_AWD_CAR_CLUB_MEM", 100);
			Stats::SetInt("MP0_AWD_SPRINTRACER", 50);
			Stats::SetInt("MP0_AWD_STREETRACER", 50);
			Stats::SetInt("MP0_AWD_PURSUITRACER", 50);
			Stats::SetInt("MP0_AWD_TEST_CAR", 240);
			Stats::SetInt("MP0_AWD_AUTO_SHOP", 50);
			Stats::SetInt("MP0_AWD_CAR_EXPORT", 100);
			Stats::SetInt("MP0_AWD_GROUNDWORK", 40);
			Stats::SetInt("MP0_AWD_ROBBERY_CONTRACT", 100);
			Stats::SetInt("MP0_AWD_FACES_OF_DEATH", 30);

			// Los Santos Summer Special
			Stats::SetBool("MP0_AWD_KINGOFQUB3D", true);
			Stats::SetBool("MP0_AWD_QUBISM", true);
			Stats::SetBool("MP0_AWD_QUIBITS", true);
			Stats::SetBool("MP0_AWD_GODOFQUB3D", true);
			Stats::SetBool("MP0_AWD_GOFOR11TH", true);
			Stats::SetBool("MP0_AWD_ELEVENELEVEN", true);

			// Casino Heist Awards






			
		}
	};
		class casino_heist_awards_unlock : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetBool("MP0_AWD_KINGOFQUB3D", true);
				Stats::SetBool("MP0_AWD_QUBISM", true);
				Stats::SetBool("MP0_AWD_QUIBITS", true);
				Stats::SetBool("MP0_AWD_GODOFQUB3D", true);
				Stats::SetBool("MP0_AWD_GOFOR11TH", true);
				Stats::SetBool("MP0_AWD_ELEVENELEVEN", true);
				Stats::SetBool("MP0_AWD_SCOPEOUT", true);
				Stats::SetBool("MP0_AWD_CREWEDUP", true);
				Stats::SetBool("MP0_AWD_MOVINGON", true);
				Stats::SetBool("MP0_AWD_PROMOCAMP", true);
				Stats::SetBool("MP0_AWD_GUNMAN", true);
				Stats::SetBool("MP0_AWD_SMASHNGRAB", true);
				Stats::SetBool("MP0_AWD_INPLAINSI", true);
				Stats::SetBool("MP0_AWD_UNDETECTED", true);
				Stats::SetBool("MP0_AWD_ALLROUND", true);
				Stats::SetBool("MP0_AWD_ELITETHEIF", true);
				Stats::SetBool("MP0_AWD_PRO", true);
				Stats::SetBool("MP0_AWD_SUPPORTACT", true);
				Stats::SetBool("MP0_AWD_SHAFTED", true);
				Stats::SetBool("MP0_AWD_COLLECTOR", true);
				Stats::SetBool("MP0_AWD_DEADEYE", true);
				Stats::SetBool("MP0_AWD_PISTOLSATDAWN", true);
				Stats::SetBool("MP0_AWD_TRAFFICAVOI", true);
				Stats::SetBool("MP0_AWD_CANTCATCHBRA", true);
				Stats::SetBool("MP0_AWD_WIZHARD", true);
				Stats::SetBool("MP0_AWD_APEESCAPE", true);
				Stats::SetBool("MP0_AWD_MONKEYKIND", true);
				Stats::SetBool("MP0_AWD_AQUAAPE", true);
				Stats::SetBool("MP0_AWD_KEEPFAITH", true);
				Stats::SetBool("MP0_AWD_TRUELOVE",true);
				Stats::SetBool("MP0_AWD_NEMESIS",true);
				Stats::SetBool("MP0_AWD_FRIENDZONED",true);


				// Casino Heist Awards
				Stats::SetInt("MP0_AWD_ASTROCHIMP", 3000000);
				Stats::SetInt("MP0_AWD_MASTERFUL", 40000);
				Stats::SetInt("MP0_AWD_PREPARATION", 40);
				Stats::SetInt("MP0_AWD_ASLEEPONJOB", 20);
				Stats::SetInt("MP0_AWD_DAICASHCRAB", 100000);
				Stats::SetInt("MP0_AWD_BIGBRO", 40);
				Stats::SetInt("MP0_AWD_SHARPSHOOTER", 40);
				Stats::SetInt("MP0_AWD_RACECHAMP", 40);
				Stats::SetInt("MP0_AWD_BATSWORD", 1000000);
				Stats::SetInt("MP0_AWD_COINPURSE", 950000);

				for (int i = 0; i < 10; i++) {
					Stats::SetInt(("MP0_IAP_INITIALS_" + std::to_string(i)).c_str(), 50);
					
					Stats::SetInt(("MP0_DG_DEFENDER_INITIALS_" + std::to_string(i)).c_str(),69644);
					Stats::SetInt(("MP0_DG_DEFENDER_SCORE_"+ std::to_string(i)).c_str(),50);
					Stats::SetInt(("MP0_DG_MONKEY_INITIALS_"+std::to_string(i)).c_str(),69644);
					Stats::SetInt(("DG_MONKEY_SCORE_"+std::to_string(i)).c_str(),50);
					Stats::SetInt(("DG_PENETRATOR_INITIALS_"+std::to_string(i)).c_str(),69644);
					Stats::SetInt(("DG_PENETRATOR_SCORE_"+std::to_string(i)).c_str(),50);
					Stats::SetInt(("GGSM_INITIALS_"+std::to_string(i)).c_str(),69644);
					Stats::SetInt(("GGSM_SCORE_"+std::to_string(i)).c_str(),50);
					Stats::SetInt(("TWR_INITIALS_"+std::to_string(i)).c_str(),69644);
					Stats::SetInt(("TWR_SCORE_"+std::to_string(i)).c_str(),50);
				}

				Stats::SetInt("MP0_IAP_SCORE_0", 69644);
				Stats::SetInt("MP0_IAP_SCORE_1", 50333);
				Stats::SetInt("MP0_IAP_SCORE_2", 63512);
				Stats::SetInt("MP0_IAP_SCORE_3", 46136);
				Stats::SetInt("MP0_IAP_SCORE_4", 21638);
				Stats::SetInt("MP0_IAP_SCORE_5", 2133);
				Stats::SetInt("MP0_IAP_SCORE_6", 1215);
				Stats::SetInt("MP0_IAP_SCORE_7", 2444);
				Stats::SetInt("MP0_IAP_SCORE_8", 38023);
				Stats::SetInt("MP0_IAP_SCORE_9", 2233);
				Stats::SetInt("MP0_SCGW_SCORE_1",50);
				Stats::SetInt("MP0_SCGW_SCORE_2",50);
				Stats::SetInt("MP0_SCGW_SCORE_3",50);
				Stats::SetInt("MP0_SCGW_SCORE_4",50);
				Stats::SetInt("MP0_SCGW_SCORE_5",50);
				Stats::SetInt("MP0_SCGW_SCORE_6",50);
				Stats::SetInt("MP0_SCGW_SCORE_7",50);
				Stats::SetInt("MP0_SCGW_SCORE_8",50);
				Stats::SetInt("MP0_SCGW_SCORE_9",50);

				/*Stats::SetInt(("MP0_SCGW_INITIALS_" + std::to_string(i)).c_str(), X);*/
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


				// Integer stats
			    Stats::SetInt("MP0_CAS_HEIST_NOTS", -1);
			    Stats::SetInt("MP0_CH_ARC_CAB_CLAW_TROPHY", -1);
			    Stats::SetInt("MP0_CH_ARC_CAB_LOVE_TROPHY", -1);
			    Stats::SetInt("MP0_SIGNAL_JAMMERS_COLLECTED", 50);
			    Stats::SetInt("MP0_AWD_ODD_JOBS", 52);
			    Stats::SetInt("MP0_AWD_PREPARATION", 40);
			    Stats::SetInt("MP0_AWD_ASLEEPONJOB", 20);
			    Stats::SetInt("MP0_AWD_DAICASHCRAB", 100000);
			    Stats::SetInt("MP0_AWD_BIGBRO", 40);
			    Stats::SetInt("MP0_AWD_SHARPSHOOTER", 40);
			    Stats::SetInt("MP0_AWD_RACECHAMP", 40);
			    Stats::SetInt("MP0_AWD_BATSWORD", 1000000);
			    Stats::SetInt("MP0_AWD_COINPURSE", 950000);
			    Stats::SetInt("MP0_AWD_ASTROCHIMP", 3000000);
			    Stats::SetInt("MP0_AWD_MASTERFUL", 40000);
			    Stats::SetInt("MP0_H3_BOARD_DIALOGUE0", -1);
			    Stats::SetInt("MP0_H3_BOARD_DIALOGUE1", -1);
			    Stats::SetInt("MP0_H3_BOARD_DIALOGUE2", -1);
			    Stats::SetInt("MP0_H3_VEHICLESUSED", -1);

			    // Boolean stats
			    Stats::SetBool("MP0_AWD_FIRST_TIME1", true);
			    Stats::SetBool("MP0_AWD_FIRST_TIME2", true);
			    Stats::SetBool("MP0_AWD_FIRST_TIME3", true);
			    Stats::SetBool("MP0_AWD_FIRST_TIME4", true);
			    Stats::SetBool("MP0_AWD_FIRST_TIME5", true);
			    Stats::SetBool("MP0_AWD_FIRST_TIME6", true);
			    Stats::SetBool("MP0_AWD_ALL_IN_ORDER", true);
			    Stats::SetBool("MP0_AWD_SUPPORTING_ROLE", true);
			    Stats::SetBool("MP0_AWD_LEADER", true);
			    Stats::SetBool("MP0_AWD_ODD_JOBS", true);
			    Stats::SetBool("MP0_AWD_SURVIVALIST", true);
			    Stats::SetBool("MP0_AWD_SCOPEOUT", true);
			    Stats::SetBool("MP0_AWD_CREWEDUP", true);
			    Stats::SetBool("MP0_AWD_MOVINGON", true);
			    Stats::SetBool("MP0_AWD_PROMOCAMP", true);
			    Stats::SetBool("MP0_AWD_GUNMAN", true);
			    Stats::SetBool("MP0_AWD_SMASHNGRAB", true);
			    Stats::SetBool("MP0_AWD_INPLAINSI", true);
			    Stats::SetBool("MP0_AWD_UNDETECTED", true);
			    Stats::SetBool("MP0_AWD_ALLROUND", true);
			    Stats::SetBool("MP0_AWD_ELITETHEIF", true);
			    Stats::SetBool("MP0_AWD_PRO", true);
			    Stats::SetBool("MP0_AWD_SUPPORTACT", true);
			    Stats::SetBool("MP0_AWD_SHAFTED", true);
			    Stats::SetBool("MP0_AWD_COLLECTOR", true);
			    Stats::SetBool("MP0_AWD_DEADEYE", true);
			    Stats::SetBool("MP0_AWD_PISTOLSATDAWN", true);
			    Stats::SetBool("MP0_AWD_TRAFFICAVOI", true);
			    Stats::SetBool("MP0_AWD_CANTCATCHBRA", true);
			    Stats::SetBool("MP0_AWD_WIZHARD", true);
			    Stats::SetBool("MP0_AWD_APEESCAPE", true);
			    Stats::SetBool("MP0_AWD_MONKEYKIND", true);
			    Stats::SetBool("MP0_AWD_AQUAAPE", true);
			    Stats::SetBool("MP0_AWD_KEEPFAITH", true);
			    Stats::SetBool("MP0_AWD_TRUELOVE", true);
			    Stats::SetBool("MP0_AWD_NEMESIS", true);
			    Stats::SetBool("MP0_AWD_FRIENDZONED", true);
			    Stats::SetBool("MP0_VCM_FLOW_CS_RSC_SEEN", true);
			    Stats::SetBool("MP0_VCM_FLOW_CS_BWL_SEEN", true);
			    Stats::SetBool("MP0_VCM_FLOW_CS_MTG_SEEN", true);
			    Stats::SetBool("MP0_VCM_FLOW_CS_OIL_SEEN", true);
			    Stats::SetBool("MP0_VCM_FLOW_CS_DEF_SEEN", true);
			    Stats::SetBool("MP0_VCM_FLOW_CS_FIN_SEEN", true);
			    Stats::SetBool("MP0_CAS_VEHICLE_REWARD", false);
			    Stats::SetBool("MP0_HELP_FURIA", true);
			    Stats::SetBool("MP0_HELP_MINITAN", true);
			    Stats::SetBool("MP0_HELP_YOSEMITE2", true);
			    Stats::SetBool("MP0_HELP_ZHABA", true);
			    Stats::SetBool("MP0_HELP_IMORGEN", true);
			    Stats::SetBool("MP0_HELP_SULTAN2", true);
			    Stats::SetBool("MP0_HELP_VAGRANT", true);
			    Stats::SetBool("MP0_HELP_VSTR", true);
			    Stats::SetBool("MP0_HELP_STRYDER", true);
			    Stats::SetBool("MP0_HELP_SUGOI", true);
			    Stats::SetBool("MP0_HELP_KANJO", true);
			    Stats::SetBool("MP0_HELP_FORMULA", true);
			    Stats::SetBool("MP0_HELP_FORMULA2", true);
			    Stats::SetBool("MP0_HELP_JB7002", true);

			}
		};
	    class nightclub_awards_unlock : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_AWD_DANCE_TO_SOLOMUN", 120);
			    Stats::SetInt("MP0_AWD_DANCE_TO_TALEOFUS", 120);
			    Stats::SetInt("MP0_AWD_DANCE_TO_DIXON", 120);
			    Stats::SetInt("MP0_AWD_DANCE_TO_BLKMAD", 120);
			    Stats::SetInt("MP0_AWD_CLUB_DRUNK", 200);
			    Stats::SetInt("MP0_NIGHTCLUB_VIP_APPEAR", 700);
			    Stats::SetInt("MP0_NIGHTCLUB_JOBS_DONE", 700);
			    Stats::SetInt("MP0_NIGHTCLUB_EARNINGS", 20721002);
			    Stats::SetInt("MP0_HUB_SALES_COMPLETED", 1001);
			    Stats::SetInt("MP0_HUB_EARNINGS", 320721002);
			    Stats::SetInt("MP0_DANCE_COMBO_DURATION_MINS", 3600000);
			    Stats::SetInt("MP0_NIGHTCLUB_PLAYER_APPEAR", 9506);
			    Stats::SetInt("MP0_LIFETIME_HUB_GOODS_SOLD", 784672);
			    Stats::SetInt("MP0_LIFETIME_HUB_GOODS_MADE", 507822);
			    Stats::SetInt("MP0_DANCEPERFECTOWNCLUB", 120);
			    Stats::SetInt("MP0_NUMUNIQUEPLYSINCLUB", 120);
			    Stats::SetInt("MP0_DANCETODIFFDJS", 4);
			    Stats::SetInt("MP0_NIGHTCLUB_HOTSPOT_TIME_MS", 3600000);
			    Stats::SetInt("MP0_NIGHTCLUB_CONT_TOTAL", 20);
			    Stats::SetInt("MP0_NIGHTCLUB_CONT_MISSION", -1);
			    Stats::SetInt("MP0_CLUB_CONTRABAND_MISSION", 1000);
			    Stats::SetInt("MP0_HUB_CONTRABAND_MISSION", 1000);
			    Stats::SetBool("MP0_AWD_CLUB_HOTSPOT", true);
			    Stats::SetBool("MP0_AWD_CLUB_CLUBBER", true);
			    Stats::SetBool("MP0_AWD_CLUB_COORD", true);



		    }
	    };
	    class arena_war_awards_unlock : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_ARN_BS_TRINKET_TICKERS", -1);
			    Stats::SetInt("MP0_ARN_BS_TRINKET_SAVED", -1);
			    Stats::SetInt("MP0_AWD_WATCH_YOUR_STEP", 50);
			    Stats::SetInt("MP0_AWD_TOWER_OFFENSE", 50);
			    Stats::SetInt("MP0_AWD_READY_FOR_WAR", 50);
			    Stats::SetInt("MP0_AWD_THROUGH_A_LENS", 50);
			    Stats::SetInt("MP0_AWD_SPINNER", 50);
			    Stats::SetInt("MP0_AWD_YOUMEANBOOBYTRAPS", 50);
			    Stats::SetInt("MP0_AWD_MASTER_BANDITO", 50);
			    Stats::SetInt("MP0_AWD_SITTING_DUCK", 50);
			    Stats::SetInt("MP0_AWD_CROWDPARTICIPATION", 50);
			    Stats::SetInt("MP0_AWD_KILL_OR_BE_KILLED", 50);
			    Stats::SetInt("MP0_AWD_MASSIVE_SHUNT", 50);
			    Stats::SetInt("MP0_AWD_YOURE_OUTTA_HERE", 200);
			    Stats::SetInt("MP0_AWD_WEVE_GOT_ONE", 50);
			    Stats::SetInt("MP0_AWD_ARENA_WAGEWORKER", 1000000);
			    Stats::SetInt("MP0_AWD_TIME_SERVED", 1000);
			    Stats::SetInt("MP0_AWD_TOP_SCORE", 55000);
			    Stats::SetInt("MP0_AWD_CAREER_WINNER", 1000);
			    Stats::SetInt("MP0_ARENAWARS_SP", 209);
			    Stats::SetInt("MP0_ARENAWARS_SKILL_LEVEL", 20);
			    Stats::SetInt("MP0_ARENAWARS_SP_LIFETIME", 209);
			    Stats::SetInt("MP0_ARENAWARS_AP_TIER", 1000);
			    Stats::SetInt("MP0_ARENAWARS_AP_LIFETIME", 47551850);
			    Stats::SetInt("MP0_ARENAWARS_CARRER_UNLK", 44);
			    Stats::SetInt("MP0_ARN_W_THEME_SCIFI", 1000);
			    Stats::SetInt("MP0_ARN_W_THEME_APOC", 1000);
			    Stats::SetInt("MP0_ARN_W_THEME_CONS", 1000);
			    Stats::SetInt("MP0_ARN_W_PASS_THE_BOMB", 1000);
			    Stats::SetInt("MP0_ARN_W_DETONATION", 1000);
			    Stats::SetInt("MP0_ARN_W_ARCADE_RACE", 1000);
			    Stats::SetInt("MP0_ARN_W_CTF", 1000);
			    Stats::SetInt("MP0_ARN_W_TAG_TEAM", 1000);
			    Stats::SetInt("MP0_ARN_W_DESTR_DERBY", 1000);
			    Stats::SetInt("MP0_ARN_W_CARNAGE", 1000);
			    Stats::SetInt("MP0_ARN_W_MONSTER_JAM", 1000);
			    Stats::SetInt("MP0_ARN_W_GAMES_MASTERS", 1000);
			    Stats::SetInt("MP0_ARN_L_PASS_THE_BOMB", 500);
			    Stats::SetInt("MP0_ARN_L_DETONATION", 500);
			    Stats::SetInt("MP0_ARN_L_ARCADE_RACE", 500);
			    Stats::SetInt("MP0_ARN_L_CTF", 500);
			    Stats::SetInt("MP0_ARN_L_TAG_TEAM", 500);
			    Stats::SetInt("MP0_ARN_L_DESTR_DERBY", 500);
			    Stats::SetInt("MP0_ARN_L_CARNAGE", 500);
			    Stats::SetInt("MP0_ARN_L_MONSTER_JAM", 500);
			    Stats::SetInt("MP0_ARN_L_GAMES_MASTERS", 500);
			    Stats::SetInt("MP0_NUMBER_OF_CHAMP_BOUGHT", 1000);
			    Stats::SetInt("MP0_ARN_SPECTATOR_KILLS", 1000);
			    Stats::SetInt("MP0_ARN_LIFETIME_KILLS", 1000);
			    Stats::SetInt("MP0_ARN_LIFETIME_DEATHS", 500);
			    Stats::SetInt("MP0_ARENAWARS_CARRER_WINS", 1000);
			    Stats::SetInt("MP0_ARENAWARS_CARRER_WINT", 1000);
			    Stats::SetInt("MP0_ARENAWARS_MATCHES_PLYD", 1000);
			    Stats::SetInt("MP0_ARENAWARS_MATCHES_PLYDT", 1000);
			    Stats::SetInt("MP0_ARN_SPEC_BOX_TIME_MS", 86400000);
			    Stats::SetInt("MP0_ARN_SPECTATOR_DRONE", 1000);
			    Stats::SetInt("MP0_ARN_SPECTATOR_CAMS", 1000);
			    Stats::SetInt("MP0_ARN_SMOKE", 1000);
			    Stats::SetInt("MP0_ARN_DRINK", 1000);
			    Stats::SetInt("MP0_ARN_VEH_MONSTER", 31000);
			    Stats::SetInt("MP0_ARN_VEH_MONSTER", 41000);
			    Stats::SetInt("MP0_ARN_VEH_MONSTER", 51000); 
			    Stats::SetInt("MP0_ARN_VEH_CERBERUS", 1000);
			    Stats::SetInt("MP0_ARN_VEH_CERBERUS2", 1000);
			    Stats::SetInt("MP0_ARN_VEH_CERBERUS3", 1000);
			    Stats::SetInt("MP0_ARN_VEH_BRUISER", 1000);
			    Stats::SetInt("MP0_ARN_VEH_BRUISER2", 1000);
			    Stats::SetInt("MP0_ARN_VEH_BRUISER3", 1000);
			    Stats::SetInt("MP0_ARN_VEH_SLAMVAN4", 1000);
			    Stats::SetInt("MP0_ARN_VEH_SLAMVAN5", 1000);
			    Stats::SetInt("MP0_ARN_VEH_SLAMVAN6", 1000);
			    Stats::SetInt("MP0_ARN_VEH_BRUTUS", 1000);
			    Stats::SetInt("MP0_ARN_VEH_BRUTUS2", 1000);
			    Stats::SetInt("MP0_ARN_VEH_BRUTUS3", 1000);
			    Stats::SetInt("MP0_ARN_VEH_SCARAB", 1000);
			    Stats::SetInt("MP0_ARN_VEH_SCARAB2", 1000);
			    Stats::SetInt("MP0_ARN_VEH_SCARAB3", 1000);
			    Stats::SetInt("MP0_ARN_VEH_DOMINATOR4", 1000);
			    Stats::SetInt("MP0_ARN_VEH_DOMINATOR5", 1000);
			    Stats::SetInt("MP0_ARN_VEH_DOMINATOR6", 1000);
			    Stats::SetInt("MP0_ARN_VEH_IMPALER2", 1000);
			    Stats::SetInt("MP0_ARN_VEH_IMPALER3", 1000);
			    Stats::SetInt("MP0_ARN_VEH_IMPALER4", 1000);
			    Stats::SetInt("MP0_ARN_VEH_ISSI4", 1000);
			    Stats::SetInt("MP0_ARN_VEH_ISSI5", 1000);
			    Stats::SetInt("MP0_ARN_VEH_ISSI", 61000);
			    Stats::SetInt("MP0_ARN_VEH_IMPERATOR", 1000);
			    Stats::SetInt("MP0_ARN_VEH_IMPERATOR2", 1000);
			    Stats::SetInt("MP0_ARN_VEH_IMPERATOR3", 1000);
			    Stats::SetInt("MP0_ARN_VEH_ZR380", 1000);
			    Stats::SetInt("MP0_ARN_VEH_ZR3802", 1000);
			    Stats::SetInt("MP0_ARN_VEH_ZR3803", 1000);
			    Stats::SetInt("MP0_ARN_VEH_DEATHBIKE", 1000);
			    Stats::SetInt("MP0_ARN_VEH_DEATHBIKE2", 1000);
			    Stats::SetInt("MP0_ARN_VEH_DEATHBIKE3", 1000);

			    Stats::SetBool("MP0_AWD_BEGINNER", true);
			    Stats::SetBool("MP0_AWD_FIELD_FILLER", true);
			    Stats::SetBool("MP0_AWD_ARMCHAIR_RACER", true);
			    Stats::SetBool("MP0_AWD_LEARNER", true);
			    Stats::SetBool("MP0_AWD_SUNDAY_DRIVER", true);
			    Stats::SetBool("MP0_AWD_THE_ROOKIE", true);
			    Stats::SetBool("MP0_AWD_BUMP_AND_RUN", true);
			    Stats::SetBool("MP0_AWD_GEAR_HEAD", true);
			    Stats::SetBool("MP0_AWD_DOOR_SLAMMER", true);
			    Stats::SetBool("MP0_AWD_HOT_LAP", true);
			    Stats::SetBool("MP0_AWD_ARENA_AMATEUR", true);
			    Stats::SetBool("MP0_AWD_PAINT_TRADER", true);
			    Stats::SetBool("MP0_AWD_SHUNTER", true);
			    Stats::SetBool("MP0_AWD_JOCK", true);
			    Stats::SetBool("MP0_AWD_WARRIOR", true);
			    Stats::SetBool("MP0_AWD_T_BONE", true);
			    Stats::SetBool("MP0_AWD_MAYHEM", true);
			    Stats::SetBool("MP0_AWD_WRECKER", true);
			    Stats::SetBool("MP0_AWD_CRASH_COURSE", true);
			    Stats::SetBool("MP0_AWD_ARENA_LEGEND", true);
			    Stats::SetBool("MP0_AWD_PEGASUS", true);
			    Stats::SetBool("MP0_AWD_UNSTOPPABLE", true);
			    Stats::SetBool("MP0_AWD_CONTACT_SPORT", true);

		    }
	    };
	    class doomsday_awards_unlock : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_GANGOPS_FM_MISSION_PROG", -1);
			    Stats::SetInt("MP0_GANGOPS_FLOW_MISSION_PROG", -1);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_ALLINORDER", 100);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_LOYALTY", 100);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_CRIMMASMD", 100);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_LOYALTY2", 100);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_LOYALTY3", 100);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_CRIMMASMD2", 100);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_CRIMMASMD3", 100);
			    Stats::SetInt("MP0_MPPLY_GANGOPS_SUPPORT", 100);
			    Stats::SetInt("MP0_CR_GANGOP_MORGUE", 10);
			    Stats::SetInt("MP0_CR_GANGOP_DELUXO", 10);
			    Stats::SetInt("MP0_CR_GANGOP_SERVERFARM", 10);
			    Stats::SetInt("MP0_CR_GANGOP_IAABASE_FIN", 10);
			    Stats::SetInt("MP0_CR_GANGOP_STEALOSPREY", 10);
			    Stats::SetInt("MP0_CR_GANGOP_FOUNDRY", 10);
			    Stats::SetInt("MP0_CR_GANGOP_RIOTVAN", 10);
			    Stats::SetInt("MP0_CR_GANGOP_SUBMARINECAR", 10);
			    Stats::SetInt("MP0_CR_GANGOP_SUBMARINE_FIN", 10);
			    Stats::SetInt("MP0_CR_GANGOP_PREDATOR", 10);
			    Stats::SetInt("MP0_CR_GANGOP_BMLAUNCHER", 10);
			    Stats::SetInt("MP0_CR_GANGOP_BCCUSTOM", 10);
			    Stats::SetInt("MP0_CR_GANGOP_STEALTHTANKS", 10);
			    Stats::SetInt("MP0_CR_GANGOP_SPYPLANE", 10);
			    Stats::SetInt("MP0_CR_GANGOP_FINALE", 10);
			    Stats::SetInt("MP0_CR_GANGOP_FINALE_P2", 10);
			    Stats::SetInt("MP0_CR_GANGOP_FINALE_P3", 10);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_IAA", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_SUBMARINE", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_MISSILE", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_ALLINORDER", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_LOYALTY", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_LOYALTY2", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_LOYALTY3", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_CRIMMASMD", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_CRIMMASMD2", true);
			    Stats::SetBool("MP0_MPPLY_AWD_GANGOPS_CRIMMASMD3", true);

		    }
	    };
	    class apartment_heist_awards_unlock : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_AWD_FINISH_HEISTS", 900);
			    Stats::SetInt("MP0_MPPLY_WIN_GOLD_MEDAL_HEISTS", 900);
			    Stats::SetInt("MP0_AWD_DO_HEIST_AS_MEMBER", 900);
			    Stats::SetInt("MP0_AWD_DO_HEIST_AS_THE_LEADER", 900);
			    Stats::SetInt("MP0_AWD_FINISH_HEIST_SETUP_JOB", 900);
			    Stats::SetInt("MP0_AWD_FINISH_HEIST", 900);
			    Stats::SetInt("MP0_HEIST_COMPLETION", 900);
			    Stats::SetInt("MP0_HEISTS_ORGANISED", 900);
			    Stats::SetInt("MP0_AWD_CONTROL_CROWDS", 900);
			    Stats::SetInt("MP0_AWD_WIN_GOLD_MEDAL_HEISTS", 900);
			    Stats::SetInt("MP0_AWD_COMPLETE_HEIST_NOT_DIE", 900);
			    Stats::SetInt("MP0_HEIST_START", 900);
			    Stats::SetInt("MP0_HEIST_END", 900);
			    Stats::SetInt("MP0_CUTSCENE_MID_PRISON", 900);
			    Stats::SetInt("MP0_CUTSCENE_MID_HUMANE", 900);
			    Stats::SetInt("MP0_CUTSCENE_MID_NARC", 900);
			    Stats::SetInt("MP0_CUTSCENE_MID_ORNATE", 900);
			    Stats::SetInt("MP0_CR_FLEECA_PREP_1", 5000);
			    Stats::SetInt("MP0_CR_FLEECA_PREP_2", 5000);
			    Stats::SetInt("MP0_CR_FLEECA_FINALE", 5000);
			    Stats::SetInt("MP0_CR_PRISON_PLANE", 5000);
			    Stats::SetInt("MP0_CR_PRISON_BUS", 5000);
			    Stats::SetInt("MP0_CR_PRISON_STATION", 5000);
			    Stats::SetInt("MP0_CR_PRISON_UNFINISHED_BIZ", 5000);
			    Stats::SetInt("MP0_CR_PRISON_FINALE", 5000);
			    Stats::SetInt("MP0_CR_HUMANE_KEY_CODES", 5000);
			    Stats::SetInt("MP0_CR_HUMANE_ARMORDILLOS", 5000);
			    Stats::SetInt("MP0_CR_HUMANE_EMP", 5000);
			    Stats::SetInt("MP0_CR_HUMANE_VALKYRIE", 5000);
			    Stats::SetInt("MP0_CR_HUMANE_FINALE", 5000);
			    Stats::SetInt("MP0_CR_NARC_COKE", 5000);
			    Stats::SetInt("MP0_CR_NARC_TRASH_TRUCK", 5000);
			    Stats::SetInt("MP0_CR_NARC_BIKERS", 5000);
			    Stats::SetInt("MP0_CR_NARC_WEED", 5000);
			    Stats::SetInt("MP0_CR_NARC_STEAL_METH", 5000);
			    Stats::SetInt("MP0_CR_NARC_FINALE", 5000);
			    Stats::SetInt("MP0_CR_PACIFIC_TRUCKS", 5000);
			    Stats::SetInt("MP0_CR_PACIFIC_WITSEC", 5000);
			    Stats::SetInt("MP0_CR_PACIFIC_HACK", 5000);
			    Stats::SetInt("MP0_CR_PACIFIC_BIKES", 5000);
			    Stats::SetInt("MP0_CR_PACIFIC_CONVOY", 5000);
			    Stats::SetInt("MP0_CR_PACIFIC_FINALE", 5000);
			    Stats::SetInt("MP0_MPPLY_HEIST_ACH_TRACKER", -1);
			    Stats::SetBool("MP0_MPPLY_AWD_COMPLET_HEIST_MEM", true);
			    Stats::SetBool("MP0_MPPLY_AWD_COMPLET_HEIST_1STPER", true);
			    Stats::SetBool("MP0_MPPLY_AWD_FLEECA_FIN", true);
			    Stats::SetBool("MP0_MPPLY_AWD_HST_ORDER", true);
			    Stats::SetBool("MP0_MPPLY_AWD_HST_SAME_TEAM", true);
			    Stats::SetBool("MP0_MPPLY_AWD_HST_ULT_CHAL", true);
			    Stats::SetBool("MP0_MPPLY_AWD_HUMANE_FIN", true);
			    Stats::SetBool("MP0_MPPLY_AWD_PACIFIC_FIN", true);
			    Stats::SetBool("MP0_MPPLY_AWD_PRISON_FIN", true);
			    Stats::SetBool("MP0_MPPLY_AWD_SERIESA_FIN", true);
			    Stats::SetBool("MP0_AWD_FINISH_HEIST_NO_DAMAGE", true);
			    Stats::SetBool("MP0_AWD_SPLIT_HEIST_TAKE_EVENLY", true);
			    Stats::SetBool("MP0_AWD_ALL_ROLES_HEIST", true);
			    Stats::SetBool("MP0_AWD_MATCHING_OUTFIT_HEIST", true);
			    Stats::SetBool("MP0_HEIST_PLANNING_DONE_PRINT", true);
			    Stats::SetBool("MP0_HEIST_PLANNING_DONE_HELP_0", true);
			    Stats::SetBool("MP0_HEIST_PLANNING_DONE_HELP_1", true);
			    Stats::SetBool("MP0_HEIST_PRE_PLAN_DONE_HELP_0", true);
			    Stats::SetBool("MP0_HEIST_CUTS_DONE_FINALE", true);
			    Stats::SetBool("MP0_HEIST_IS_TUTORIAL", false);
			    Stats::SetBool("MP0_HEIST_STRAND_INTRO_DONE", true);
			    Stats::SetBool("MP0_HEIST_CUTS_DONE_ORNATE", true);
			    Stats::SetBool("MP0_HEIST_CUTS_DONE_PRISON", true);
			    Stats::SetBool("MP0_HEIST_CUTS_DONE_BIOLAB", true);
			    Stats::SetBool("MP0_HEIST_CUTS_DONE_NARCOTIC", true);
			    Stats::SetBool("MP0_HEIST_CUTS_DONE_TUTORIAL", true);
			    Stats::SetBool("MP0_HEIST_AWARD_DONE_PREP", true);
			    Stats::SetBool("MP0_HEIST_AWARD_BOUGHT_IN", true);
		    }
	    };
	    class unlock_all_contacts : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_FM_ACT_PHN", -1);
			    Stats::SetInt("MP0_FM_VEH_TX1", -1);
			    Stats::SetInt("MP0_FM_CUT_DONE", -1);
			    Stats::SetInt("MP0_FM_CUT_DONE_2", -1);

			    Stats::SetInt("MP0_FM_ACT_PH2", -1);
			    Stats::SetInt("MP0_FM_ACT_PH3", -1);
			    Stats::SetInt("MP0_FM_ACT_PH4", -1);
			    Stats::SetInt("MP0_FM_ACT_PH5", -1);
			    Stats::SetInt("MP0_FM_ACT_PH6", -1);
			    Stats::SetInt("MP0_FM_ACT_PH7", -1);
			    Stats::SetInt("MP0_FM_ACT_PH8", -1);
			    Stats::SetInt("MP0_FM_ACT_PH9", -1);
		    }
	    };
	    class unlock_some_tattoos : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_AWD_CAR_BOMBS_ENEMY_KILLS", 25); // Trust No One
			    Stats::SetInt("MP0_AWD_HOLD_UP_SHOPS", 20); // Clown, Clown and Gun, Clown Dual Wield & Clown Dual Wield Dollar
			    Stats::SetInt("MP0_AWD_FMBBETWIN", 50000);            // Hustler
			    Stats::SetInt("MP0_AWD_100_HEADSHOTS", 500);          // Skull
			    Stats::SetInt("MP0_AWD_FM_DM_WINS", 50);              // Burning Heart
			    Stats::SetInt("MP0_AWD_RACES_WON", 50);               // Racing Brunette
			    Stats::SetInt("MP0_AWD_FMREVENGEKILLSDM", 50);        // Dragon and Dagger
			    Stats::SetInt("MP0_AWD_FM_DM_TOTALKILLS", 500);       // Melting Skull
			    Stats::SetInt("MP0_LAP_DANCED_BOUGHT", 25);           // Hottie
			    Stats::SetInt("MP0_AWD_FM_TDM_MVP", 50);              // Grim Reaper
			    Stats::SetInt("MP0_AWD_FMKILLBOUNTY", 25);            // Skull and Sword
			    Stats::SetInt("MP0_SNIPERRFL_ENEMY_KILLS", 100);      // Broken Skull
			    Stats::SetBool("MP0_AWD_FMWINEVERYGAMEMODE", true);   // Angel
			    Stats::SetBool("MP0_AWD_FMMOSTKILLSSURVIVE", true);   // The Wages of Sin
			    Stats::SetBool("MP0_AWD_FMRACEWORLDRECHOLDER", true); // Racing Blonde
			    Stats::SetBool("MP0_AWD_FMATTGANGHQ", true);          // Grim Reaper Smoking Gun
			    Stats::SetBool("MP0_AWD_FMKILL3ANDWINGTARACE", true); // Ride or Die
			    Stats::SetBool("MP0_AWD_FMKILLSTREAKSDM", true);      // Flaming Skull

			    Stats::SetInt("MP0_KILLS_PLAYERS", 250);          // Blank Scroll
			    Stats::SetInt("MP0_KILLS_PLAYERS", 500);          // Embellished Scroll
			    Stats::SetInt("MP0_KILLS_PLAYERS", 1000);         // Seven Deadly Sins
			    Stats::SetBool("MP0_AWD_FMFULLYMODDEDCAR", true); // Los Santos Customs

			    Stats::SetPackedBool(15887, true); // Lucky 7s Tattoo - Male
			    Stats::SetPackedBool(15894, true); // The Royals Tattoo - Male
			    Stats::SetPackedBool(15898, true); // Lucky 7s Tattoo - Female
			    Stats::SetPackedBool(15905, true); // The Royals Tattoo - Female
			    Stats::SetPackedBool(15737, true); //Alien Tatto - Male
			    Stats::SetPackedBool(15748, true); //Alien Tatto - Female

				for (int i = 0; i <= 53; i++) {
					std::string statName = "MP0_TATTOO_FM_UNLOCKS_" + std::to_string(i);
					Stats::SetInt(statName.c_str(), -1);
				}
				Stats::SetInt("MP0_TATTOO_FM_CURRENT_32", -1);
		    }
	    };
	    class unlock_some_trade_price : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_GANGOPS_FLOW_BITSET_MISS0", -1);
			    Stats::SetInt("MP0_LFETIME_HANGAR_BUY_UNDETAK", 42);
			    Stats::SetInt("MP0_LFETIME_HANGAR_BUY_COMPLET", 42);
			    Stats::SetInt("MP0_AT_FLOW_IMPEXP_NUM", 32);
			    Stats::SetInt("MP0_AT_FLOW_VEHICLE_BS", -1);
			    Stats::SetInt("MP0_WVM_FLOW_VEHICLE_BS", -1);
			    Stats::SetInt("MP0_H3_BOARD_DIALOGUE0", -1);
			    Stats::SetInt("MP0_H3_BOARD_DIALOGUE1", -1);
			    Stats::SetInt("MP0_H3_BOARD_DIALOGUE2", -1);
			    Stats::SetInt("MP0_H3_VEHICLESUSED", -1);
			    Stats::SetInt("MP0_WAM_FLOW_VEHICLE_BS", -1);

			    Stats::SetBool("MP0_HELP_VETO", true);
			    Stats::SetBool("MP0_HELP_VETO2", true);
			    Stats::SetBool("MP0_HELP_ITALIRSX", true);
			    Stats::SetBool("MP0_HELP_BRIOSO2", true);
			    Stats::SetBool("MP0_HELP_MANCHEZ2", true);
			    Stats::SetBool("MP0_HELP_SLAMTRUCK", true);
			    Stats::SetBool("MP0_HELP_VETIR", true);
			    Stats::SetBool("MP0_HELP_SQUADDIE", true);
			    Stats::SetBool("MP0_HELP_DINGY5", true);
			    Stats::SetBool("MP0_HELP_VERUS", true);
			    Stats::SetBool("MP0_HELP_WEEVIL", true);
			    Stats::SetBool("MP0_HELP_VEHUNTUNER", true);
			    Stats::SetBool("MP0_FIXER_VEH_HELP", true);
			    Stats::SetBool("MP0_HELP_DOMINATOR7", true);
			    Stats::SetBool("MP0_HELP_JESTER4", true);
			    Stats::SetBool("MP0_HELP_FUTO2", true);
			    Stats::SetBool("MP0_HELP_DOMINATOR8", true);
			    Stats::SetBool("MP0_HELP_PREVION", true);
			    Stats::SetBool("MP0_HELP_GROWLER", true);
			    Stats::SetBool("MP0_HELP_COMET6", true);
			    Stats::SetBool("MP0_HELP_VECTRE", true);
			    Stats::SetBool("MP0_HELP_SULTAN3", true);
			    Stats::SetBool("MP0_HELP_CYPHER", true);

		    }
	    };
	    class unlock_shotaro : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("CRDEADLINE", -1);
		    }
	    };
	    class unlock_taxi_livery : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("AWD_TAXIDRIVER", 100);
		    }
	    };
	    class SCMembershipBypass : public LoopedCommand
	    {
		    using LoopedCommand::LoopedCommand;

		    virtual void OnTick() override
		    {
			    if (auto scMembershipData = SC_MEMBERSHIP_DATA::Get())
			    {
				    *Tunables::GetTunable("GTAO_AUTO_REFRESH_FREQUENCY_IN_FRAMES"_J).As<int*>() = INT_MAX;
				    scMembershipData->Flags.Set(eSCMembershipFlags::MEMBERSHIP_CHECKED);
				    scMembershipData->Flags.Clear(eSCMembershipFlags::CHECK_MEMBERSHIP);
				    scMembershipData->Flags.Set(eSCMembershipFlags::DISABLE_MEMBERSHIP_CHECK);
				    scMembershipData->HasMembership = TRUE;
			    }
		    }
	    };
		class unlock_removed_vehicle : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
				auto base = ScriptGlobal(262145);
				int offsets[] = {
					22565, 14708, 34371, 34373, 34451, 34349, 34527, 34533, 17356, 17372, 34589, 35492, 34415, 34417, 34465, 34573,
					34499, 34495, 34493, 34511, 28191, 34501, 34333, 34551, 34553, 34409, 34365, 34569, 34571, 23726, 34401, 17230,
					25367, 34335, 34337, 34339, 34341, 34325, 18947, 18948, 22564, 17229, 34367, 34331, 21603, 17364, 25369, 34431,
					34453, 34497, 25387, 34455, 34403, 17355, 34399, 34323, 34437, 23717, 17358, 17370, 34467, 34433, 34435, 34351,
					34411, 34587, 34565, 34523, 34369, 34563, 34559, 34481, 19951, 34581, 34577, 22556, 34585, 34473, 25386, 22563,
					34457, 34513, 22557, 28201, 34405, 34541, 34459, 34535, 34429, 25383, 34439, 34387, 34361, 34557, 34503, 34583,
					28830, 28190, 25379, 17232, 34353, 34555, 34597, 23729, 14703, 25385, 34471, 25396, 34443, 34441, 25397, 34591,
					34475, 34561, 25389, 34485, 34567, 34427, 34529, 34595, 22560, 34505, 34355, 34357, 21607, 17363, 17373, 34483,
					17223, 34507, 34531, 21606, 22558, 22562, 34593, 34521, 34377, 34393, 34469, 34489, 19953, 34509, 25393, 34463,
					34461, 17366, 34515, 22561, 22554, 34519, 34345, 34347, 34547, 34579, 28831, 34445, 34575, 34359, 34479, 23781,
					34539, 34383, 34381, 34379, 34545, 22551, 34343, 34549, 34525, 23780, 34537, 34327, 29156, 20830, 17371, 25370,
					17221, 34407, 34477, 26330, 34375, 29605, 34487, 22566, 34397, 34543, 34517, 17369, 20828, 34423, 34425, 34395,
					34447, 34449, 25384, 17354, 25381, 34599 , 
					12025 // Halloween Vehicles
				};
				for (int i = 0; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
					*base.At(offsets[i]).As<int*>() = 1;
				}
		    }
	    };
		class unlock_all_parachutes : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetPackedBool(3609,true)
				Stats::SetPackedBool(31791, true);
				Stats::SetPackedBool(31792, true);
				Stats::SetPackedBool(31793, true);
				Stats::SetPackedBool(31794, true);
				Stats::SetPackedBool(31795, true);
				Stats::SetPackedBool(31796, true);

				Stats::SetPackedBool(34378, true);
				Stats::SetPackedBool(34379, true);

		    }
	    };
		class Fastrun_Reload_unlock : public Command
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
				Stats::SetInt("MP0_CHAR_FM_ABILITY_1_UNLCK", -1);
				Stats::SetInt("MP0_CHAR_ABILITY_1_UNLCK", -1);
				Stats::SetInt("MP0_CHAR_FM_ABILITY_2_UNLCK", -1);
				Stats::SetInt("MP0_CHAR_ABILITY_2_UNLCK", -1);
				Stats::SetInt("MP0_CHAR_FM_ABILITY_3_UNLCK", -1);
				Stats::SetInt("MP0_CHAR_ABILITY_3_UNLCK", -1);
		    }
	    };
		







	static BunkerResearch _BunkerResearch{"bunkerresearch", "Unlock Bunker Research", "Unlocks all Bunker Research Items"};
	static unlock_clothing _UnlockClothing{"unlockclothing", "Unlock Areana War Clothing", "Unlocks all Areana War Clothing"};
	static Casino_Heist_Clothing _UnlockCasinoHeistClothing{"unlockcasinoheistclothing", "Unlock Casino Clothing", "Unlocks Casino Heist Clothing"};
	static Genderchange _unlockgenderchange{"unlockgenderchange", "Unlock Gender Change", "Allows to Change Gender"};
	static CareerProgress_Rewards _CareerProgress_Rewards{"careerprogressreawards", "Unlock Career Progress", "Unlocks all Career Progress Stats"};
	static cayo_awards_unlock _cayo_awards_unlock{"cayoawardsunlock", "Unlock Cayo Perico Awards", "Unlocks all Awards"};
	static agent_sabotage_awards_unlock _agent_sabotage_awards_unlock{"agentsabotageawardsunlock", "Unlock Agent Sabotage Awards", "Unlocks all Agent of Sabotage Awards"};
	static bottom_dollar_bounties_awards_unlock _bottom_dollar_bounties_awards_unlock{"bottomdollarbountiesawardsunlock", "Unlock Bottom Dollar Bounties Awards", "Unlocks all Bottom Dollar Bounties Awards"};
	static the_chop_shop_awards_unlock  _the_chop_shop_awards_unlock{"thechopshopawardsunlock", "Unlock Chop Shop Awards", "Unlocks all the Chop Shop Awards"};
	static los_santos_drug_wars_awards_unlock  _los_santos_drug_wars_awards_unlock{"lossantosdrugwarsunlock", "Unlock Los Drug Wars Awards", "Unlocks all the Los Santos Drug wars Awards"};
	static the_contract_awards_unlock  _the_contract_awards_unlock{"thecontractawardsunlock", "Unlock The Contract Awards", "Unlocks all the Contract Awards"};
	static los_santos_tuners_awards_unlock  _los_santos_tuners_awards_unlock{"lossantostunersawardsunlock", "Unlock Los Santos Tuners Awards", "Unlocks all the Los Santos Tuners Awards"};
	static los_santos_summer_special_awards_unlock  _los_santos_summer_special_awards_unlock{"lossantossummerspecialawardsunlock", "Unlock Los Santos Summer Special Awards", "Unlocks all Los Santos Summer Special Awards"};
	static casino_heist_awards_unlock _casino_heist_awards_unlock{"casinoheistawardsunlock", "Unlock Casino Heist Awards", "Unlocks all Casino Heist Awards"};
	static nightclub_awards_unlock _nightclub_awards_unlock{"nightclubawardsunlock", "Unlock Nightclub Awards", "Unlocks all Nightclub Awards"};
	static arena_war_awards_unlock _arena_war_awards_unlock{"arenawarawardsunlock", "Unlock Arena War Awards", "Unlocks all Arena War Awards"};
	static doomsday_awards_unlock _doomsday_awards_unlock{"doomsdayawardsunlock", "Unlock Doomsday Awards", "Unlocks all Doomsday Awards"};
	static apartment_heist_awards_unlock _apartment_heist_awards_unlock{"apartmentheistawardsunlock", "Unlock Apartment Heist Awards", "Unlocks all Apartment Heist Awards"};
	static unlock_all_contacts _unlock_all_contacts{"unlockallcontacts", "Unlock All Contacts", "Unlocks all Contacts"};
	static unlock_some_tattoos _unlock_some_tattoos{"unlocksometattoos", "Unlock All Tattoos", "Unlocks All Tattoos"};
	static unlock_some_trade_price _unlock_some_trade_price{"unlocksometradeprice", "Unlock Some Trade Price", "Unlocks some Trade Prices"};
	static unlock_shotaro _unlock_shotaro{"unlockshotaro", "Unlock Shotaro", "Unlocks the Shotaro"};
	static unlock_taxi_livery _unlock_taxi_livery{"unclocktaxilivery", "Unlock Taxi Livery", "Unlocks the Taxi Livery"};
	/*static unlock_vanilla_unicorn_award _unlock_vanilla_unicorn_award{"unlockvanillaunicornaward", "Unlock Vanilla Unicorn Award", "Unlocks the Vanilla Unicorn Award"};*/
	static SCMembershipBypass _SCMembershipBypass{"scmembership_bypass", "SC Membership Bypass", "Bypasses Social Club membership checks for tunables"};
}
