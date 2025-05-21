#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "core/util/Joaat.hpp"
#include "game/backend/Tunables.hpp"
#include "types/script/globals/SC_MEMBERSHIP_DATA.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/gta/ScriptLocal.hpp"

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
			Stats::SetPackedBool(15491, TRUE); // Weaponized Tampa Heavy Chassis Upgrade
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
			Stats::SetPackedBool(15492, TRUE); // Brushstroke Camo Mk II Weapon Livery
			Stats::SetPackedBool(15493, TRUE); // Skull Mk II Weapon Livery
			Stats::SetPackedBool(15494, TRUE); // Sessanta Nove Mk II Weapon Livery
			Stats::SetPackedBool(15495, TRUE); // Perseus Mk II Weapon Livery
			Stats::SetPackedBool(15496, TRUE); // Leopard Mk II Weapon Livery
			Stats::SetPackedBool(15497, TRUE); // Zebra Mk II Weapon Livery
			Stats::SetPackedBool(15498, TRUE); // Geometric Mk II Weapon Livery
			Stats::SetPackedBool(15499, TRUE); // Boom! Mk II Weapon Livery
		}
	};
	class unlock_clothing : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetPackedBool(25244, TRUE); // Yellow/Blue Robot Bodysuit
			Stats::SetPackedBool(25245, TRUE); // Blue/Red Hero Bodysuit
			Stats::SetPackedBool(25246, TRUE); // Green/Purple Shapes Bodysuit
			Stats::SetPackedBool(25247, TRUE); // Blue&Pink/Red&Green Contours Bodysuit
			Stats::SetPackedBool(25248, TRUE); // Green/Purple Martian Bodysuit
			Stats::SetPackedBool(25249, TRUE); // Blue/Red Reptile 
			Stats::SetPackedBool(25250, TRUE); // Blue/Pink Galaxy Bodysuit
			Stats::SetPackedBool(25000, TRUE); // Red&Blue/Blue&Green Nebula Bodysuit
			Stats::SetPackedBool(25251, TRUE); // All Space Creature Suits
			Stats::SetPackedBool(25252, TRUE); // All Space Cyclops Suits
			Stats::SetPackedBool(25253, TRUE); // All Space Horro Suits
			Stats::SetPackedBool(25254, TRUE); // All Retro Suits
			Stats::SetPackedBool(25255, TRUE); // All Astronaut Suits
			Stats::SetPackedBool(25256, TRUE); // All Space Traveler Suits
			Stats::SetPackedBool(25257, TRUE); // Pogo Space Monkey
			Stats::SetPackedBool(25258, TRUE); // Republican Space Ranger
			Stats::SetPackedBool(25265, TRUE); // Green/Yellow/White/Black Space Rangers Tee
			Stats::SetPackedBool(25266, TRUE); // Green/Black Space Ranger Logo Tee
			Stats::SetPackedBool(25267, TRUE); // Yellow/White Phases Tee
			Stats::SetPackedBool(25268, TRUE); // Pink/Blue Rocket Splash Tee
			Stats::SetPackedBool(24977, TRUE); // Pink/Black Spacesuit Alien Tee
			Stats::SetPackedBool(25269, TRUE); // Pink/Blue/Purple Moons Tee
			Stats::SetPackedBool(25270, TRUE); // Red/Green/Blue Isn't Free Tee
			Stats::SetPackedBool(25271, TRUE); // All Raider Tops
			Stats::SetPackedBool(25272, TRUE); // All Leather Feather Tops
			Stats::SetPackedBool(25273, TRUE); // All Mercenary Tops
			Stats::SetPackedBool(25274, TRUE); // Benedict Light Beer Hoodie
			Stats::SetPackedBool(25275, TRUE); // Taco Bomb Hoodie
			Stats::SetPackedBool(25276, TRUE); // Cluckin'Bell Logo Bomb Hoodie
			Stats::SetPackedBool(25277, TRUE); // Patriot Beer Hoodie
			Stats::SetPackedBool(25278, TRUE); // Pisswasser Hoodie
			Stats::SetPackedBool(25279, TRUE); // Burger Shot Hoodie
			Stats::SetPackedBool(25280, TRUE); // Corn Dog Hoodie
			Stats::SetPackedBool(25281, TRUE); // Donut Hoodie
			Stats::SetPackedBool(25282, TRUE); // Lucky Plucker Hoodie
			Stats::SetPackedBool(25289, TRUE); // Cluckin"Bell Logo Hoodie
			Stats::SetPackedBool(25290, TRUE); // Lemons Hoodie
			Stats::SetPackedBool(25291, TRUE); // Tacos Hoodie
			Stats::SetPackedBool(25292, TRUE); // Burger Shot Pattern Sweater
			Stats::SetPackedBool(25293, TRUE); // Burger Shot Logo Sweater
			Stats::SetPackedBool(25294, TRUE); // Burger Shot Sweater
			Stats::SetPackedBool(25295, TRUE); // Green/White Sprunk Sweater
			Stats::SetPackedBool(25296, TRUE); // Wigwam Sweater
			Stats::SetPackedBool(25297, TRUE); // Taco Bomb Chili Sweater
			Stats::SetPackedBool(25298, TRUE); // Green/Yellow Bomb Sweater
			Stats::SetPackedBool(25299, TRUE); // Cluckin"Bell Logo Bomb Sweater
			Stats::SetPackedBool(25300, TRUE); // Blue Cluckin"Bell Sweater
			Stats::SetPackedBool(25301, TRUE); // Black Cluckin"Bell Sweater
			Stats::SetPackedBool(25302, TRUE); // Infectious/Red eCola Sweater
			Stats::SetPackedBool(25303, TRUE); // Orange/Red MeTV Sweater
			Stats::SetPackedBool(25304, TRUE); // Magenta/Cyan Heat Sweater
			Stats::SetPackedBool(25305, TRUE); // Degenatron Sweater
			Stats::SetPackedBool(25306, TRUE); // Red/Black Pisswasser Sweater
			Stats::SetPackedBool(25307, TRUE); // Bolt Burger Sweater
			Stats::SetPackedBool(25308, TRUE); // Lucky Plucker Logo Bomb Sweater
			Stats::SetPackedBool(25309, TRUE); // Lucky Plucker Sweater
			Stats::SetPackedBool(25310, TRUE); // Dark Red/Red/Black/Blue Burger Shot Hockey Shirt
			Stats::SetPackedBool(25311, TRUE); // Black/Blue Cluckin" Bell Hockey Shirt
			Stats::SetPackedBool(25312, TRUE); // Wigwam Hockey Shirt
			Stats::SetPackedBool(25313, TRUE); // Redwood Hockey Shirt
			Stats::SetPackedBool(25314, TRUE); // Bean Machine Hockey Shirt
			Stats::SetPackedBool(25315, TRUE); // Red eCola Hockey Shirt
			Stats::SetPackedBool(25316, TRUE); // Black eCola Hockey Shirt
			Stats::SetPackedBool(25317, TRUE); // Blue/Black Phat Chips Hockey Shirt
			Stats::SetPackedBool(25318, TRUE); // Green/Dark Green Sprunk Hockey Shirt
			Stats::SetPackedBool(25319, TRUE); // Sprunk Classic Hockey Shirt
			Stats::SetPackedBool(25320, TRUE); // Burger Shot Black Tee
			Stats::SetPackedBool(25321, TRUE); // Burger Shot Logo Tee
			Stats::SetPackedBool(25322, TRUE); // Cluckin"Bell Logo Tee
			Stats::SetPackedBool(25323, TRUE); // Cluckin"Bell Black Tee
			Stats::SetPackedBool(25324, TRUE); // Cluckin"Bell Filled Logo Tee
			Stats::SetPackedBool(25325, TRUE); // eCola Black Tee
			Stats::SetPackedBool(25326, TRUE); // Lucky Plucker Tee
			Stats::SetPackedBool(25327, TRUE); // Pisswasser Tee
			Stats::SetPackedBool(25328, TRUE); // Sprunk Tee
			Stats::SetPackedBool(25329, TRUE); // Taco Bomb Chili Tee
			Stats::SetPackedBool(25330, TRUE); // Taco Bomb Black Tee
			Stats::SetPackedBool(25331, TRUE); // Up-n-Atom Hamburgers Tee
			Stats::SetPackedBool(25332, TRUE); // Up-n-Atom Tee
			Stats::SetPackedBool(25333, TRUE); // Wigwam Tee
			Stats::SetPackedBool(25334, TRUE); // Degenatron ROYGBIV Tee
			Stats::SetPackedBool(25335, TRUE); // CNT Tee
			Stats::SetPackedBool(25336, TRUE); // Qub3d Tee
			Stats::SetPackedBool(25337, TRUE); // Righteous Slaughter Tee
			Stats::SetPackedBool(25338, TRUE); // Space Monkey Full Tee
			Stats::SetPackedBool(25339, TRUE); // Space Monkey Pixel Tee
			Stats::SetPackedBool(25340, TRUE); // Space Monkey Enemy Tee
			Stats::SetPackedBool(25341, TRUE); // Burger Shot Tee
			Stats::SetPackedBool(25342, TRUE); // Heat Rises Tee
			Stats::SetPackedBool(25343, TRUE); // Space Monkey Logo Tee
			Stats::SetPackedBool(25344, TRUE); // Space Monkey Suit Tee
			Stats::SetPackedBool(25345, TRUE); // Space Monkey Face Tee
			Stats::SetPackedBool(25346, TRUE); // Space Monkey Mosaic Tee
			Stats::SetPackedBool(25347, TRUE); // Bolt Burger Logo Tee
			Stats::SetPackedBool(24970, TRUE); // Bolt Burger Hunger Tee
			Stats::SetPackedBool(25348, TRUE); // Exsorbeo 720 Tee
			Stats::SetPackedBool(25349, TRUE); // Heat Blue Logo Tee
			Stats::SetPackedBool(25350, TRUE); // Heat Blue Ball Logo Tee
			Stats::SetPackedBool(25351, TRUE); // Heat Blue Pop Art Logo Tee
			Stats::SetPackedBool(25352, TRUE); // MeTV Blue 90s Tee
			Stats::SetPackedBool(25353, TRUE); // MeTV Blue Safari Tee
			Stats::SetPackedBool(25354, TRUE); // Burger Shot Target Tee
			Stats::SetPackedBool(25355, TRUE); // eCola Infectious Tee
			Stats::SetPackedBool(25356, TRUE); // Up-n-Atom White Tee
			Stats::SetPackedBool(25357, TRUE); // Jock Cranley Patriot Tee
			Stats::SetPackedBool(25358, TRUE); // CCC TV Tee
			Stats::SetPackedBool(25359, TRUE); // Degenatron Logo Tee
			Stats::SetPackedBool(25360, TRUE); // eCola White Tee
			Stats::SetPackedBool(25361, TRUE); // eCola Pass It On Tee
			Stats::SetPackedBool(25362, TRUE); // TW@ Tee
		    Stats::SetPackedBool(25363, TRUE); // All Chain Pants
			Stats::SetPackedBool(25364, TRUE); // All Chain Shorts
			Stats::SetPackedBool(25365, TRUE); // All Stitch Pants
			Stats::SetPackedBool(25366, TRUE); // All Raider Pants // Raider Shoes+Pants
			Stats::SetPackedBool(25367, TRUE); // All Light Ups
			Stats::SetPackedBool(25368, TRUE); // All Flaming Skull Boots
			Stats::SetPackedBool(25369, TRUE); // All Skull Harness Boots
			Stats::SetPackedBool(25370, TRUE); // All Plated Boots
			Stats::SetPackedBool(25371, TRUE); // Burger Shot Fries/Burgers Cap
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
			Stats::SetPackedBool(28225, TRUE); // Refuse Collectors
			Stats::SetPackedBool(28226, TRUE); // Undertakers
			Stats::SetPackedBool(28227, TRUE); // Valet Outfits
			Stats::SetPackedBool(28229, TRUE); // Prision Guards
			Stats::SetPackedBool(28230, TRUE); // FIB Suits
			Stats::SetPackedBool(28232, TRUE); // Gruppe Sechs Gear
			Stats::SetPackedBool(28233, TRUE); // Bugstars Uniforms
			Stats::SetPackedBool(28234, TRUE); // Maintenance
			Stats::SetPackedBool(28235, TRUE); // Yung Ancestors
			Stats::SetPackedBool(28236, TRUE); // Firefighter Gear
			Stats::SetPackedBool(28237, TRUE); // Orderly Armor
			Stats::SetPackedBool(28238, TRUE); // Upscale Armor
			Stats::SetPackedBool(28239, TRUE); // Evening Armor
			Stats::SetPackedBool(28240, TRUE); // Reinforced: Padded Combat
			Stats::SetPackedBool(28241, TRUE); // Reinforced: Bulk Combat
			Stats::SetPackedBool(28242, TRUE); // Reinforced: Compact Combat
			Stats::SetPackedBool(28243, TRUE); // Balaclava Crook
			Stats::SetPackedBool(28244, TRUE); // Classic Crook
			Stats::SetPackedBool(28245, TRUE); // High-end Crook
			Stats::SetPackedBool(28246, TRUE); // Infiltration: Upgraded Tech
			Stats::SetPackedBool(28247, TRUE); // Infiltration: Advanced Tech
			Stats::SetPackedBool(28248, TRUE); // Infiltration: Modernized Tech
			Stats::SetPackedBool(51217, TRUE); // Gold Pisswasser Shorts
		    Stats::SetPackedBool(51240, TRUE); // Silver Gun Necklace
		    Stats::SetPackedBool(51241, TRUE); // Black Gun Necklace
		    Stats::SetPackedBool(51242, TRUE); // Gold Gun Necklace
		    Stats::SetPackedBool(51243, TRUE); // Rose Gun Necklace
		    Stats::SetPackedBool(51244, TRUE); // Bronze Gun Necklace
		    Stats::SetPackedBool(51221, TRUE); // Halloween Spooky Tee
		    Stats::SetPackedBool(51216, TRUE); // Pisswasser Good Time Tee
		    Stats::SetPackedBool(51220, TRUE); // Día de Muertos Tee
		    Stats::SetPackedBool(51239, TRUE); // Rockstar Red Logo Sweater
		    Stats::SetPackedBool(51219, TRUE); // Mid Autumn Festival Sundress (female)
		    Stats::SetPackedBool(51218, TRUE); // Mid Autumn Festival Shirt
		    Stats::SetPackedBool(51245, TRUE); // Black Yeti Fall Sweater
		    Stats::SetPackedBool(51246, TRUE); // White Yeti Fall Sweater
		    Stats::SetPackedBool(51247, TRUE); // Red Yeti Fall Sweater
		    Stats::SetPackedBool(42287, TRUE); // Pizza This... Caps & Outfit
		    Stats::SetPackedBool(51215, TRUE); // Brown Alpine Hat / Alpine Outfit
		    Stats::SetPackedBool(42257, TRUE); // The Street Artist
		    Stats::SetPackedBool(42268, TRUE); // Ghosts Exposed Outfit
		    Stats::SetPackedBool(42286, TRUE); // Ludendorff Survivor
		    Stats::SetPackedBool(51237, TRUE); // Tan Turkey
		    Stats::SetPackedBool(51238, TRUE); // Brown Turkey
		    Stats::SetPackedBool(51234, TRUE); // Orange Glow Skeleton Onesie
		    Stats::SetPackedBool(51235, TRUE); // Purple Glow Skeleton Onesie
		    Stats::SetPackedBool(51236, TRUE); // Green Glow Skeleton Onesie
		    Stats::SetPackedBool(51258, TRUE); // Pizza This... Tee
		    Stats::SetPackedBool(32407, TRUE); // Bottom Dollar Jacket
		    Stats::SetPackedBool(32408, TRUE); // The Bottom Dollar
		    Stats::SetPackedBool(51250, TRUE); // Cobalt Jackal Racing Pants
		    Stats::SetPackedBool(51251, TRUE); // Khaki 247 Chino Pants
		    Stats::SetPackedBool(51248, TRUE); // The Diamond Jackpot Tee
		    Stats::SetPackedBool(51249, TRUE); // Cobalt Jackal Racing Jersey
		    Stats::SetPackedBool(51253, TRUE); // Purple Güffy Cardigan
		    Stats::SetPackedBool(51252, TRUE); // Demon Biker Jacket
		    Stats::SetPackedBool(51254, TRUE); // SA Denim Biker Jacket
		    Stats::SetPackedBool(51255, TRUE); // Green 247 Shirt
		    Stats::SetPackedBool(51256, TRUE); // Barbed Wire Shirt
			*ScriptGlobal(262145).At(23812).As<int*>() = 1; // Unlocks BASE5 T-Shirt
			Stats::SetPackedBool(28185, TRUE); // Pixel Pete's Tee
			Stats::SetPackedBool(28186, TRUE); // Wonderama Tee
			Stats::SetPackedBool(28187, TRUE); // Warehouse Tee
			Stats::SetPackedBool(28188, TRUE); // Eight Bit Tee
			Stats::SetPackedBool(28189, TRUE); // Insert Coin Tee
			Stats::SetPackedBool(28190, TRUE); // Videogeddon Tee
			Stats::SetPackedBool(28191, TRUE); // Nazar Speaks Tee
			Stats::SetPackedBool(28197, TRUE); // Badlands Revenge II Gunshot Tee
			Stats::SetPackedBool(28198, TRUE); // Badlands Revenge II Eagle Tee
			Stats::SetPackedBool(28199, TRUE); // Badlands Revenge II Pixtro Tee
			Stats::SetPackedBool(28200, TRUE); // Badlands Revenge II Romance Tee, Bear Tee, Help Me Tee & Retro Tee
			Stats::SetPackedBool(28201, TRUE); // Race and Chase Decor Tee
			Stats::SetPackedBool(28202, TRUE); // Race and Chase Vehicles Tee
			Stats::SetPackedBool(28203, TRUE); // Race and Chase Finish Tee
			Stats::SetPackedBool(28204, TRUE); // Crotch Rockets Tee, Street Legal Tee & Get Truckin' Tee
			Stats::SetPackedBool(28205, TRUE); // Wizard's Ruin Loot Tee
			Stats::SetPackedBool(28206, TRUE); // The Wizard's Ruin Rescue Tee
			Stats::SetPackedBool(28207, TRUE); // The Wizard's Ruin Vow Tee
			Stats::SetPackedBool(28208, TRUE); // Thog Mighty Sword Tee, Thog Tee & Thog Bod Tee
			Stats::SetPackedBool(28209, TRUE); // Space Monkey 3 Tee
			Stats::SetPackedBool(28210, TRUE); // Space Monkey Space Crafts Tee
			Stats::SetPackedBool(28211, TRUE); // Space Monkey Pixel Tee
			Stats::SetPackedBool(28212, TRUE); // Space Monkey Boss Fights Tee, Radioactive Space Monkey Tee & Space Monkey Art Tee
			Stats::SetPackedBool(28213, TRUE); // Monkey's Paradise Tee
			Stats::SetPackedBool(28214, TRUE); // Retro Defender of the Faith Tee
			Stats::SetPackedBool(28215, TRUE); // Penetrator Tee
			Stats::SetPackedBool(28216, TRUE); // Defender of the Faith Tee
			Stats::SetPackedBool(28217, TRUE); // Love Professor His Tee & Love Professor Hers Tee
			Stats::SetPackedBool(28218, TRUE); // Love Professor Nemesis Tee
			Stats::SetPackedBool(28219, TRUE); // Love Professor Friendzoned Tee
			Stats::SetPackedBool(28220, TRUE); // Love Professor Secrets Tee & Love Professor Score Tee
			Stats::SetPackedBool(28221, TRUE); // Shiny Wasabi Kitty Claw Tee
			Stats::SetPackedBool(28222, TRUE); // Pixtro Tee, Akedo Tee & Arcade Trophy Tee
			Stats::SetPackedBool(28224, TRUE); // White Dog With Cone Tee, Yellow Dog With Cone Tee, Dog With Cone Slip-Ons & Dog With Cone Chain
			Stats::SetPackedBool(28225, TRUE); // Refuse Collectors (Outfits)
			Stats::SetPackedBool(28226, TRUE); // Undertakers (Outfit)
			Stats::SetPackedBool(28227, TRUE); // Valet Outfits
			Stats::SetPackedBool(28229, TRUE); // Prison Guards (Outfits)
			Stats::SetPackedBool(28230, TRUE); // FIB Suits (Outfits)
			Stats::SetPackedBool(28232, TRUE); // Gruppe Sechs Gear (Outfits)
			Stats::SetPackedBool(28233, TRUE); // Bugstars Uniforms (Outfits)
			Stats::SetPackedBool(28234, TRUE); // Maintenance (Outfits)
			Stats::SetPackedBool(28235, TRUE); // Yung Ancestors (Outfits)
			Stats::SetPackedBool(28236, TRUE); // Firefighter Gear (Outfits)
			Stats::SetPackedBool(28237, TRUE); // Orderly Armor (Outfits)
			Stats::SetPackedBool(28238, TRUE); // Upscale Armor (Outfits)
			Stats::SetPackedBool(28239, TRUE); // Evening Armor (Outfits)
			Stats::SetPackedBool(28240, TRUE); // Reinforced: Padded Combat (Outfits)
			Stats::SetPackedBool(28241, TRUE); // Reinforced: Bulk Combat (Outfits)
			Stats::SetPackedBool(28242, TRUE); // Reinforced: Compact Combat (Outfits)
			Stats::SetPackedBool(28243, TRUE); // Balaclava Crook (Outfits)
			Stats::SetPackedBool(28244, TRUE); // Classic Crook (Outfits)
			Stats::SetPackedBool(28245, TRUE); // High-end Crook (Outfits)
			Stats::SetPackedBool(28246, TRUE); // Infiltration: Upgraded Tech (Outfits)
			Stats::SetPackedBool(28247, TRUE); // Infiltration: Advanced Tech (Outfits)
			Stats::SetPackedBool(28248, TRUE); // Infiltration: Modernized Tech (Outfits)
			Stats::SetPackedBool(28249, TRUE); // Degenatron Glitch Tee
			Stats::SetPackedBool(28254, TRUE); // Get Metal Tee
			Stats::SetPackedBool(28255, TRUE); // 11 11 Tee
			Stats::SetPackedBool(28254, TRUE); // Axe of Fury Tee (part 1)
			Stats::SetPackedBool(28255, TRUE); // Axe of Fury Tee (part 2)
			Stats::SetPackedBool(30254, TRUE); // King Of QUB3D Tee
			Stats::SetPackedBool(30255, TRUE); // Qubism Tee
			Stats::SetPackedBool(30256, TRUE); // God Of QUB3D Tee
			Stats::SetPackedBool(30257, TRUE); // QUB3D Boxart Tee
			Stats::SetPackedBool(30258, TRUE); // Qub3d Qub3s Tee
			Stats::SetPackedBool(31760, TRUE); // Faces of Death Tee
			Stats::SetPackedBool(31761, TRUE); // Straight to Video Tee
			Stats::SetPackedBool(31762, TRUE); // Monkey See Monkey Die Tee
			Stats::SetPackedBool(31763, TRUE); // Trained to Kill Tee
			Stats::SetPackedBool(31764, TRUE); // The Director Tee
			Stats::SetPackedBool(31783, TRUE); // Bearsy (Mask)
			Stats::SetPackedBool(28393, TRUE); // Badlands Revenge II Retro Tee (Male)
			Stats::SetPackedBool(28394, TRUE); // Badlands Revenge II Pixtro Tee (Male)
			Stats::SetPackedBool(28395, TRUE); // Degenatron Glitch Tee (Male)
			Stats::SetPackedBool(28396, TRUE); // Degenatron Logo Tee (Male)
			Stats::SetPackedBool(28397, TRUE); // The Wizard's Ruin Rescue Tee (Male)
			Stats::SetPackedBool(28398, TRUE); // The Wizard's Ruin Vow Tee (Male)
			Stats::SetPackedBool(28399, TRUE); // Space Monkey Art Tee (Male)
			Stats::SetPackedBool(28400, TRUE); // Crotch Rockets Tee (Male)
			Stats::SetPackedBool(28401, TRUE); // Street Legal Tee (Male)
			Stats::SetPackedBool(28402, TRUE); // Get Truckin' Tee (Male)
			Stats::SetPackedBool(28403, TRUE); // Arcade Trophy Tee (Male)
			Stats::SetPackedBool(28404, TRUE); // Videogeddon Tee (Male)
			Stats::SetPackedBool(28405, TRUE); // Insert Coin Tee (Male)
			Stats::SetPackedBool(28406, TRUE); // Plushie Princess Tee (Male)
			Stats::SetPackedBool(28407, TRUE); // Plushie Wasabi Kitty Tee (Male)
			Stats::SetPackedBool(28408, TRUE); // Plushie Master Tee (Male)
			Stats::SetPackedBool(28409, TRUE); // Plushie Muffy Tee (Male)
			Stats::SetPackedBool(28410, TRUE); // Plushie Humpy Tee (Male)
			Stats::SetPackedBool(28411, TRUE); // Plushie Saki Tee (Male)
			Stats::SetPackedBool(28412, TRUE); // Plushie Grindy Tee (Male)
			Stats::SetPackedBool(28413, TRUE); // Plushie [removed]ie Tee (Male)
			Stats::SetPackedBool(28414, TRUE); // Plushie Smoker Tee (Male)
			Stats::SetPackedBool(28415, TRUE); // Shiny Wasabi Kitty Claw Tee (Male)
			Stats::SetPackedBool(28416, TRUE); // Nazar Speaks Tee (Male)
			Stats::SetPackedBool(28447, TRUE); // 11 11 Tee (Male)
			Stats::SetPackedBool(28448, TRUE); // King Of QUB3D Tee (Male)
			Stats::SetPackedBool(28449, TRUE); // Qubism Tee (Male)
			Stats::SetPackedBool(28450, TRUE); // God Of QUB3D Tee (Male)
			Stats::SetPackedBool(28451, TRUE); // QUB3D Boxart Tee (Male)
			Stats::SetPackedBool(30418, TRUE); // Faces of Death Tee (Male)
			Stats::SetPackedBool(30419, TRUE); // Straight to Video Tee (Male)
			Stats::SetPackedBool(30420, TRUE); // Monkey See Monkey Die Tee (Male)
			Stats::SetPackedBool(30421, TRUE); // Trained to Kill Tee (Male)
			Stats::SetPackedBool(30422, TRUE); // The Director Tee (Male)
			Stats::SetPackedBool(28404, TRUE); // Badlands Revenge II Retro Tee (Female)
			Stats::SetPackedBool(28405, TRUE); // Badlands Revenge II Pixtro Tee (Female)
			Stats::SetPackedBool(28406, TRUE); // Degenatron Glitch Tee (Female)
			Stats::SetPackedBool(28407, TRUE); // Degenatron Logo Tee (Female)
			Stats::SetPackedBool(28408, TRUE); // The Wizard's Ruin Rescue Tee (Female)
			Stats::SetPackedBool(28409, TRUE); // The Wizard's Ruin Vow Tee (Female)
			Stats::SetPackedBool(28410, TRUE); // Space Monkey Art Tee (Female)
			Stats::SetPackedBool(28411, TRUE); // Crotch Rockets Tee (Female)
			Stats::SetPackedBool(28412, TRUE); // Street Legal Tee (Female)
			Stats::SetPackedBool(28413, TRUE); // Get Truckin' Tee (Female)
			Stats::SetPackedBool(28414, TRUE); // Arcade Trophy Tee (Female)
			Stats::SetPackedBool(28415, TRUE); // Videogeddon Tee (Female)
			Stats::SetPackedBool(28416, TRUE); // Insert Coin Tee (Female)
			Stats::SetPackedBool(28417, TRUE); // Plushie Princess Tee (Female)
			Stats::SetPackedBool(28418, TRUE); // Plushie Wasabi Kitty Tee (Female)
			Stats::SetPackedBool(28419, TRUE); // Plushie Master Tee (Female)
			Stats::SetPackedBool(28420, TRUE); // Plushie Muffy Tee (Female)
			Stats::SetPackedBool(28421, TRUE); // Plushie Humpy Tee (Female)
			Stats::SetPackedBool(28422, TRUE); // Plushie Saki Tee (Female)
			Stats::SetPackedBool(28423, TRUE); // Plushie Grindy Tee (Female)
			Stats::SetPackedBool(28424, TRUE); // Plushie [removed]ie Tee (Female)
			Stats::SetPackedBool(28425, TRUE); // Plushie Smoker Tee (Female)
			Stats::SetPackedBool(28426, TRUE); // Shiny Wasabi Kitty Claw Tee (Female)
			Stats::SetPackedBool(28427, TRUE); // Nazar Speaks Tee (Female)
			Stats::SetPackedBool(28458, TRUE); // 11 11 Tee (Female)
			Stats::SetPackedBool(28459, TRUE); // King Of QUB3D Tee (Female)
			Stats::SetPackedBool(28460, TRUE); // Qubism Tee (Female)
			Stats::SetPackedBool(28461, TRUE); // God Of QUB3D Tee (Female)
			Stats::SetPackedBool(28462, TRUE); // QUB3D Boxart Tee (Female)
			Stats::SetPackedBool(30429, TRUE); // Faces of Death Tee (Female)
			Stats::SetPackedBool(30430, TRUE); // Straight to Video Tee (Female)
			Stats::SetPackedBool(30431, TRUE); // Monkey See Monkey Die Tee (Female)
			Stats::SetPackedBool(30432, TRUE); // Trained to Kill Tee (Female)
			Stats::SetPackedBool(30433, TRUE); // The Director Tee (Female)
			Stats::SetPackedBool(7475, TRUE);  // Meltdown T-Shirt
			Stats::SetPackedBool(25006, TRUE); // Kifflom Tee
			Stats::SetPackedBool(28171, TRUE); // Green Reindeer Lights Bodysuit
			Stats::SetPackedBool(28172, TRUE); // Ho-Ho-Ho Sweater
			Stats::SetPackedBool(28173, TRUE); // Traditional Festive Lights Bodysuit
			Stats::SetPackedBool(28174, TRUE); // Yellow Reindeer Lights Bodysuit
			Stats::SetPackedBool(28175, TRUE); // Neon Festive Lights Bodysuit
			Stats::SetPackedBool(27184, TRUE); // Invade and Persuade Enemies Tee
			Stats::SetPackedBool(27185, TRUE); // Invade and Persuade Oil Tee
			Stats::SetPackedBool(27186, TRUE); // Invade and Persuade Tour Tee
			Stats::SetPackedBool(27187, TRUE); // Invade and Persuade Green Tee
			Stats::SetPackedBool(27188, TRUE); // Invade and Persuade RON Tee
			Stats::SetPackedBool(27189, TRUE); // Street Crimes Hoods Tee
			Stats::SetPackedBool(27190, TRUE); // Street Crimes Punks Tee
			Stats::SetPackedBool(27191, TRUE); // Street Crimes Yokels Tee
			Stats::SetPackedBool(27192, TRUE); // Street Crimes Bikers Tee
			Stats::SetPackedBool(27193, TRUE); // Street Crimes Action Tee
			Stats::SetPackedBool(25271, TRUE); // Apocalyptic Raider Top set
			Stats::SetPackedBool(25272, TRUE); // Apocalyptic Leather Feather Top set
			Stats::SetPackedBool(25273, TRUE); // Apocalyptic Mercenary Vest set
			Stats::SetPackedBool(25274, TRUE); // Benedict Light Beer Hoodie
			Stats::SetPackedBool(25275, TRUE); // Taco Bomb Hoodie
			Stats::SetPackedBool(25276, TRUE); // Cluckin' Bell Logo Bomb Hoodie
			Stats::SetPackedBool(25277, TRUE); // Patriot Beer Hoodie
			Stats::SetPackedBool(25278, TRUE); // [removed]wasser Hoodie
			Stats::SetPackedBool(25279, TRUE); // Burger Shot Hoodie
			Stats::SetPackedBool(25280, TRUE); // Corn Dog Hoodie
			Stats::SetPackedBool(25281, TRUE); // Donut Hoodie
			Stats::SetPackedBool(25282, TRUE); // Lucky Plucker Hoodie
			Stats::SetPackedBool(25283, TRUE); // Logger Light Hoodie
			Stats::SetPackedBool(25284, TRUE); // Pizza Hoodie
			Stats::SetPackedBool(25285, TRUE); // Fries Hoodie
			Stats::SetPackedBool(25286, TRUE); // Mushrooms Hoodie
			Stats::SetPackedBool(25287, TRUE); // Redwood Hoodie
			Stats::SetPackedBool(25288, TRUE); // eCola Infectious Hoodie
			Stats::SetPackedBool(25289, TRUE); // Cluckin' Bell Logo Hoodie
			Stats::SetPackedBool(25290, TRUE); // Lemons Hoodie
			Stats::SetPackedBool(25291, TRUE); // Tacos Hoodie
			Stats::SetPackedBool(25292, TRUE); // Burger Shot Pattern Sweater
			Stats::SetPackedBool(25293, TRUE); // Burger Shot Logo Sweater
			Stats::SetPackedBool(25294, TRUE); // Burger Shot Sweater
			Stats::SetPackedBool(25295, TRUE); // Sprunk Sweater set
			Stats::SetPackedBool(25296, TRUE); // Wigwam Sweater
			Stats::SetPackedBool(25297, TRUE); // Taco Bomb Chili Sweater
			Stats::SetPackedBool(25298, TRUE); // Taco Bomb Sweater set
			Stats::SetPackedBool(25299, TRUE); // Cluckin' Bell Logo Bomb Sweater
			Stats::SetPackedBool(25300, TRUE); // Blue Cluckin' Bell Sweater
			Stats::SetPackedBool(25301, TRUE); // Black Cluckin' Bell Sweater
			Stats::SetPackedBool(25302, TRUE); // eCola Sweater set
			Stats::SetPackedBool(25303, TRUE); // MeTV Sweater set
			Stats::SetPackedBool(25304, TRUE); // Heat Sweater set
			Stats::SetPackedBool(25305, TRUE); // Degenatron Sweater
			Stats::SetPackedBool(25306, TRUE); // [removed]wasser Sweater set
			Stats::SetPackedBool(25307, TRUE); // Bolt Burger Sweater
			Stats::SetPackedBool(25308, TRUE); // Lucky Plucker Logo Bomb Sweater
			Stats::SetPackedBool(25309, TRUE); // Lucky Plucker Sweater
			Stats::SetPackedBool(24970, TRUE); // Bolt Burger Hunger Tee
			Stats::SetPackedBool(24977, TRUE); // Spacesuit Alien Tee set
			Stats::SetPackedBool(25265, TRUE); // Space Rangers Tee set
			Stats::SetPackedBool(25266, TRUE); // Space Ranger Logo Tee set
			Stats::SetPackedBool(25267, TRUE); // Phases Tee set
			Stats::SetPackedBool(25268, TRUE); // Rocket Splash Tee set
			Stats::SetPackedBool(25269, TRUE); // Two Moons Tee set
			Stats::SetPackedBool(25270, TRUE); // Freedom Isn't Free Tee set
			Stats::SetPackedBool(25310, TRUE); // Burger Shot Hockey Shirt set
			Stats::SetPackedBool(25311, TRUE); // Cluckin' Bell Hockey Shirt set
			Stats::SetPackedBool(25312, TRUE); // Wigwam Hockey Shirt
			Stats::SetPackedBool(25313, TRUE); // Redwood Hockey Shirt
			Stats::SetPackedBool(25314, TRUE); // Bean Machine Hockey Shirt
			Stats::SetPackedBool(25315, TRUE); // Red eCola Hockey Shirt
			Stats::SetPackedBool(25316, TRUE); // Black eCola Hockey Shirt
			Stats::SetPackedBool(25317, TRUE); // Phat Chips Hockey Shirt set
			Stats::SetPackedBool(25318, TRUE); // Sprunk Hockey Shirt set
			Stats::SetPackedBool(25319, TRUE); // Sprunk Classic Hockey Shirt
			Stats::SetPackedBool(25320, TRUE); // Burger Shot Black Tee
			Stats::SetPackedBool(25321, TRUE); // Burger Shot Logo Tee
			Stats::SetPackedBool(25322, TRUE); // Cluckin' Bell Logo Tee
			Stats::SetPackedBool(25323, TRUE); // Cluckin' Bell Black Tee
			Stats::SetPackedBool(25325, TRUE); // eCola Black Tee
			Stats::SetPackedBool(25326, TRUE); // Lucky Plucker Tee
			Stats::SetPackedBool(25327, TRUE); // [removed]wasser Tee
			Stats::SetPackedBool(25328, TRUE); // Sprunk Tee
			Stats::SetPackedBool(25329, TRUE); // Taco Bomb Chili Tee
			Stats::SetPackedBool(25330, TRUE); // Taco Bomb Black Tee
			Stats::SetPackedBool(25331, TRUE); // Up-n-Atom Hamburgers Tee
			Stats::SetPackedBool(25332, TRUE); // Up-n-Atom Logo Tee
			Stats::SetPackedBool(25333, TRUE); // Wigwam Tee
			Stats::SetPackedBool(25334, TRUE); // Degenatron ROYGBIV Tee
			Stats::SetPackedBool(25335, TRUE); // CNT Tee
			Stats::SetPackedBool(25336, TRUE); // Qub3d Tee
			Stats::SetPackedBool(25337, TRUE); // Righteous Slaughter Tee
			Stats::SetPackedBool(25338, TRUE); // Space Monkey Full Tee
			Stats::SetPackedBool(25339, TRUE); // Space Monkey Pixel Tee
			Stats::SetPackedBool(25340, TRUE); // Space Monkey Enemy Tee
			Stats::SetPackedBool(25341, TRUE); // Burger Shot Bleeder Tee
			Stats::SetPackedBool(25342, TRUE); // Heat Rises Tee
			Stats::SetPackedBool(25343, TRUE); // Space Monkey Logo Tee
			Stats::SetPackedBool(25344, TRUE); // Space Monkey Suit Tee
			Stats::SetPackedBool(25345, TRUE); // Space Monkey Face Tee
			Stats::SetPackedBool(25346, TRUE); // Space Monkey Mosaic Tee
			Stats::SetPackedBool(25347, TRUE); // Bolt Burger Logo Tee
			Stats::SetPackedBool(25348, TRUE); // Exsorbeo 720 Tee
			Stats::SetPackedBool(25349, TRUE); // Heat Ball Logo Tee set
			Stats::SetPackedBool(25350, TRUE); // Heat Logo Tee set
			Stats::SetPackedBool(25351, TRUE); // Heat Pop Art Logo Tee set
			Stats::SetPackedBool(25352, TRUE); // MeTV Logo Tee set
			Stats::SetPackedBool(25353, TRUE); // MeTV 90s Tee set
			Stats::SetPackedBool(25354, TRUE); // Burger Shot Target Tee
			Stats::SetPackedBool(25355, TRUE); // eCola Infectious Tee
			Stats::SetPackedBool(25356, TRUE); // Up-n-Atom White Tee
			Stats::SetPackedBool(25357, TRUE); // Jock Cranley Patriot Tee
			Stats::SetPackedBool(25358, TRUE); // CCC TV Tee
			Stats::SetPackedBool(25359, TRUE); // Degenatron Logo Tee
			Stats::SetPackedBool(25360, TRUE); // eCola White Tee
			Stats::SetPackedBool(25361, TRUE); // eCola Pass It On Tee
			Stats::SetPackedBool(25362, TRUE); // Tw@ Tee
			Stats::SetPackedBool(25363, TRUE); // Chain Pants set
			Stats::SetPackedBool(25364, TRUE); // Chain Shorts set
			Stats::SetPackedBool(25365, TRUE); // Leather Stitch Pants set
			Stats::SetPackedBool(25366, TRUE); // Raider Pants set
			Stats::SetPackedBool(25367, TRUE); // Light Ups Shoes set
			Stats::SetPackedBool(25368, TRUE); // Flaming Skull Boots set
			Stats::SetPackedBool(25369, TRUE); // Skull Harness Boots set
			Stats::SetPackedBool(25370, TRUE); // Plated Boots set
			Stats::SetPackedBool(25000, TRUE); // Nebula Bodysuit set
			Stats::SetPackedBool(25244, TRUE); // Robot Bodysuit set
			Stats::SetPackedBool(25245, TRUE); // Hero Bodysuit set
			Stats::SetPackedBool(25246, TRUE); // Shapes Bodysuit set
			Stats::SetPackedBool(25247, TRUE); // Contours Bodysuit set
			Stats::SetPackedBool(25248, TRUE); // Martian Bodysuit set
			Stats::SetPackedBool(25249, TRUE); // Reptile Bodysuit set
			Stats::SetPackedBool(25250, TRUE); // Galaxy Bodysuit set
			Stats::SetPackedBool(25251, TRUE); // Space Creature Suits
			Stats::SetPackedBool(25252, TRUE); // Space Cyclops Suits
			Stats::SetPackedBool(25253, TRUE); // Space Horror Suits
			Stats::SetPackedBool(25254, TRUE); // Retro Spacesuits
			Stats::SetPackedBool(25255, TRUE); // Astronaut Suits
			Stats::SetPackedBool(25256, TRUE); // Space Traveler Suits
			Stats::SetPackedBool(25257, TRUE); // Character Suits: Pogo Space Monkey
			Stats::SetPackedBool(25258, TRUE); // Character Suits: Republican Space Ranger
			Stats::SetPackedBool(25134, TRUE); // Apocalypse Scarab - Livery set
			Stats::SetPackedBool(25137, TRUE); // Future Shock Scarab - Livery set
			Stats::SetPackedBool(25138, TRUE); // Nightmare Scarab - Livery set
			Stats::SetPackedBool(25168, TRUE); // Apocalypse Scarab - Body Spikes set
			Stats::SetPackedBool(25169, TRUE); // Future Shock Scarab - Body Spikes set
			Stats::SetPackedBool(25170, TRUE); // Nightmare Scarab - Body Spikes set
			Stats::SetPackedBool(15562, TRUE); // White Coil Tee
			Stats::SetPackedBool(15563, TRUE); // Red Coil Tee
			Stats::SetPackedBool(15564, TRUE); // Black Coil Tee
			Stats::SetPackedBool(15565, TRUE); // Black Ammu-Nation Tee
			Stats::SetPackedBool(15566, TRUE); // White Ammu-Nation Tee
			Stats::SetPackedBool(15567, TRUE); // Yellow Warstock Tee and Yellow Warstock Tee (Tucked)
			Stats::SetPackedBool(15568, TRUE); // Green Warstock Tee
			Stats::SetPackedBool(31755, TRUE); // Race and Chase Arcade Machine for the Auto Shop
			Stats::SetPackedBool(26968, TRUE); // The Impotent Rage (Outfit & Haircut)
			Stats::SetPackedBool(26969, TRUE); // The High Roller (Outfit)
			Stats::SetPackedBool(27068, TRUE); // White Benny's T-Shirt
			Stats::SetPackedBool(27082, TRUE); // Death Defying T-Shirt
			Stats::SetPackedBool(27084, TRUE); // Showroom T-Shirt
			Stats::SetPackedBool(30408, TRUE); // Blue Keinemusik Tee (Male)
			Stats::SetPackedBool(30409, TRUE); // Moodymann Tee (Male)
			Stats::SetPackedBool(30410, TRUE); // Palms Trax Tee (Male)
			Stats::SetPackedBool(30418, TRUE); // White Keinemusik Tee (Female)
			Stats::SetPackedBool(30419, TRUE); // Blue Keinemusik Tee (Female)
			Stats::SetPackedBool(30420, TRUE); // Moodymann Tee (Female)
			Stats::SetPackedBool(30421, TRUE); // Palms Trax Tee (Female)
			Stats::SetPackedBool(28452, TRUE); // Channel X Aged Tee (Male)
			Stats::SetPackedBool(28453, TRUE); // Rebel Radio Aged Tee (Male)
			Stats::SetPackedBool(28454, TRUE); // LSUR Aged Tee (Male)
			Stats::SetPackedBool(28455, TRUE); // Steel Horse Solid Logo Aged Tee (Male)
			Stats::SetPackedBool(28456, TRUE); // Black Western Logo Aged Tee (Male)
			Stats::SetPackedBool(28457, TRUE); // White Nagasaki Aged Tee (Male)
			Stats::SetPackedBool(28458, TRUE); // Black Principe Aged Tee (Male)
			Stats::SetPackedBool(28459, TRUE); // Albany Vintage Aged Tee (Male)
			Stats::SetPackedBool(28460, TRUE); // Benefactor Aged Tee (Male)
			Stats::SetPackedBool(28461, TRUE); // Bravado Aged Tee (Male)
			Stats::SetPackedBool(28462, TRUE); // Declasse Aged Tee (Male)
			Stats::SetPackedBool(28463, TRUE); // Dinka Aged Tee (Male)
			Stats::SetPackedBool(28464, TRUE); // Grotti Aged Tee (Male)
			Stats::SetPackedBool(28465, TRUE); // Lampadati Aged Tee (Male)
			Stats::SetPackedBool(28466, TRUE); // Ocelot Aged Tee (Male)
			Stats::SetPackedBool(28467, TRUE); // Overflod Aged Tee (Male)
			Stats::SetPackedBool(28468, TRUE); // Pegassi Aged Tee (Male)
			Stats::SetPackedBool(28469, TRUE); // Pfister Aged Tee (Male)
			Stats::SetPackedBool(28470, TRUE); // Vapid Aged Tee (Male)
			Stats::SetPackedBool(28471, TRUE); // Weeny Aged Tee (Male)
			Stats::SetPackedBool(28472, TRUE); // Toe Shoes Aged T-Shirt (Male)
			Stats::SetPackedBool(28473, TRUE); // Vanilla Unicorn Aged T-Shirt (Male)
			Stats::SetPackedBool(28474, TRUE); // Fake Vapid Aged T-Shirt (Male)
			Stats::SetPackedBool(28475, TRUE); // I Married My Dad Aged T-Shirt (Male)
			Stats::SetPackedBool(28476, TRUE); // White Rockstar Camo Aged Tee (Male)
			Stats::SetPackedBool(28477, TRUE); // Razor Aged T-Shirt (Male)
			Stats::SetPackedBool(28478, TRUE); // Noise Rockstar Logo Aged Tee (Male)
			Stats::SetPackedBool(30355, TRUE); // Noise Aged Tee (Male)
			Stats::SetPackedBool(30356, TRUE); // Emotion 98.3 Aged T-Shirt (Male)
			Stats::SetPackedBool(30357, TRUE); // KDST Aged T-Shirt (Male)
			Stats::SetPackedBool(30358, TRUE); // KJAH Radio Aged T-Shirt (Male)
			Stats::SetPackedBool(30359, TRUE); // Bounce FM Aged T-Shirt (Male)
			Stats::SetPackedBool(30360, TRUE); // K-Rose Aged T-Shirt (Male)
			Stats::SetPackedBool(30361, TRUE); // Blue The Diamond Resort LS Aged Tee (Male)
			Stats::SetPackedBool(28463, TRUE); // Channel X Aged Tee (Female)
			Stats::SetPackedBool(28464, TRUE); // Rebel Radio Aged Tee (Female)
			Stats::SetPackedBool(28465, TRUE); // LSUR Aged Tee (Female)
			Stats::SetPackedBool(28466, TRUE); // Steel Horse Solid Logo Aged Tee (Female)
			Stats::SetPackedBool(28467, TRUE); // Black Western Logo Aged Tee (Female)
			Stats::SetPackedBool(28468, TRUE); // White Nagasaki Aged Tee (Female)
			Stats::SetPackedBool(28469, TRUE); // Black Principe Aged Tee (Female)
			Stats::SetPackedBool(28470, TRUE); // Albany Vintage Aged Tee (Female)
			Stats::SetPackedBool(28471, TRUE); // Benefactor Aged Tee (Female)
			Stats::SetPackedBool(28472, TRUE); // Bravado Aged Tee (Female)
			Stats::SetPackedBool(28473, TRUE); // Declasse Aged Tee (Female)
			Stats::SetPackedBool(28474, TRUE); // Dinka Aged Tee (Female)
			Stats::SetPackedBool(28475, TRUE); // Grotti Aged Tee (Female)
			Stats::SetPackedBool(28476, TRUE); // Lampadati Aged Tee (Female)
			Stats::SetPackedBool(28477, TRUE); // Ocelot Aged Tee (Female)
			Stats::SetPackedBool(28478, TRUE); // Overflod Aged Tee (Female)
			Stats::SetPackedBool(30355, TRUE); // Pegassi Aged Tee (Female)
			Stats::SetPackedBool(30356, TRUE); // Pfister Aged Tee (Female)
			Stats::SetPackedBool(30357, TRUE); // Vapid Aged Tee (Female)
			Stats::SetPackedBool(30358, TRUE); // Weeny Aged Tee (Female)
			Stats::SetPackedBool(30359, TRUE); // Toe Shoes Aged T-Shirt (Female)
			Stats::SetPackedBool(30360, TRUE); // Vanilla Unicorn Aged T-Shirt (Female)
			Stats::SetPackedBool(30361, TRUE); // Fake Vapid Aged T-Shirt (Female)
			Stats::SetPackedBool(30362, TRUE); // I Married My Dad Aged T-Shirt (Female)
			Stats::SetPackedBool(30363, TRUE); // White Rockstar Camo Aged Tee (Female)
			Stats::SetPackedBool(30364, TRUE); // Razor Aged T-Shirt (Female)
			Stats::SetPackedBool(30365, TRUE); // Noise Rockstar Logo Aged Tee (Female)
			Stats::SetPackedBool(30366, TRUE); // Noise Aged Tee (Female)
			Stats::SetPackedBool(30367, TRUE); // Emotion 98.3 Aged T-Shirt (Female)
			Stats::SetPackedBool(30368, TRUE); // KDST Aged T-Shirt (Female)
			Stats::SetPackedBool(30369, TRUE); // KJAH Radio Aged T-Shirt (Female)
			Stats::SetPackedBool(30370, TRUE); // Bounce FM Aged T-Shirt (Female)
			Stats::SetPackedBool(30371, TRUE); // K-Rose Aged T-Shirt (Female)
			Stats::SetPackedBool(30372, TRUE); // Blue The Diamond Resort LS Aged Tee (Female)
			Stats::SetPackedBool(31857, TRUE); // Green Crowex Pro Racing Suit
			Stats::SetPackedBool(31874, TRUE); // Gray Benefactor Racing Suit
			Stats::SetPackedBool(31879, TRUE); // Black Crowex Pro Racing Suit
			Stats::SetPackedBool(31884, TRUE); // Blue Xero Gas Racing Suit
			Stats::SetPackedBool(31889, TRUE); // Dark Benefactor Racing Suit
			Stats::SetPackedBool(31894, TRUE); // Red Xero Gas Racing Suit
			Stats::SetPackedBool(31899, TRUE); // Wildstyle Racing Suit
			Stats::SetPackedBool(32224, TRUE); // Tuned For Speed Racing Suit
			Stats::SetPackedBool(31827, TRUE); // Beige Knit Sneakers
			Stats::SetPackedBool(31843, TRUE); // Cream Knit Sneakers
			Stats::SetPackedBool(31862, TRUE); // Black Knit Sneakers
			Stats::SetPackedBool(31878, TRUE); // Gray & Purple Knit Sneakers
			Stats::SetPackedBool(31895, TRUE); // Gray & Magenta Knit Sneakers
			Stats::SetPackedBool(31912, TRUE); // Gray & Aqua Knit Sneakers
			Stats::SetPackedBool(31928, TRUE); // White & Pink Knit Sneakers
			Stats::SetPackedBool(31952, TRUE); // Gray & Yellow Knit Sneakers
			Stats::SetPackedBool(31977, TRUE); // Grayscale Knit Sneakers
			Stats::SetPackedBool(32000, TRUE); // Gray & Cyan Knit Sneakers
			Stats::SetPackedBool(32018, TRUE); // Lilac Knit Sneakers
			Stats::SetPackedBool(32027, TRUE); // White Knit Sneakers
			Stats::SetPackedBool(32035, TRUE); // Ice Knit Sneakers
			Stats::SetPackedBool(32042, TRUE); // Aqua Sole Knit Sneakers
			Stats::SetPackedBool(32050, TRUE); // Smoky Knit Sneakers
			Stats::SetPackedBool(32056, TRUE); // White & Gold Knit Sneakers
			Stats::SetPackedBool(32060, TRUE); // Orange Knit Sneakers
			Stats::SetPackedBool(32063, TRUE); // Pink Vibrant Knit Sneakers
			Stats::SetPackedBool(32067, TRUE); // Lime Highlight Knit Sneakers
			Stats::SetPackedBool(32070, TRUE); // Purple Fade Knit Sneakers
			Stats::SetPackedBool(32072, TRUE); // Teal Knit Sneakers
			Stats::SetPackedBool(32073, TRUE); // Black & Lime Knit Sneakers
			Stats::SetPackedBool(32074, TRUE); // Cyan Fade Knit Sneakers
			Stats::SetPackedBool(32084, TRUE); // Red Highlight Knit Sneakers
			Stats::SetPackedBool(31833, TRUE); // White Emperor Motors Tee
			Stats::SetPackedBool(31850, TRUE); // Navy Emperor Motors Tee
			Stats::SetPackedBool(31868, TRUE); // Yellow Annis Rally Tee
			Stats::SetPackedBool(31885, TRUE); // Blue Annis Noise Tee
			Stats::SetPackedBool(31902, TRUE); // Light Dinka Tee
			Stats::SetPackedBool(31918, TRUE); // Black Annis Noise Tee
			Stats::SetPackedBool(31937, TRUE); // Dark Dinka Tee
			Stats::SetPackedBool(31962, TRUE); // Light Vapid Ellie Tee
			Stats::SetPackedBool(31987, TRUE); // Dark Vapid Ellie Tee
			Stats::SetPackedBool(32007, TRUE); // White Logo Ruiner Tee
			Stats::SetPackedBool(32022, TRUE); // Gray Vapid Truck Tee
			Stats::SetPackedBool(32031, TRUE); // White Obey Omnis Tee
			Stats::SetPackedBool(32038, TRUE); // Light Blue Vapid Truck Tee
			Stats::SetPackedBool(32046, TRUE); // Black Vapid USA Tee
			Stats::SetPackedBool(32053, TRUE); // Red Obey Omnis Tee
			Stats::SetPackedBool(32058, TRUE); // Red Logo Ruiner Tee
			Stats::SetPackedBool(32062, TRUE); // Blue Bravado Gauntlet Tee
			Stats::SetPackedBool(32066, TRUE); // Black Bravado Gauntlet Tee
			Stats::SetPackedBool(32069, TRUE); // Pfister Pocket Tee
			Stats::SetPackedBool(32071, TRUE); // Karin 90s Tee
			Stats::SetPackedBool(32104, TRUE); // Annis Hellion 4x4 Tee
			Stats::SetPackedBool(31828, TRUE); // Gray Emperor Classic Hoodie
			Stats::SetPackedBool(31845, TRUE); // Yellow Pfister Hoodie
			Stats::SetPackedBool(31863, TRUE); // Green Emperor Classic Hoodie
			Stats::SetPackedBool(31880, TRUE); // Gray Pfister Hoodie
			Stats::SetPackedBool(31897, TRUE); // Black Vapid Ellie Hoodie
			Stats::SetPackedBool(31913, TRUE); // Gray Karin Hoodie
			Stats::SetPackedBool(31930, TRUE); // Navy Vapid Ellie Hoodie
			Stats::SetPackedBool(31955, TRUE); // Navy Karin Hoodie
			Stats::SetPackedBool(31980, TRUE); // Light Obey Hoodie
			Stats::SetPackedBool(32002, TRUE); // Black Ubermacht Hoodie
			Stats::SetPackedBool(32020, TRUE); // Dark Obey Hoodie
			Stats::SetPackedBool(32028, TRUE); // Red Ubermacht Hoodie
			Stats::SetPackedBool(32036, TRUE); // Blue Annis Noise Hoodie
			Stats::SetPackedBool(32043, TRUE); // Green Emperor Modern Hoodie
			Stats::SetPackedBool(32051, TRUE); // Gray Annis Noise Hoodie
			Stats::SetPackedBool(32057, TRUE); // Dark Emperor Modern Hoodie
			Stats::SetPackedBool(32061, TRUE); // Light Dinka Hoodie
			Stats::SetPackedBool(32065, TRUE); // Gold Lampadati Hoodie
			Stats::SetPackedBool(32068, TRUE); // Dark Dinka Hoodie
			Stats::SetPackedBool(32134, TRUE); // Tricolor Lampadati Hoodie
			Stats::SetPackedBool(31837, TRUE); // Never Barcode Print Hoodie
			Stats::SetPackedBool(31853, TRUE); // Never Triangle Print Hoodie
			Stats::SetPackedBool(31872, TRUE); // Life ZigZag Print Hoodie
			Stats::SetPackedBool(31888, TRUE); // Life Static Print Hoodie
			Stats::SetPackedBool(31905, TRUE); // Never Crosshair Print Hoodie
			Stats::SetPackedBool(31922, TRUE); // Hiding Print Hoodie
			Stats::SetPackedBool(31942, TRUE); // Life Binary Print Hoodie
			Stats::SetPackedBool(31967, TRUE); // Lucky Penny Print Hoodie
			Stats::SetPackedBool(32174, TRUE); // Crash Out Print Hoodie
			Stats::SetPackedBool(31840, TRUE); // Gray Leather Bomber
			Stats::SetPackedBool(31858, TRUE); // Mustard Tan Leather Bomber
			Stats::SetPackedBool(31875, TRUE); // Orange Tan Leather Bomber
			Stats::SetPackedBool(31892, TRUE); // Chestnut Tan Leather Bomber
			Stats::SetPackedBool(31908, TRUE); // Dark Tan Leather Bomber
			Stats::SetPackedBool(31925, TRUE); // Ox Blood Leather Bomber
			Stats::SetPackedBool(31947, TRUE); // Dark Nut Leather Bomber
			Stats::SetPackedBool(31972, TRUE); // Navy Blue Leather Bomber
			Stats::SetPackedBool(31995, TRUE); // Dark Green Leather Bomber
			Stats::SetPackedBool(32015, TRUE); // White Leather Bomber
			Stats::SetPackedBool(32026, TRUE); // Red Leather Bomber
			Stats::SetPackedBool(32144, TRUE); // Mono Leather Bomber
			Stats::SetPackedBool(31830, TRUE); // Cyan Check Sleeveless Puffer
			Stats::SetPackedBool(31835, TRUE); // Cyan Check Puffer
			Stats::SetPackedBool(31847, TRUE); // Red Check Sleeveless Puffer
			Stats::SetPackedBool(31852, TRUE); // Red Check Puffer
			Stats::SetPackedBool(31865, TRUE); // Green Geo Sleeveless Puffer
			Stats::SetPackedBool(31870, TRUE); // Green Geo Puffer
			Stats::SetPackedBool(31882, TRUE); // Black Geo Sleeveless Puffer
			Stats::SetPackedBool(31887, TRUE); // Black Geo Puffer
			Stats::SetPackedBool(31898, TRUE); // Cream Bigness Sleeveless Puffer
			Stats::SetPackedBool(31903, TRUE); // Cream Bigness Puffer
			Stats::SetPackedBool(31915, TRUE); // Purple Bigness Sleeveless Puffer
			Stats::SetPackedBool(31920, TRUE); // Purple Bigness Puffer
			Stats::SetPackedBool(31932, TRUE); // Green Aztec Sleeveless Puffer
			Stats::SetPackedBool(31940, TRUE); // Green Aztec Puffer
			Stats::SetPackedBool(31957, TRUE); // Black Aztec Sleeveless Puffer
			Stats::SetPackedBool(31965, TRUE); // Black Aztec Puffer
			Stats::SetPackedBool(31982, TRUE); // Cream Splinter Sleeveless Puffer
			Stats::SetPackedBool(31990, TRUE); // Cream Splinter Puffer
			Stats::SetPackedBool(32005, TRUE); // Dark Splinter Sleeveless Puffer
			Stats::SetPackedBool(32010, TRUE); // Dark Splinter Puffer
			Stats::SetPackedBool(32021, TRUE); // Green Latin Sleeveless Puffer
			Stats::SetPackedBool(32023, TRUE); // Green Latin Puffer
			Stats::SetPackedBool(32030, TRUE); // Black Latin Sleeveless Puffer
			Stats::SetPackedBool(32032, TRUE); // Black Latin Puffer
			Stats::SetPackedBool(32037, TRUE); // Orange Camo Sleeveless Puffer
			Stats::SetPackedBool(32040, TRUE); // Orange Camo Puffer
			Stats::SetPackedBool(32045, TRUE); // Aqua Camo Sleeveless Puffer
			Stats::SetPackedBool(32047, TRUE); // Aqua Camo Puffer
			Stats::SetPackedBool(32052, TRUE); // Gradient Sleeveless Puffer
			Stats::SetPackedBool(32055, TRUE); // Gradient Puffer
			Stats::SetPackedBool(32114, TRUE); // Pink Gradient Sleeveless Puffer
			Stats::SetPackedBool(32154, TRUE); // Pink Gradient Puffer
			Stats::SetPackedBool(31832, TRUE); // Blue Hayes Retro Racing
			Stats::SetPackedBool(31838, TRUE); // Hayes Modern Racing
			Stats::SetPackedBool(31848, TRUE); // White Hayes Retro Racing
			Stats::SetPackedBool(31855, TRUE); // LTD Modern Racing
			Stats::SetPackedBool(31867, TRUE); // White Globe Oil Retro Racing
			Stats::SetPackedBool(31873, TRUE); // Blue Dinka Modern Racing
			Stats::SetPackedBool(31883, TRUE); // Green Crowex Retro Racing
			Stats::SetPackedBool(31890, TRUE); // Red Dinka Modern Racing
			Stats::SetPackedBool(31900, TRUE); // Red Globe Oil Retro Racing
			Stats::SetPackedBool(31907, TRUE); // Yellow Vapid Modern Racing
			Stats::SetPackedBool(31917, TRUE); // Black Crowex Retro Racing
			Stats::SetPackedBool(31923, TRUE); // Ubermacht Modern Racing
			Stats::SetPackedBool(31935, TRUE); // Blue Atomic Retro Racing
			Stats::SetPackedBool(31945, TRUE); // White Güffy Modern Racing
			Stats::SetPackedBool(31960, TRUE); // Yellow Atomic Retro Racing
			Stats::SetPackedBool(31970, TRUE); // Black Güffy Modern Racing
			Stats::SetPackedBool(31985, TRUE); // Blue Redwood Retro Racing
			Stats::SetPackedBool(31992, TRUE); // Light Dinka Modern Racing
			Stats::SetPackedBool(32012, TRUE); // Dark Dinka Modern Racing
			Stats::SetPackedBool(32025, TRUE); // Blue Bravado Modern Racing
			Stats::SetPackedBool(32033, TRUE); // Black Bravado Modern Racing
			Stats::SetPackedBool(32041, TRUE); // Imponte Modern Racing
			Stats::SetPackedBool(32048, TRUE); // Xero Modern Racing
			Stats::SetPackedBool(32124, TRUE); // Fade Broker Modern Racing
			Stats::SetPackedBool(32164, TRUE); // Red Redwood Retro Racing  
		}
	};
	class CareerProgress_Rewards : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			// Set ranged bools
			auto setRange = [](int start, int end) {
				for (int i = start; i <= end; ++i)
				{
					Stats::SetPackedBool(i, TRUE);
				}
			};
			// OSCAR GUZMAN FLIES AGAIN
			Stats::SetPackedBool(51280, TRUE); // Complete Up and Running for Oscar Guzman Flies Again
			Stats::SetPackedBool(51285, TRUE); // Complete Oscar Guzman Flies Again
			Stats::SetPackedBool(51278, TRUE); // Complete an Oscar Guzman Flies Again mission without dying
			Stats::SetPackedBool(51279, TRUE); // Complete Oscar Guzman Flies Again in under 60 minutes
			Stats::SetInt("MP0_PROG_HUB_MFH_EARNINGS", 5000000); // Earn $5,000,000 from Oscar Guzman Flies Again
			setRange(51286, 51291); // Complete an Oscar Guzman Flies Again mission on Hard
			setRange(51292, 51297); // Complete all Oscar Guzman Flies Again missions on Hard without using snacks or armor

			// THE CLUCKIN" BELL FARM RAID
			Stats::SetPackedBool(28272, TRUE); // Steal the setup funds for The Cluckin" Bell Farm Raid
			Stats::SetPackedBool(28287, TRUE); // Complete The Cluckin" Bell Farm Raid
			Stats::SetPackedBool(28286, TRUE); // Complete a Cluckin" Bell Farm Raid mission without dying
			Stats::SetPackedBool(28285, TRUE); // Complete Scene of the Crime without being spotted
			Stats::SetPackedBool(28282, TRUE); // Complete The Cluckin" Bell Farm Raid in less than 45 minutes as a leader
			Stats::SetInt("MP0_PROG_HUB_CBR_EARNINGS", 5000000); // Earn $5,000,000 from The Cluckin" Bell Farm Raid
			setRange(28283, 28284); // Complete Scene of the Crime using both approaches
			setRange(28273, 28281); // Complete Scene of the Crime using all available setup equipment

			// SAN ANDREAS MERCENARIES
			Stats::SetPackedBool(41566, TRUE); // Complete a Project Overthrow mission without dying
			Stats::SetPackedBool(41706, TRUE); // Complete a Project Overthrow mission on Hard difficulty
			Stats::SetInt("MP0_SUM23_AVOP_PROGRESS", 4095);   // Complete a Project Overthrow mission for Charlie Reed
			setRange(41567, 41572); // Complete all Project Overthrow missions on Hard difficulty
			setRange(41573, 41578); // Complete all Project Overthrow missions on Hard difficulty without using snacks or armor
			setRange(41579, 41584); // Complete all Project Overthrow missions taking less than 50% damage
			setRange(41585, 41590); // Complete all Project Overthrow missions with over 80% accuracy

			// OPERATION PAPER TRAIL
			Stats::SetPackedBool(41707, TRUE); // Complete an Operation Paper Trail mission on Hard difficulty
			Stats::SetInt("MP0_ULP_MISSION_PROGRESS", 16383); // Complete an Operation Paper Trail mission for Agent ULP
			setRange(41333, 41338); // Complete an Operation Paper Trail mission without dying
			setRange(41339, 41344); // Complete all Operation Paper Trail missions on Hard difficulty
			setRange(41345, 41350); // Complete all Operation Paper Trail missions on Hard difficulty without using snacks or armor
			setRange(41351, 41356); // Complete all Operation Paper Trail missions taking less than 50% damage
			setRange(41357, 41362); // Complete all Operation Paper Trail missions with over 80% accuracy

			// A SUPERYACHT LIFE
			Stats::SetPackedBool(41379, TRUE); // Complete a Superyacht Life mission without dying
			Stats::SetPackedBool(41708, TRUE); // Complete a Superyacht Life mission on Hard difficulty
			Stats::SetInt("MP0_YACHT_MISSION_FLOW", 65520);   // Complete a Superyacht Life mission for Brendan Darcy
			setRange(41380, 41385); // Complete all Superyacht Life missions on Hard difficulty
			setRange(41386, 41391); // Complete all Superyacht Life missions on Hard difficulty without using snacks or armor
			setRange(41392, 41397); // Complete all Superyacht Life missions taking less than 50% damage
			setRange(41398, 41403); // Complete all Superyacht Life missions with over 80% accuracy

			// GERALD'S LAST PLAY
			Stats::SetPackedBool(41410, TRUE); // Complete a Last Play mission without dying
			Stats::SetPackedBool(41709, TRUE); // Complete a Last Play mission on Hard difficulty
			setRange(41404, 41409); // Complete a Last Play mission for Gerald
			setRange(41411, 41416); // Complete all Last Play missions on Hard difficulty
			setRange(41417, 41422); // Complete all Last Play missions on Hard difficulty without using snacks or armor
			setRange(41423, 41428); // Complete all Last Play missions taking less than 50% damage
			setRange(41429, 41434); // Complete all Last Play missions with over 80% accuracy

			// PREMIUM DELUXE REPO WORK
			Stats::SetPackedBool(41435, TRUE); // Complete a Repo Work mission without dying
			Stats::SetPackedBool(41705, TRUE); // Complete a Repo Work mission on Hard difficulty
			setRange(41436, 41443); // Complete a Repo Work mission for Simeon Yetarian
			setRange(41444, 41451); // Complete all Repo Work missions on Hard difficulty
			setRange(41452, 41459); // Complete all Repo Work missions on Hard difficulty without using snacks or armor
			setRange(41460, 41467); // Complete all Repo Work missions taking less than 50% damage
			setRange(41468, 41475); // Complete all Repo Work missions with over 80% accuracy

			// MADRAZO DISPATCH SERVICES
			Stats::SetPackedBool(41506, TRUE); // Complete a Dispatch Mission without dying
			Stats::SetPackedBool(41710, TRUE); // Complete a Dispatch Mission on Hard difficulty
			setRange(41476, 41481); // Complete a Dispatch Mission for Martin Madrazo
			setRange(41482, 41487); // Complete all Dispatch Missions on Hard difficulty
			setRange(41488, 41493); // Complete all Dispatch Missions on Hard difficulty without using snacks or armor
			setRange(41494, 41499); // Complete all Dispatch Missions taking less than 50% damage
			setRange(41500, 41505); // Complete all Dispatch Missions with over 80% accuracy

			// LOWRIDERS
			Stats::SetPackedBool(41539, TRUE); // Complete a Lowrider mission without dying
			Stats::SetPackedBool(41711, TRUE); // Complete a Lowrider mission on Hard difficulty
			setRange(42015, 42022); // Complete a Lowrider mission for Lamar
			setRange(41507, 41514); // Complete all Lowrider missions on Hard difficulty
			setRange(41515, 41522); // Complete all Lowrider missions on Hard difficulty without using snacks or armor
			setRange(41523, 41530); // Complete all Lowrider missions taking less than 50% damage
			setRange(41531, 41538); // Complete all Lowrider missions with over 80% accuracy

			// AGENTS OF SABOTAGE
			Stats::SetPackedBool(9539, TRUE);  // Meet with Pavel
			Stats::SetPackedBool(9549, TRUE);  // Complete the Priority File 2 weeks in a row
			Stats::SetPackedBool(9542, TRUE);  // Complete all mission challenges for a File
			Stats::SetPackedInt(24903, 25); // Complete 25 Files
			Stats::SetPackedInt(24904, 2);  // Complete 2 Files without losing a life
			Stats::SetInt("MP0_HACKER_DEN_OWNED", 1);         // Acquire the Garment Factory
			Stats::SetInt("MP0_HACKER24_GEN_BS", 8160);  // Complete all the Files
			Stats::SetInt("MP0_PROG_HUB_DEN24_SAFEEARNINGS", 100000); // Earn $100,000 in additional Garment Factory earnings
			setRange(9543, 9546); // Complete all mission challenges for all Files
			Stats::SetPackedInt(24905, 9); //  Unlock 9 platinum awards for Agents of Sabotage

			// BOTTOM DOLLAR BOUNTIES
			Stats::SetPackedBool(9537, TRUE);  // Meet with Maude Eccles
			Stats::SetPackedBool(7639, TRUE);  // Secure or eliminate a bounty target
			Stats::SetPackedInt(7669, 5); // Secure or eliminate 5 Standard bounty targets
			Stats::SetPackedInt(7672, 2); // Secure or eliminate 2 Most Wanted bounty targets
			Stats::SetPackedInt(7670, 10); //  Secure or eliminate 10 bounty targets without losing a life
			Stats::SetPackedInt(7674, 3); //  Secure or eliminate a Most Wanted bounty target 3 days in a row
			Stats::SetPackedInt(7671, 25); //  Secure or eliminate 25 bounty targets
			Stats::SetInt("MP0_BAIL_OFFICE_OWNED", 1);   // Set up a Bail Office
			Stats::SetInt("MP0_PROG_HUB_BOUNTY_EARNINGS", 5000000); // Earn $5,000,000 from securing or eliminating bounty targets
			Stats::SetInt("MP0_PROG_HUB_BOUNTIES_ALIVE_BS", 31); // Secure all bounty targets alive
			Stats::SetInt("MP0_BAIL_PROPERTY_EARNINGS", 1000000); // Earn $1,000,000 in additional income from your Bail Office Agents
			Stats::SetPackedInt(26809, 10); //  Unlock 10 platinum awards for Bottom Dollar Bounties

			// THE CHOP SHOP
			Stats::SetPackedBool(42038, TRUE); // Meet with Yusuf Amir
			Stats::SetPackedBool(42041, TRUE); // Complete a Salvage Yard Robbery
			Stats::SetPackedBool(42044, TRUE); // Sell a vehicle
			Stats::SetPackedBool(42045, TRUE); // Salvage a vehicle
			Stats::SetPackedBool(42042, TRUE); // Complete all Salvage Yard Robberies
			Stats::SetPackedBool(42046, TRUE); // Complete all bonus challenges for a Salvage Yard Robbery
			Stats::SetInt("MP0_SALVAGE_YARD_OWNED", 1); // Set up a Salvage Yard
			Stats::SetInt("MP0_PROG_HUB_SALV23_EARN_SALV", 2500000); // Earn $250,000 from salvaging vehicles
			Stats::SetInt("MP0_PROG_HUB_SALV23_EARN_PERF", 5); // Sell 5 vehicles in perfect condition from Salvage Yard Robberies
			Stats::SetInt("MP0_PROG_HUB_SALV23_EARN_SELL", 10000000); // Earn $10,000,000 from selling stolen vehicles
			setRange(22082, 22083); // Hire a second Resident DJ
			Stats::SetPackedInt(51052, 10); // Unlock 10 Platinum Awards for The Chop Shop


			// LOS SANTOS DRUG WARS
			Stats::SetPackedBool(42037, TRUE); // Set up an Acid Lab
			Stats::SetPackedInt(41241, 5);  // Unlock all custom acid names
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 131071);  // Complete all missions for The First Dose
			Stats::SetInt("MP0_LFETIME_BIKER_BUY_COMPLET6", 100); // Complete 10 Source Supplies missions for the Acid Lab
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 1984); // Complete all missions for The Last Dose
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 4063232);// Complete all missions for The Last Dose
			Stats::SetInt("MP0_XM22_FLOW", 32505856); // Complete all Fooligan Jobs
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS6", 10000000); // Earn $1,000,000 selling Acid
			Stats::SetInt("MP0_LFETIME_BIKER_BUY_COMPLET6", 10); // Unlock all custom acid names
			Stats::SetInt("MP0_LFETIME_BIKER_SELL_COMPLET6", 10); // Unlock all custom acid names
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 5); // Unlock all custom acid names
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 10); // Unlock all custom acid names
			Stats::SetInt("MP0_XM22_MISSIONS_SA", 26); // Unlock all custom acid names
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS6", 1000000); // Unlock all custom acid names
			Stats::SetInt("MP0_PROG_HUB_LSDW_FJ_NO_DEATHS", 25); // Complete 25 Fooligan Jobs without dying
			Stats::SetInt("MP0_PROG_HUB_DAX_CLONE_KILLS", 100); // Take out 100 hostile versions of yourself in The Last Dose - Checking In
			setRange(41660, 41670); // Complete all missions in The First Dose and The Last Dose without dying
			Stats::SetPackedInt(42084, 24); // Unlock all Platinum Awards for Los Santos Drug Wars

			// THE CONTRACT
			Stats::SetPackedBool(28257, TRUE); // Set up the Agency
			Stats::SetPackedBool(41507, TRUE); // Earn $5,000,000 from Security Contracts
			Stats::SetInt("MP0_FIXER_COUNT", 100);// Complete a Security Contract
			Stats::SetInt("MP0_FIXER_GENERAL_BS", 0);// Meet the VIP
			Stats::SetInt("MP0_AWD_COLD_CALLER", 10);// Complete 10 Payphone Hits
			Stats::SetInt("MP0_FIXER_GENERAL_BS", 2);// Complete the VIP Contract
			Stats::SetInt("MP0_PROG_HUB_FXER_PAY_HIT_BONUS", 100); // Complete 25 Payphone Hits with the Assassination Bonus
			Stats::SetInt("MP0_PROG_HUB_FIXER_SEC_CON_SPEC", 100); // Complete 100 Security Contracts on Specialist or Specialist+ difficulty
			Stats::SetInt("MP0_FIXER_EARNINGS", 5000000); // Earn $5,000,000 from Security Contracts
			Stats::SetInt("MP0_AWD_SHORTFRANK_1", TRUE); // Complete all Short Trips playing as Franklin and Lamar
			Stats::SetInt("MP0_AWD_SHORTFRANK_2", TRUE);  // Complete all Short Trips playing as Franklin and Lamar
			Stats::SetInt("MP0_AWD_SHORTFRANK_3", TRUE); // Complete all Short Trips playing as Franklin and Lamar
			Stats::SetPackedInt(42085, 10); // Unlock 10 Platinum Awards for The Contract

			// AFTER HOURS
			Stats::SetPackedBool(22067, TRUE); // Set up a Nightclub
			Stats::SetPackedBool(15533, TRUE); // Hire a second Resident DJ
			Stats::SetPackedBool(36868, TRUE); // Source Goods for your Nightclub Basement
			Stats::SetPackedBool(36944, TRUE); // Eject a troublemaker from your Nightclub
			Stats::SetPackedBool(41989, TRUE); // Fill up your Nightclub safe
			Stats::SetInt("MP0_NIGHTCLUB_JOBS_DONE", 25); // Complete a Club Management mission
			Stats::SetInt("MP0_PROG_HUB_DANCE_DUR", 5); // Dance for 5 minutes inside a Nightclub
			Stats::SetInt("MP0_NIGHTCLUB_VIP_APPEAR", 25); // Have 25 celebrity appearances at your Nightclub
			Stats::SetInt("MP0_PROG_HUB_NCLUB_POP_MAX_TME", 600); // Keep your Nightclub popularity at 100% for 10 hours
			Stats::SetInt("MP0_HUB_EARNINGS", 50000000); // Earn a total of $50,000,000 or more
			setRange(22067, 22067); // Complete 25 Club Management missions
			setRange(36868, 36944); // Source Goods and eject a troublemaker from your Nightclub
			setRange(41989, 41989); // Fill up your Nightclub safe
			setRange(42089, 42089); // Unlock 8 Platinum Awards for After Hours
			setRange(50000000, 50000000); // Earn $50,000,000 or more
			Stats::SetPackedInt(42089, 8); // Unlock 8 Platinum Awards for After Hours

			// SMUGGLER'S RUN
			Stats::SetPackedBool(15966, TRUE);  // Set up a Hangar
			Stats::SetPackedBool(41676, TRUE); // Send a staff member to source Air-Freight Cargo
			Stats::SetPackedBool(32398, TRUE); // Turn a Pegasus vehicle into a Personal Aircraft
			Stats::SetPackedBool(41987, TRUE); // Fill your Hangar with Air-Freight Cargo
			Stats::SetPackedBool(36924, TRUE); // Sell 50 crates of the same type of Air-Freight Cargo in one sale
			Stats::SetInt("MP0_LFETIME_HANGAR_BUY_COMPLET", 100); // Complete a Source Cargo mission
			Stats::SetInt("MP0_LFETIME_HANGAR_SEL_COMPLET", 1); // Complete an Air-Freight Cargo Sell mission
			Stats::SetInt("MP0_PROG_HUB_SMUGGLER_CRATES", 1000); // Sell 1,000 crates of Air-Freight Cargo
			Stats::SetInt("MP0_LFETIME_HANGAR_EARNINGS", 50000000); // Earn $50,000,000 selling Air-Freight Cargo
			setRange(36925, 36932); // Sell all types of Air-Freight Cargo

			// GUNRUNNING
			Stats::SetPackedBool(36870, TRUE); // Deliver excess weapon parts to Ammu-Nation
			Stats::SetPackedInt(9359, 25);  // Complete 25 research project
			Stats::SetInt("MP0_WVM_FLOW_BITSET_MISSIONS0", 1);   // Complete a Mobile Operation
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC5", 1); // Complete a Sell mission
			Stats::SetInt("MP0_LFETIME_BIKER_SELL_COMPLET5", 1); // Complete a Sell mission
			Stats::SetInt("MP0_SR_WEAPON_BIT_SET", 262142); // Complete all Challenges for 1 weapon at the Bunker Shooting Range
			Stats::SetInt("MP0_LFETIME_BIKER_BUY_COMPLET5", 25); // Complete 25 Resupply missions
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS5", 25000000); // Earn $25,000,000 selling Weapons
			setRange(42002, 42013); // Upgrade 5 weapons to Mk II
			setRange(36831, 36838); // Complete all Mobile Operations on Hard difficulty in under 10 minutes

			// IMPORT / EXPORT
			Stats::SetPackedBool(41988, TRUE); // Fill a Vehicle Warehouse with 40 stolen vehicles
			Stats::SetInt("MP0_OWNED_IE_WAREHOUSE", 1); // Own a Vehicle Warehouse
			Stats::SetInt("MP0_LFETIME_IE_EXPORT_COMPLETED", 25); // Complete a Vehicle Cargo mission
			Stats::SetInt("MP0_PROG_HUB_VEH_CARGO_SELL_PER", 50); // Sell 1 vehicle in perfect condition
			Stats::SetInt("MP0_PROG_HUB_VEH_CARGO_SPECIAL", 5);   // Sell 5 vehicles to Specialist Dealers
			Stats::SetInt("MP0_LFETIME_IE_MISSION_EARNINGS", 25000000); // Earn $25,000,000 selling Vehicle Cargo
			setRange(42029, 42036); // Complete a Special Vehicle Work
			setRange(41874, 41883); // Source all vehicles for one Collector
			setRange(41540, 41547); // Complete all Special Vehicle Works on Hard difficulty

			// BIKERS
			Stats::SetPackedBool(36871, TRUE); // Become President of a Motorcycle Club
			Stats::SetPackedBool(36872, TRUE); // Hire a player to join your Motorcycle Club
			Stats::SetPackedBool(36873, TRUE); // Deliver a customer bike
			Stats::SetPackedBool(42001, TRUE); // Set up any Biker business
			Stats::SetPackedBool(36874, TRUE); // Complete a Resupply mission for any Biker business
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_COMPLETBC", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC1", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC2", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC3", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_LIFETIME_BKR_SEL_COMPLETBC4", 1); // Sell Product from all Biker businesses
			Stats::SetInt("MP0_BAR_RESUPPLY_CR", 10); // Resupply the Clubhouse bar 10 times
			Stats::SetInt("MP0_LIFETIME_BKR_SELL_EARNINGS0", 25000000); // Earn $25,000,000 selling Product
			Stats::SetInt("MP0_PROG_HUB_BIK_CUST_DEL_CASH", 2500000); // Earn $2,500,000 delivering customer bikes
			Stats::SetInt("MP0_PROG_HUB_CLBH_BAR_EARNINGS", 500000); // Earn $500,000 from your Clubhouse bar
			Stats::SetInt("MP0_PROG_HUB_BIK_CONTRACT_COUNT", 50); // Complete 50 Clubhouse Contracts
			setRange(36875, 36887); // Complete a Clubhouse Contract
			
			// FURTHER ADVENTURES IN FINANCE AND FELONY
			Stats::SetPackedBool(36888, TRUE); // Become CEO of an Organization
			Stats::SetPackedBool(36889, TRUE); // Hire a player to join your Organization
			Stats::SetPackedBool(36890, TRUE); // Export Mixed Goods to the Docks
			Stats::SetPackedBool(36891, TRUE); // Sell 111 crates of Cargo in one Sell mission
			Stats::SetInt("MP0_WARHOUSESLOT0", 1); // Own a Special Cargo Warehouse
			Stats::SetInt("MP0_LIFETIME_BUY_COMPLETE", 1); // Source Cargo for your Warehouse
			Stats::SetInt("MP0_PROG_HUB_FAIFAF_CRATES_COL", 250); // Source 250 crates of Cargo
			Stats::SetInt("MP0_LIFETIME_CONTRA_EARNINGS", 50000000); // Earn $50,000,000 selling Cargo
			setRange(36892, 36915); // Complete a VIP Work
			setRange(7559, 7553);   // Source all types of Cargo
			setRange(36860, 36865); // Source all types of Special Items

			// LOS SANTOS TUNERS
			Stats::SetPackedBool(31737, TRUE); // Visit and become a member of the LS Car Meet
			Stats::SetPackedBool(41870, TRUE); // Take a vehicle into the LS Car Meet Test Track
			Stats::SetPackedBool(31753, TRUE); // Set up an Auto Shop
			Stats::SetPackedBool(32397, TRUE); // Complete a Prize Ride Challenge
			Stats::SetInt("MP0_CAR_CLUB_MEMBERSHIP", 1); // Visit and become a member of the LS Car Meet
			Stats::SetInt("MP0_TUNER_COMP_BS", 255);    // Complete any Robbery Contract
			Stats::SetInt("MP0_AWD_AUTO_SHOP", 10);     // Service and deliver 10 customer vehicles
			Stats::SetInt("MP0_AWD_CAR_CLUB_MEM", 100); // Reach LS Car Meet reputation level 10
			Stats::SetInt("MP0_AWD_GROUNDWORK", 1); // Deliver all 10 Exotic Exports vehicles in a day
			Stats::SetInt("MP0_TUNER_COUNT", 25);       // Complete 25 Robbery Contracts
			Stats::SetInt("MP0_PROG_HUB_TUNER_CUS_DEL_CASH", 5000000); // Earn $5,000,000 delivering customer vehicles
			Stats::SetPackedInt(30226, 10); // Unlock 10 Platinum Awards for Los Santos Tuners

			// THE DIAMOND CASINO & RESORT
			Stats::SetPackedBool(27089, TRUE); // Visit The Diamond Casino & Resort
			Stats::SetPackedBool(27090, TRUE); // Purchase a Penthouse and visit Agatha Baker
			Stats::SetPackedBool(36916, TRUE); // Recover the bonus item after completing Cashing Out
			Stats::SetPackedBool(41868, TRUE); // Take out Avery's bodyguards without being spotted in Cashing Out
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 6);  // Complete Loose Cheng
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 12); // Complete Loose Cheng
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 12); // Complete Loose Cheng
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 11); // Complete Cashing Out
			Stats::SetInt("MP0_VCM_FLOW_PROGRESS", 17); // Complete Cashing Out
			Stats::SetInt("MP0_AWD_ODD_JOBS", 100);     // Complete Casino Work for Agatha Baker
			Stats::SetPackedInt(42093, 11); // Unlock 11 Platinum Awards for The Diamond Casino & Resort

			// THE CAYO PERICO HEIST
			Stats::SetPackedBool(30309, TRUE); // Meet Miguel Madrazo inside The Music Locker
			Stats::SetPackedBool(30522, TRUE); // Set up a Kosatka
			Stats::SetPackedBool(41677, TRUE); // Complete The Cayo Perico Heist on Hard difficulty
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
			Stats::SetPackedInt(42094, 15); // Unlock 15 Platinum Awards for The Cayo Perico Heist

			// THE DIAMOND CASINO HEIST
			Stats::SetPackedBool(28270, TRUE); // Set up an Arcade
			Stats::SetPackedBool(36842, TRUE); // Scope the contents of the Casino Vault
			Stats::SetPackedBool(32399, TRUE); // Play an arcade game
			Stats::SetPackedBool(42025, TRUE); // Complete The Diamond Casino Heist in under 10 minutes on Hard difficulty
			Stats::SetInt("MP0_CAS_HEIST_FLOW", 1); // Meet Lester Crest at Mirror Park
			Stats::SetInt("MP0_CAS_HEIST_FLOW", 10);  // Complete The Diamond Casino Heist as a leader
			Stats::SetInt("MP0_AWD_PREPARATION", 25); // Complete 25 prep missions
			Stats::SetInt("MP0_CAS_HEIST_FLOW", 14336); // Complete The Diamond Casino Heist using all approaches
			Stats::SetInt("MP0_PROG_HUB_CASINO_H_EARNINGS", 50000000); // Steal $50,000,000 from the vault
			Stats::SetInt("MP0_AWD_DAICASHCRAB", 100000); // Steal $100,000 from the Daily Vault
			setRange(36844, 36859); // Complete 13 different Casino Work missions
			setRange(41548, 41553); // Complete all Casino Story Missions on Hard difficulty
			setRange(41560, 41565); // Complete all Casino Story Missions on Hard difficulty while taking less than 50% damage
			setRange(41554, 41559); // Complete all Casino Story Missions on Hard difficulty using only pistols
			setRange(41678, 41681); // Steal all variations of loot from the vault on Hard difficulty, without being spotted
			Stats::SetPackedBool(42086, TRUE); // Unlock 15 Platinum Awards for The Diamond Casino Heist

			// THE DOOMSDAY HEIST
			Stats::SetPackedBool(18139, TRUE); // Set up a Facility and meet Lester Crest
			Stats::SetPackedBool(36861, TRUE); // Set up The Data Breaches
			Stats::SetPackedBool(41712, TRUE); // Complete The Data Breaches as a leader
			Stats::SetPackedBool(36862, TRUE); // Set up The Bogdan Problem
			Stats::SetPackedBool(41713, TRUE); // Complete The Bogdan Problem as a leader
			Stats::SetPackedBool(36863, TRUE); // Set up The Doomsday Scenario
			Stats::SetPackedBool(41714, TRUE); // Complete The Doomsday Scenario as a leader
			Stats::SetPackedBool(41685, TRUE); // Complete all 3 Acts using only pistols and vehicles
			Stats::SetPackedBool(41690, TRUE); // Complete all 3 Acts using only pistols and vehicles
			Stats::SetPackedBool(41696, TRUE); // Complete all 3 Acts using only pistols and vehicles
			Stats::SetPackedInt(42087, 10); // Unlock 10 Platinum Awards for The Doomsday Heist
			Stats::SetInt("MP0_GANGOPS_FLOW_BITSET_MISS0", 7); // Complete any Setup for The Data Breaches
			Stats::SetInt("MP0_PROG_HUB_DOOM_PRP_NO_DEATHS", 14); // Complete 14 prep missions without dying
			Stats::SetInt("MP0_PROG_HUB_DOOMSDAY_ACTS", 15);      // Complete 15 Acts as a leader
			setRange(41697, 41699); // Complete the Elite Challenges for all 3 Acts
			setRange(41701, 41704); // Complete the Elite Challenge for each heist

			// ORIGINAL HEISTS
			Stats::SetPackedBool(36867, TRUE); // Own a high-end or custom Apartment
			Stats::SetPackedBool(36933, TRUE); // Set up The Fleeca Job
			Stats::SetPackedBool(41700, TRUE); // Complete a Setup for The Fleeca Job as a leader
			Stats::SetPackedBool(41715, TRUE); // Complete The Fleeca Job as a leader
			Stats::SetPackedBool(41716, TRUE); // Complete Prison Break as a leader
			Stats::SetPackedBool(41717, TRUE); // Complete The Humane Labs Raid as a leader
			Stats::SetPackedBool(41718, TRUE); // Complete Series A Funding as a leader
			Stats::SetPackedBool(41719, TRUE); // Complete The Pacific Standard Job as a leader
			Stats::SetPackedBool(36917, TRUE); // Complete the Elite Challenge for each heist
			Stats::SetPackedBool(42000, TRUE); // Complete the Criminal Mastermind challenge
			Stats::SetInt("MP0_PROG_HUB_HEIST_EARNINGS", 50000000); // Earn $50,000,000 across all heists
			Stats::SetPackedInt(42100, 5);  // Complete all heists with the same crew
			Stats::SetPackedInt(42090, 15); // Unlock 15 Platinum Awards for heists

			// ARENA WAR
			Stats::SetPackedBool(25009, TRUE); // Set up an Arena Workshop
			Stats::SetInt("MP0_ARENAWARS_AP_TIER", 50); // Reach Sponsorship Tier 25
			Stats::SetPackedInt(22063, 20); // Reach skill level 5
			Stats::SetPackedInt(42000, 20); // Earn skill level 20 in Arena Wars
			setRange(41647, 41655); // Win an Arena Mode
			Stats::SetPackedInt(42088, 15); // Unlock 15 Platinum Awards for Arena Wars

			// ADVERSARY MODE
			Stats::SetPackedBool(36840, TRUE); // Participate in the Featured Series
			Stats::SetPackedBool(36921, TRUE); // Win 5 Adversary Modes in a row
			Stats::SetInt("MP0_PROG_HUB_ADV_WINS", 50); // Win 5 Adversary Modes
			setRange(41594, 41646); // Participate in any Adversary Mode
			setRange(41656, 41646); // Participate in 25 different Adversary Modes
			setRange(51339, 41646); // Participate in 25 different Adversary Modes
			
			// SURVIVALS
			Stats::SetPackedBool(41672, TRUE); // Survive 5 waves in Survival without dying
			Stats::SetPackedBool(41673, TRUE); // Get 100 headshots in a game of Survival
			Stats::SetPackedBool(41332, TRUE); // Complete 10 waves in Survival mode playing solo
			Stats::SetPackedBool(41331, TRUE); // Reach wave 16 playing Endless Waves
			Stats::SetInt("MP0_PROG_HUB_SURVIVALS_PLAYED", 1); // Play a Survival mode
			Stats::SetInt("MP0_PROG_HUB_SURV_WAVES", 50);    // Clear 50 waves in Survival
			Stats::SetInt("MP0_AWD_FMHORDWAVESSURVIVE", 10); // Survive 10 waves in Survival without dying
			Stats::SetInt("MP0_PROG_HUB_SURV_WAVES", 250); // Clear 250 waves in Survival

			// RACING
			Stats::SetPackedBool(42023, TRUE); // Participate in any Race
			Stats::SetPackedInt(41246, 20); // Win 20 Races in the Community Series
			Stats::SetInt("MP0_RACES_WON", 50); // Win 5 Races against another player
			Stats::SetInt("MP0_PROG_HUB_T_TRIAL_PAR_TIME", 67108863); // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_T_TRL_PAR_TIME_RC", 67108863);  // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_T_TRL_PAR_TIME_HSW", 67108863); // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_T_TRL_PAR_TIME_BKE", 67108863); // Beat the par time in 25 Time Trials
			Stats::SetInt("MP0_PROG_HUB_FST_LPS_RSTAR_RAC", 50); // Achieve the fastest lap 50 times on any Rockstar-created Race
			setRange(41363, 42151); // Win a Race in 5 different race types

			// DEATHMATCHES
			Stats::SetPackedBool(36922, TRUE); // Win 5 Deathmatches in a row
			Stats::SetInt("MP0_DM_END", 1); // Participate in any Deathmatch
			Stats::SetInt("MP0_PROG_HUB_DM_TDM_PLAYS", 1); // Participate in a Team Deathmatch
			Stats::SetInt("MP0_AWD_FM_DM_WINS", 50); // Win 5 Deathmatches
			Stats::SetInt("MP0_PROG_HUB_DM_COMMUNITY_PLAYS", 10); // Play 10 Deathmatches in the Community Series
			Stats::SetInt("MP0_PROG_HUB_DTHM_KILL_5_WO_DIE", 25); // Kill 5 players without dying 25 times during Deathmatches

			// VEHICLE ENTHUSIAST
			Stats::SetPackedBool(41864, TRUE); // Own a Garage with at least 10 spaces
			Stats::SetPackedBool(42014, TRUE); // Customize a vehicle in Los Santos Customs
			Stats::SetPackedBool(41865, TRUE); // Own a Pegasus vehicle
			Stats::SetPackedBool(41863, TRUE); // Test drive or purchase a vehicle from Premium Deluxe Motorsport or Luxury Autos
			Stats::SetPackedBool(41840, TRUE); // Upgrade a vehicle to its custom variant at Benny's Original Motor Works
			Stats::SetPackedBool(41839, TRUE); // Upgrade a vehicle with HSW Performance Upgrades at Hao's Special Works inside the LS Car Meet
			Stats::SetPackedBool(41841, TRUE); // Upgrade a vehicle into an Arena Contender at an Arena Workshop
			Stats::SetPackedBool(41838, TRUE); // Customize a vehicle with Imani tech at an Agency
			Stats::SetPackedBool(41866, TRUE); // Own 100 vehicles including 1 Special Vehicle
			Stats::SetInt("MP0_HUB_VEH_ENTH_OWNED_VEHS", 99); // Own 100 vehicles including 1 Special Vehicle
			Stats::SetInt("MP0_VEHICLES_CUSTOMISED", 50);     // Customize 50 vehicles
			setRange(41842, 41862); // Own a vehicle in each of the 15 different vehicle classes
			Stats::SetPackedInt(42092, 5);  // Earn 5 gold medals in the Flight School challenges
			Stats::SetPackedInt(42091, 10); // Unlock 10 Platinum Awards for Vehicles

			// WEAPONS EXPERT
			Stats::SetPackedBool(36934, TRUE); // Own 5 different weapons
			Stats::SetPackedBool(36935, TRUE); // Equip Body Armor
			Stats::SetPackedBool(36936, TRUE); // Add an attachment to a weapon
			Stats::SetPackedBool(36937, TRUE); // Customize your weapon loadout at a Gun Locker
			Stats::SetPackedBool(36938, TRUE); // Customize a weapon at a Weapon Workshop
			Stats::SetPackedBool(36920, TRUE); // Request and collect a Merryweather Ammo Drop
			Stats::SetPackedBool(36941, TRUE); // Own 50 weapons
			Stats::SetPackedBool(36942, TRUE); // Visit the Gun Van every day for 10 days
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
		}
	};

    class unlock_all_awards : public Command
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
			Stats::SetBool("MP0_AWD_TRUELOVE", true);
			Stats::SetBool("MP0_AWD_NEMESIS", true);
			Stats::SetBool("MP0_AWD_FRIENDZONED", true);
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
			for (int i = 0; i < 10; i++){
			Stats::SetInt(("MP0_IAP_INITIALS_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MP0_DG_DEFENDER_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MP0_DG_DEFENDER_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MP0_DG_MONKEY_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MP0_DG_MONKEY_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MP0_DG_PENETRATOR_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MP0_DG_PENETRATOR_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MP0_GGSM_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MP0_GGSM_SCORE_" + std::to_string(i)).c_str(), 50);
			Stats::SetInt(("MP0_TWR_INITIALS_" + std::to_string(i)).c_str(), 69644);
			Stats::SetInt(("MP0_TWR_SCORE_" + std::to_string(i)).c_str(), 50);}
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
			Stats::SetInt("MP0_SCGW_SCORE_1", 50);
			Stats::SetInt("MP0_SCGW_SCORE_2", 50);
			Stats::SetInt("MP0_SCGW_SCORE_3", 50);
			Stats::SetInt("MP0_SCGW_SCORE_4", 50);
			Stats::SetInt("MP0_SCGW_SCORE_5", 50);
			Stats::SetInt("MP0_SCGW_SCORE_6", 50);
			Stats::SetInt("MP0_SCGW_SCORE_7", 50);
			Stats::SetInt("MP0_SCGW_SCORE_8", 50);
			Stats::SetInt("MP0_SCGW_SCORE_9", 50);
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
			Stats::SetInt("MP0_CAS_HEIST_NOTS", -1);
			Stats::SetInt("MP0_CH_ARC_CAB_CLAW_TROPHY", -1);
			Stats::SetInt("MP0_CH_ARC_CAB_LOVE_TROPHY", -1);
			Stats::SetInt("MP0_SIGNAL_JAMMERS_COLLECTED", 50);
			Stats::SetInt("MP0_AWD_ODD_JOBS", 52);
			Stats::SetInt("MP0_H3_BOARD_DIALOGUE0", -1);
			Stats::SetInt("MP0_H3_BOARD_DIALOGUE1", -1);
			Stats::SetInt("MP0_H3_BOARD_DIALOGUE2", -1);
			Stats::SetInt("MP0_H3_VEHICLESUSED", -1);
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

			// Nightclub Awards
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

			// Arena War Awards
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

			// Doomsday Awards
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

			// Apartment Awards
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

            //Character Stats
			Stats::SetInt("MP0_AWD_MENTALSTATE_TO_NORMAL", 25);
			Stats::SetInt("MP0_AWD_TRADE_IN_YOUR_PROPERTY", 25);
			Stats::SetInt("MP0_AWD_100_KILLS_PISTOL", 100);
			Stats::SetInt("MP0_AWD_100_KILLS_SNIPER", 100);
			Stats::SetInt("MP0_AWD_50_KILLS_GRENADES", 50);
			Stats::SetInt("MP0_AWD_100_KILLS_SHOTGUN", 100);
			Stats::SetInt("MP0_AWD_100_KILLS_SMG", 100);
			Stats::SetInt("MP0_AWD_50_KILLS_ROCKETLAUNCH", 50);
			Stats::SetInt("MP0_AWD_25_KILLS_STICKYBOMBS", 50);
			Stats::SetInt("MP0_AWD_20_KILLS_MELEE", 20);
			Stats::SetInt("MP0_AWD_50_VEHICLES_BLOWNUP", 50);
			Stats::SetInt("MP0_AWD_ENEMYDRIVEBYKILLS", 10);
			Stats::SetInt("MP0_AWD_VEHICLES_JACKEDR", 100);
			Stats::SetInt("MP0_AWD_HOLD_UP_SHOPS", 19);
			Stats::SetInt("MP0_AWD_COPS_KILLED", 200);
		    Stats::SetInt("MP0_PISTOL_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_CMBTPISTOL_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_APPISTOL_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_MICROSMG_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_SMG_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_ASLTRIFLE_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_CRBNRIFLE_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_ADVRIFLE_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_MG_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_CMBTMG_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_ASLTSMG_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_PUMP_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_ASLTSHTGN_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_SNIPERRFL_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_HVYSNIPER_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_GRNLAUNCH_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_RPG_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_MINIGUNS_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_SAWNOFF_ENEMY_KILLS", 600);
		    Stats::SetInt("MP0_CHAR_FM_CARMOD_1_UNLCK", -1);
		    Stats::SetInt("MP0_CHAR_FM_CARMOD_2_UNLCK", -1);
		    Stats::SetInt("MP0_CHAR_FM_CARMOD_3_UNLCK", -1);
		    Stats::SetInt("MP0_CHAR_FM_CARMOD_4_UNLCK", -1);
		    Stats::SetInt("MP0_CHAR_FM_CARMOD_5_UNLCK", -1);
		    Stats::SetInt("MP0_CHAR_FM_CARMOD_6_UNLCK", -1);
		    Stats::SetInt("MP0_CHAR_FM_CARMOD_7_UNLCK", -1);
		    Stats::SetInt("MP0_AWD_FMRALLYWONDRIVE", 1);
		    Stats::SetInt("MP0_AWD_FMRALLYWONNAV", 1);
		    Stats::SetInt("MP0_AWD_FMWINSEARACE", 1);
		    Stats::SetInt("MP0_AWD_FMWINAIRRACE", 1);
		    Stats::SetInt("MP0_NUMBER_TURBO_STARTS_IN_RACE", 50);
		    Stats::SetInt("MP0_USJS_COMPLETED", 50);
		    Stats::SetInt("MP0_RACES_WON", 50);
		    Stats::SetInt("MPPLY_TOTAL_RACES_WON", 50); // Global stat, no MPx prefix
		    Stats::SetInt("MP0_AWD_FM_RACES_FASTEST_LAP", 50);
		    Stats::SetInt("MP0_NUMBER_SLIPSTREAMS_IN_RACE", 100);
			Stats::SetInt("MP0_PLAYER_HEADSHOTS", 500);


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
	    class unlock_all_tattoos : public Command
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
	    class unlock_some_trade_price : public Command    //(Not Working!!)
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
	    class unlock_vehicle_gun_mods : public Command //bodyarmor&livery
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
			    Stats::SetInt("AWD_TAXIDRIVER", 100);
			    STATS::STAT_SET_MASKED_INT("MP0_DLC22022PSTAT_INT536"_J, 10, 16, 8, true);
				// Chrome Rims
			    Stats::SetInt("MP0_AWD_WIN_CAPTURES", 50);
			    Stats::SetInt("MP0_AWD_DROPOFF_CAP_PACKAGES", 100);
			    Stats::SetInt("MP0_AWD_KILL_CARRIER_CAPTURE", 100);
			    Stats::SetInt("MP0_AWD_NIGHTVISION_KILLS", 100);
			    Stats::SetInt("MP0_AWD_WIN_LAST_TEAM_STANDINGS", 50);
			    Stats::SetInt("MP0_AWD_ONLY_PLAYER_ALIVE_LTS", 50);
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
				Stats::SetPackedBool(25155, TRUE); // Apocalypse ZR380 - Livery set
			    Stats::SetPackedBool(25156, TRUE); // Future Shock ZR380 - Livery set
			    Stats::SetPackedBool(25157, TRUE); // Nightmare ZR380 - Livery set
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
		class unlock_vehicles : public Command         //(Not Working!!)
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
					34447, 34449, 25384, 17354, 25381, 34599 , 12025, 35633, 35596, 35640, 35601, 35636, 35600, 35631, 35592, 35643,
					35602, 35637, 35588, 35635, 35594, 35634, 35607  
				};
				for (int i = 0; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
					*base.At(offsets[i]).As<int*>() = 1;
				}
				*ScriptGlobal(2707347).As<int*>() = 1; // BEDVg5 - Bypass
				Stats::SetInt("CRDEADLINE", -1); //Shotaro
				Stats::SetPackedBool(25474, TRUE); // Apocalypse & Nightmare Imperator - Whole Lotta Pole
			    Stats::SetPackedBool(25475, TRUE); // Apocalypse & Nightmare Imperator - Getting Medieval
			    Stats::SetPackedBool(25476, TRUE); // Apocalypse & Nightmare Imperator - It's A Stick Up
			    Stats::SetPackedBool(25477, TRUE); // Apocalypse & Nightmare Imperator - Boom On A Spear
			    Stats::SetPackedBool(25478, TRUE); // Apocalypse & Nightmare Imperator - Village Justice
			    Stats::SetPackedBool(25479, TRUE); // Apocalypse & Nightmare Imperator - Wasteland Peacock
			    Stats::SetPackedBool(25480, TRUE); // Apocalypse & Nightmare Imperator - Shish-Kebbabed
			    Stats::SetPackedBool(25481, TRUE); // Apocalypse & Nightmare Imperator - Junk Pipes
			    Stats::SetPackedBool(25482, TRUE); // Apocalypse & Nightmare Imperator - Mega Zorst
			    Stats::SetPackedBool(25483, TRUE); // Apocalypse & Nightmare Imperator - Ride 'Em Cowboy
			    Stats::SetPackedBool(25484, TRUE); // Apocalypse & Nightmare Imperator - Cannibal Totem
				Stats::SetPackedBool(25420, TRUE); // Apocalypse & Nightmare Brutus - Gassed Up Bar
			    Stats::SetPackedBool(25421, TRUE); // Apocalypse & Nightmare Brutus - Roadblock
			    Stats::SetPackedBool(25422, TRUE); // Apocalypse & Nightmare Brutus - Junk Trunk
			    Stats::SetPackedBool(25423, TRUE); // Apocalypse & Nightmare Brutus - Fire Spitters
			    Stats::SetPackedBool(25424, TRUE); // Apocalypse & Nightmare Brutus - Hell Chambers
			    Stats::SetPackedBool(25425, TRUE); // Apocalypse & Nightmare Brutus - Heavy Armored Arches
			    Stats::SetPackedBool(25426, TRUE); // Apocalypse & Nightmare Brutus - Toothy
			    Stats::SetPackedBool(25427, TRUE); // Apocalypse & Nightmare Brutus - Armored Spares
			    Stats::SetPackedBool(25428, TRUE); // Apocalypse & Nightmare Brutus - Armored Supplies
			    Stats::SetPackedBool(25429, TRUE); // Apocalypse & Nightmare Brutus - Eternally Chained
			    Stats::SetPackedBool(25430, TRUE); // Apocalypse & Nightmare Brutus - Speared
				Stats::SetPackedBool(25465, TRUE); // Apocalypse & Nightmare Impaler - Got Pole?
			    Stats::SetPackedBool(25466, TRUE); // Apocalypse & Nightmare Impaler - Getting Medieval
			    Stats::SetPackedBool(25467, TRUE); // Apocalypse & Nightmare Impaler - Wasteland Peacock
			    Stats::SetPackedBool(25468, TRUE); // Apocalypse & Nightmare Impaler - Shish-Kebbabed
			    Stats::SetPackedBool(25469, TRUE); // Apocalypse & Nightmare Impaler - It's A Stick Up
			    Stats::SetPackedBool(25470, TRUE); // Apocalypse & Nightmare Impaler - The Dark Ages
			    Stats::SetPackedBool(25471, TRUE); // Apocalypse & Nightmare Impaler - Dolly Spearton
			    Stats::SetPackedBool(25472, TRUE); // Apocalypse & Nightmare Impaler - War Poles
				Stats::SetPackedBool(24963, TRUE); // Apocalypse Cerberus
			    Stats::SetPackedBool(24964, TRUE); // Future Shock Cerberus
			    Stats::SetPackedBool(24965, TRUE); // Apocalypse Brutus
			    Stats::SetPackedBool(24966, TRUE); // Nightmare Cerberus
			    Stats::SetPackedBool(24967, TRUE); // Apocalypse ZR380
			    Stats::SetPackedBool(24968, TRUE); // Future Shock Brutus
			    Stats::SetPackedBool(24969, TRUE); // Impaler
			    Stats::SetPackedBool(24972, TRUE); // Rat-Truck
			    Stats::SetPackedBool(24973, TRUE); // Glendale
			    Stats::SetPackedBool(24974, TRUE); // Slamvan
			    Stats::SetPackedBool(24975, TRUE); // Dominator
			    Stats::SetPackedBool(24976, TRUE); // Issi Classic
			    Stats::SetPackedBool(24978, TRUE); // Gargoyle
			    Stats::SetPackedBool(25101, TRUE); // Nightmare Brutus
			    Stats::SetPackedBool(25102, TRUE); // Apocalypse Scarab
			    Stats::SetPackedBool(25103, TRUE); // Future Shock Scarab
			    Stats::SetPackedBool(25104, TRUE); // Nightmare Scarab
			    Stats::SetPackedBool(25105, TRUE); // Future Shock ZR380
			    Stats::SetPackedBool(25106, TRUE); // Nightmare ZR380
			    Stats::SetPackedBool(25107, TRUE); // Apocalypse Imperator
			    Stats::SetPackedBool(25108, TRUE); // Future Shock Imperator
			    Stats::SetPackedBool(25109, TRUE); // Nightmare Imperator
			    Stats::SetPackedBool(24992, TRUE); // Taxi Custom
			    Stats::SetPackedBool(24993, TRUE); // Dozer
			    Stats::SetPackedBool(24994, TRUE); // Clown Van
			    Stats::SetPackedBool(24995, TRUE); // Trashmaster
			    Stats::SetPackedBool(24996, TRUE); // Barracks Semi
			    Stats::SetPackedBool(24997, TRUE); // Mixer
			    Stats::SetPackedBool(24998, TRUE); // Space Docker
			    Stats::SetPackedBool(24999, TRUE); // Tractor
				Stats::SetPackedBool(31810, TRUE); // Annis ZR350
			    Stats::SetPackedBool(31811, TRUE); // Pfister Comet S2
			    Stats::SetPackedBool(31812, TRUE); // Dinka Jester RR
			    Stats::SetPackedBool(31813, TRUE); // Emperor Vectre
			    Stats::SetPackedBool(31814, TRUE); // Ubermacht Cypher
			    Stats::SetPackedBool(31815, TRUE); // Pfister Growler
			    Stats::SetPackedBool(31816, TRUE); // Karin Calico GTF
			    Stats::SetPackedBool(31817, TRUE); // Annis Remus
			    Stats::SetPackedBool(31818, TRUE); // Vapid Dominator ASP
			    Stats::SetPackedBool(31819, TRUE); // Karin Futo GTX
			    Stats::SetPackedBool(31820, TRUE); // Dinka RT3000
			    Stats::SetPackedBool(31821, TRUE); // Vulcar Warrener HKR
			    Stats::SetPackedBool(31822, TRUE); // Karin Sultan RS Classic
			    Stats::SetPackedBool(31823, TRUE); // Vapid Dominator GTT
			    Stats::SetPackedBool(31824, TRUE); // Karin Previon
		    }
	    };
		class unlock_all_parachutes : public Command
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
		class fastrun_reload_unlock : public Command
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
	    class unlock_achievements : public Command
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
	    class single_mc_vehicle_sell : public Command          //(Not Working)
	    {
		    using Command::Command;

		    virtual void OnCall() override
		    {
				*ScriptLocal("gb_biker_contraband_sell"_J, 704 + 17).As<int*>() = 0;
		    }
	    };
	    class unlock_masks : public Command
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

		    }
	    };
	    class unlock_flight_school : public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {
			    for (int i = 0; i < 10; ++i)
			    {
				    Stats::SetInt(("MPPLY_PILOT_SCHOOL_MEDAL_" + std::to_string(i)).c_str(), -1);
				    Stats::SetInt(("MP0_PILOT_SCHOOL_MEDAL_" + std::to_string(i)).c_str(), -1);
				    Stats::SetBool(("MP0_PILOT_ASPASSEDLESSON_" + std::to_string(i)).c_str(), true);
			    }
			    Stats::SetInt("MPPLY_NUM_CAPTURES_CREATED", 100);
		    }
	    }; 
		class unlock_tradeprice : public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {
			    Stats::SetInt("MP0_SALV23_GEN_BS", -1);
			    Stats::SetInt("MP0_SALV23_INST_PROG", -1);
			    Stats::SetInt("MP0_SALV23_SCOPE_BS", -1);
			    Stats::SetInt("MP0_MOST_TIME_ON_3_PLUS_STARS", 300000);
		    }
	    };
	    class unlock_weapons : public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {
			    Stats::SetPackedBool(51196, TRUE);
		    }
	    };
	    class unlock_collectables: public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {
			    for (int i = 28099; i <= 28148; ++i) //
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
	    class Resupply_business : public Command
	    {
		    using Command::Command;
		    virtual void OnCall() override
		    {
			    //*ScriptGlobal(1667996 + 1 + 6).As<int*>() = 1; // Acid Lab
			    //*ScriptGlobal(1668003 + 1 + 5).As<int*>() = 1; // Bunker
			    //*ScriptGlobal(1667996 + 1 + 1).As<int*>() = 1; // Document Forge
			    //*ScriptGlobal(1667996 + 1 + 2).As<int*>() = 1; // Weed Farm
			    //*ScriptGlobal(1667996 + 1 + 3).As<int*>() = 1; // Meth Lab
			    //*ScriptGlobal(1667996 + 1 + 4).As<int*>() = 1; // Cocaine Lockup

		    }
	    };
	    class SupplyCooldownBypass : public LoopedCommand
	    {
		    using LoopedCommand::LoopedCommand;

		    virtual void OnTick() override
		    {
			    // Directly set delay to 0 (instant supplies)
			    *ScriptGlobal(262145).At(18768).As<int*>() = 0; // BIKER_PURCHASE_SUPPLIES_DELAY
			    *ScriptGlobal(262145).At(21278).As<int*>() = 0; // GR_PURCHASE_SUPPLIES_DELAY
		    }

		    virtual void OnDisable() override
		    {
			    // Restore to original value (600)
			    *ScriptGlobal(262145).At(18768).As<int*>() = 600; // BIKER_PURCHASE_SUPPLIES_DELAY
			    *ScriptGlobal(262145).At(21278).As<int*>() = 600; // GR_PURCHASE_SUPPLIES_DELAY
		    }
	    };

	static BunkerResearch _BunkerResearch{"bunkerresearch", "Unlock Bunker Research", "Unlocks all Bunker Research Items"};
	static unlock_clothing _UnlockClothing{"unlockclothing", "Unlock Areana War Clothing", "Unlocks all Areana War Clothing"};
	static Genderchange _unlockgenderchange{"unlockgenderchange", "Unlock Gender Change", "Allows to Change Gender"};
	static CareerProgress_Rewards _CareerProgress_Rewards{"careerprogressreawards", "Unlock Career Progress", "Unlocks all Career Progress Stats"};
	static unlock_all_awards _unlock_all_awards{"unlockallawards", "Unlock Awards", "Unlocks all Awards"};
	static unlock_all_contacts _unlock_all_contacts{"unlockallcontacts", "Unlock All Contacts", "Unlocks all Contacts"};
	static unlock_all_tattoos _unlock_all_tattoos{"unlockalltattoos", "Unlock Tattoos", "Unlocks Some Tattoos"};
	static unlock_some_trade_price _unlock_some_trade_price{"unlocksometradeprice", "Unlock Trade Price", "Unlocks some Trade Prices"};
	static unlock_vehicle_gun_mods _unlock_vehicle_gun_mods{"unlockvehiclegunmods", "Unlock Mods", "Unlocks Mods for Vehicle and Guns"};
	/*static unlock_vanilla_unicorn_award _unlock_vanilla_unicorn_award{"unlockvanillaunicornaward", "Unlock Vanilla Unicorn Award", "Unlocks the Vanilla Unicorn Award"};*/
	static SCMembershipBypass _SCMembershipBypass{"scmembership_bypass", "GTA +", "Get GTA+ for Free"};
	static unlock_achievements _unlock_achievements{"unlockachievements", "Unlock Achievements", "Unlocks all achievements"};
	static unlock_vehicles _unlock_vehicles{"unlockvehicle", "Unlock Vehicle", "Unlocks Some Vehicles"};
	static unlock_all_parachutes _unlock_all_parachutes{"unlockallparachutes", "Unlock All Parachutes", "Unlocks all Parachutes"};
	static fastrun_reload_unlock _fastrun_reload_unlock{"fastrunreloadunlock", "Unlock Fast Run", "Unlocks Fast Run"};
	static single_mc_vehicle_sell _single_mc_vehicle_sell{"singlemcvehiclesell", "Single MC Vehicle Sell", "Allows to sell only one MC Vehicle at a time"};
	static unlock_masks _unlock_masks{"unlockmasks", "Unlock Masks", "Unlocks Some Masks"};
	static unlock_flight_school _unlock_flight_school{"unlockflightschool", "Unlock Flight School", "Unlocks Flight School"};
	static unlock_tradeprice _unlock_tradeprice{"unlocktradeprice", "Unlock Trade Price", "Unlocks Trade Price for Few Items"};
	static unlock_weapons _unlock_weapons{"unlockweapons", "Unlock Weapons", "Unlocks Some Weapons"};
	static unlock_collectables _unlock_collectables{"unlockcollectables", "Unlock Collectables", "Unlocks Some Collectables"};
	static Resupply_business _Resupply_business{"resupplybusiness", "Resupply Business", "Resupplies all Businesses"};
	static SupplyCooldownBypass _SupplyCooldownBypass{"supplycooldownbypass", "Supply Cooldown Bypass", "Bypasses Supply Cooldown"};
}
