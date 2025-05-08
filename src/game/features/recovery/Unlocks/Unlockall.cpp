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
	namespace Unlock Clothing
	{
        class Genderchange : public Command
        {
            using Command::Command;

            virtual void OnCall() override
            {
                Stats::SetInt("ALLOW_GENDER_CHANGE", 1)
            }
        }
        class FreeORB : public Command
        {
            using Command::Command;

            virtual void OnCall() override
            {
                Stats::SetPackedBool(PACKED_MP_BOOL_AWARD_XMAS2017_CANNON_GIFT, TRUE);
                Stats::SetPackedBool(PACKED_MP_BOOL_PURCHASE_XMAS2017_CANNON_GIFT, FALSE);
            }
        }
        class Casino_Heist_Clothing : public Command
        {
            using Command::Command;

            virtual void OnCall() override
            {
                const std::vector<int> CasinoHeist_ids = {
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
                for (int id : CasinoHeist_ids)
                {
                    Stats::SetPackedBool(id, TRUE); 
                }
            }
        }
        class AreanaWar_Clothing : public Command
        {
            using Command::Command;

            virtual void OnCall() override
            {
                const std::vector<int> Areanawar_ids = {
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
                    25270, // Red/Green/Blue Isn't Free Tee 
                    25271, // All Raider Tops
                    25272, // All Leather Feather Tops
                    25273, // All Mercenary Tops
                    25274, // Benedict Light Beer Hoodie
                    25275, // Taco Bomb Hoodie
                    25276, // Cluckin'Bell Logo Bomb Hoodie
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
                    25289, // Cluckin'Bell Logo Hoodie
                    25290, // Lemons Hoodie
                    25291, // Tacos Hoodie
                    25292, // Burger Shot Pattern Sweater
                    25293, // Burger Shot Logo Sweater
                    25294, // Burger Shot Sweater
                    25295, // Green/White Sprunk Sweater
                    25296, // Wigwam Sweater
                    25297, // Taco Bomb Chili Sweater
                    25298, // Green/Yellow Bomb Sweater
                    25299, // Cluckin'Bell Logo Bomb Sweater
                    25300, // Blue Cluckin'Bell Sweater
                    25301, // Black Cluckin'Bell Sweater
                    25302, // Infectious/Red eCola Sweater
                    25303, // Orange/Red MeTV Sweater
                    25304, // Magenta/Cyan Heat Sweater
                    25305, // Degenatron Sweater
                    25306, // Red/Black Pisswasser Sweater
                    25307, // Bolt Burger Sweater
                    25308, // Lucky Plucker Logo Bomb Sweater
                    25309, // Lucky Plucker Sweater
                    25310, // Dark Red/Red/Black/Blue Burger Shot Hockey Shirt
                    25311, // Black/Blue Cluckin' Bell Hockey Shirt
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
                    25322, // Cluckin'Bell Logo Tee
                    25323, // Cluckin'Bell Black Tee
                    25324, // Cluckin'Bell Filled Logo Tee
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
                    25375, // Yellow/Blue Cluckin'Bell Cap
                    25377, // Cluckin'Bell Logos Cap
                    25378, // Pink/Purple/Black Hotdogs Cap
                    25379, // Green/White/- Taco Bomb Cap
                    25382, // Red/White Lucky Plucker Cap
                    25383, // Lucky Plucker White/Red Pattern Cap
                    25386, // Black/White Pisswasser Cap
                    25390, // Taco Canvas Hat
                    25391, // Burger Shot Canvas Hat
                    25392, // Cluckin'Bell Canvas Hat
                    25393, // Hotdogs Canvas Hat
                };
                for (int id : Areanawar_ids)
                {
                    Stats::SetPackedBool(id, TRUE); 
                }
            }
        }

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

		static BunkerResearch _UnlockBunkerResearch{"unlockbunkerresearch", "Unlock Bunker Research", "Unlocks all Bunker Research Items"};
        static AreanaWar_Clothing _UnlockAreanaWarClothing{"unlockareanawarclothing", "Unlock Areana War Clothing", "Unlocks all Areana War Clothing"};
        static Casino_Heist_Clothing _UnlockCasinoHeistClothing{"unlockcasinoheistclothing", "Unlock Casino Clothing", "Unlocks Casino Heist Clothing"};
        static FreeORB _unlockOrbitalCannonfree{"unlockorbitalcannonfree", "Free Orbital Cannon", "Unlocks Orbital cannon for Free as GIFT from XMAS 2017"};
        static Genderchange _unlockgenderchange{"unlockgenderchange","Unlock Gender Change", "Allows to Change Gender"};
	}
}