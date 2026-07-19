#include "core/commands/Command.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	namespace KortzCenterHeist
	{
		// Primary Targets
		static std::vector<std::pair<int, const char*>> kortzCenterTargets = {
			{0, "La Dernière Débauche"},
			{1, "Hare Oneself Think"},
			{2, "The Downfall of Rome"},
			{3, "Brother Brother"},
			{4, "A Cast of Characters"},
			{5, "Gone To Seed"},
			{6, "True Love"},
			{7, "Breathless"},
			{8, "Consumato"},
			{9, "I Hear Voices"},
			{10, "Winter, Nowhere in Particular"},
			{11, "The Girl With the Pearl Necklace"},
			{12, "Chat on Fruit"},
			{13, "Pumpkin"},
			{14, "Twindifference"},
			{15, "Stacks Study V"},
			{16, "I, Fruit"},
			{17, "To Beat About the Bush"},
			{18, "In Excess of Success"},
			{19, "Juiced"},
			{20, "A Winding Road Home"},
			{21, "Teckels"},
			{22, "Trust"},
			{23, "Until Death"},
			{24, "What Are Melons?"},
			{25, "The Outcome of Endeavour"},
			{26, "Mi O Melee"}
		};

		static ListCommand _KortzCenterPrimaryTarget{"kortzcenterheistprimarytarget", "Primary Target", "Select the primary target.", kortzCenterTargets, 0};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				constexpr int kAllPrepsCompleted = (1 << 16) - 1;
				constexpr int kGuardRoutes  = 1 << 5;
				constexpr int kGlassCutter  = 1 << 6;
				constexpr int kPowerDrills  = 1 << 7;
				constexpr int kEMPCharges   = 1 << 8;
				constexpr int kStreetLoadout = 1 << 9;

				int generalBits =
				    kGuardRoutes |
					kGlassCutter |
					kPowerDrills |
					kEMPCharges |
					kStreetLoadout;


				Stats::SetInt("MPX_K26_GENERAL_BS", generalBits);
				Stats::SetInt("MPX_K26_GENERAL_BS2", -1);
				Stats::SetInt("MPX_K26_ROBBERY_PROG", kAllPrepsCompleted);
				Stats::SetInt("MPX_K26_SCOPING_BS", -1);
				Stats::SetInt("MPX_K26_POI_BS", -1);
				Stats::SetInt("MPX_K26_HEIST_TARGET", _KortzCenterPrimaryTarget.GetState());
			}
		};

		static Setup _KortzCenterSetup{"kortzcenterheistsetup", "Setup","Automatically completes every prep and configures the Kortz Center Heist."};
	}
}