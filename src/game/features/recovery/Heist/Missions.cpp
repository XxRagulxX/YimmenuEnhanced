#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Tunables.hpp"
#include "game/backend/DeleteObjectsByHash.hpp"
#include "core/backend/FiberPool.hpp"

namespace YimMenu::Features
{
	namespace Missions
	{
		static std::vector<std::pair<int, const char*>> LowriderMissionList = {
		    {1, "Community Outreach"},
		    {2, "Slow and Low"},
		    {3, "It's a G Thing"},
		    {4, "Funeral Party"},
		    {5, "Lowrider Envy"},
		    {6, "Point and Shoot"},
		    {7, "Desperate Times Call For..."},
		    {8, "Peace Offerings"}};
		static ListCommand _LowriderMission{"lowridermission", "Lowrider Mission", "Select Lowrider mission", LowriderMissionList, 1};

		static std::vector<std::pair<int, const char*>> CasinoStoryMissions = {
		    {1, "Loose Cheng"},
		    {2, "House Keeping"},
		    {3, "Strong Arm Tactics"},
		    {4, "Play to Win"},
		    {5, "Bad Beat"},
		    {6, "Cashing Out"}};
		static ListCommand _CasinoStoryMission{"casinostorymission", "Casino Story", "Select Casino Story mission", CasinoStoryMissions, 1};

		static std::vector<std::pair<int, const char*>> SuperyachtMissions = {
		    {1, "Overboard"},
		    {2, "Salvage"},
		    {3, "All Hands"},
		    {4, "Icebreaker"},
		    {5, "Bon Voyage"},
		    {6, "D-Day"}};
		static ListCommand _SuperyachtMission{"superyachtmission", "A Superyacht Life", "Select Superyacht mission", SuperyachtMissions, 1};

		static std::vector<std::pair<int, const char*>> OperationPaperTrailMissions = {
		    {1, "Intelligence"},
		    {2, "Counterintelligence"},
		    {3, "Extraction"},
		    {4, "Asset Seizure"},
		    {5, "Operation Paper Trail"},
		    {6, "Cleanup"}};

		static ListCommand _OperationPaperTrailMission{"operationpapertrailmission", "Operation Paper Trail", "Select Operation Paper Trail mission", OperationPaperTrailMissions, 1};

		static std::vector<std::pair<int, const char*>> DrugWarsMissions = {
		    {1, "Welcome to the Troupe (First Dose)"},
		    {2, "Designated Driver (First Dose)"},
		    {3, "Fatal Incursion (First Dose)"},
		    {4, "Uncontrolled Substance (First Dose)"},
		    {5, "Make War not Love (First Dose)"},
		    {6, "Off the Rails (First Dose)"},
		    {7, "This is an Intervention (Last Dose)"},
		    {8, "Unusual Suspects (Last Dose)"},
		    {9, "FriedMind (Last Dose)"},
		    {10, "Checking In (Last Dose)"},
		    {11, "BDKD (Last Dose)"}};

		static ListCommand _DrugWarsMission{"drugwarsmission", "Los Santos Drug Wars", "Select Drug Wars mission", DrugWarsMissions, 1};

		static std::vector<std::pair<int, const char*>> SAMercenariesMissions = {
		    {1, "Reporting for Duty"},
		    {2, "Falling In"},
		    {3, "On Parade"},
		    {4, "Breaking Ranks"},
		    {5, "Unconventional Warfare"},
		    {6, "Shock & Awe"},
		    {7, "Unlock All Missions"}};

		static ListCommand _SAMercenariesMission{"samerccmission", "San Andreas Mercenaries", "Select San Andreas Mercenaries mission", SAMercenariesMissions, 1};

		static std::vector<std::pair<int, const char*>> CluckinBellFarmRaidMissions = {
		    {1, "Slush Fund"},
		    {2, "Breaking and Entering"},
		    {3, "Concealed Weapons"},
		    {4, "Hit and Run"},
		    {5, "Disorganized Crime"},
		    {6, "Scene of The Crime"}};

		static ListCommand _CluckinBellFarmRaidMission{"cluckinbellfarmraidmission", "The Cluckin' Bell Farm Raid", "Select Cluckin' Bell Farm Raid mission", CluckinBellFarmRaidMissions, 1};

		static std::vector<std::pair<int, const char*>> TunersRobberies = {
		    {1, "Union Depository"},
		    {2, "The Superdollar Deal"},
		    {3, "The Bank Contract"},
		    {4, "The ECU Job"},
		    {5, "The Prison Contract"},
		    {6, "The Agency Deal"},
		    {7, "The Lost Contract"},
		    {8, "The Data Contract"}};

		static ListCommand _TunersRobbery{"tunersrobbery", "The Los Santos Tuners Robbery", "Select LS Tuners robbery", TunersRobberies, 1};

		static std::vector<std::pair<int, const char*>> ContractMissions = {
		    {0, "None"},
		    {1, "The Nightclub"},
		    {2, "The Marina"},
		    {3, "NightLife Leak"},
		    {4, "The Country Club"},
		    {5, "Guest List"},
		    {6, "High Society"},
		    {7, "Davis"},
		    {8, "The Ballas"},
		    {9, "South Central"},
		    {10, "Studio Time"},
			{11, "Don't Fuck with Dre"}};

		static ListCommand _ContractMissions{"contractmissions", "Contract Missions", "Select Contract Mission", ContractMissions, 0};

		static std::vector<std::pair<int, const char*>> ChopShopRobberies = {
		    {1, "The Cargo Ship Robbery"},
		    {2, "The Gangbanger Robbery"},
		    {3, "The Duggan Robbery"},
		    {4, "The Podium Robbery"},
		    {5, "The McTony Robbery"}};

		static ListCommand _ChopShopRobbery{"chopshoprobbery", "The Chop Shop Robbery", "Select Chop Shop robbery", ChopShopRobberies, 1};


		class LowriderSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int mission = _LowriderMission.GetState();

				Stats::SetInt("MPX_LOW_FLOW_CURRENT_PROG", mission);
				Stats::SetInt("MPX_LOW_FLOW_CURRENT_CALL", mission);
				Stats::SetInt("MPX_LOWRIDER_FLOW_COMPLETE", 0);

				Notifications::Show("Lowrider", "Mission Setup Completed");
			}
		};

		class CasinoStorySetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int missionIndex = _CasinoStoryMission.GetState();

				Stats::SetInt("MPX_VCM_FLOW_PROGRESS", 1312735);
				Stats::SetInt("MPX_VCM_STORY_PROGRESS", missionIndex - 1);

				Notifications::Show("Casino Story", "Mission Setup Completed ");
			}
		};

		class SuperyachtSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int missionIndex = _SuperyachtMission.GetState();

				Stats::SetInt("MPX_YACHT_MISSION_PROG", missionIndex - 1);
				Stats::SetInt("MPX_YACHT_MISSION_FLOW", 21845);

				Notifications::Show("A Superyacht Life", "Mission Setup Completed");
			}
		};

		class OperationPaperTrailSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int missionIndex = _OperationPaperTrailMission.GetState();

				Stats::SetInt("MPX_ULP_MISSION_CURRENT", missionIndex - 1);

				Notifications::Show("Operation Paper Trail", "Mission Setup Completed");
			}
		};

		class DrugWarsSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int index = _DrugWarsMission.GetState();

				Stats::SetInt("MPX_XM22_CURRENT", index - 1);

				switch (index)
				{
				case 1: Stats::SetInt("MPX_XM22_MISSIONS", 0); break;
				case 2: Stats::SetInt("MPX_XM22_MISSIONS", 2); break;
				case 3: Stats::SetInt("MPX_XM22_MISSIONS", 3); break;
				case 4: Stats::SetInt("MPX_XM22_MISSIONS", 7); break;
				case 5: Stats::SetInt("MPX_XM22_MISSIONS", 15); break;
				case 6: Stats::SetInt("MPX_XM22_MISSIONS", 31); break;
				case 7: Stats::SetInt("MPX_XM22_MISSIONS", 4194367); break;
				case 8: Stats::SetInt("MPX_XM22_MISSIONS", 4194431); break;
				case 9: Stats::SetInt("MPX_XM22_MISSIONS", 4194559); break;
				case 10: Stats::SetInt("MPX_XM22_MISSIONS", 4194815); break;
				case 11: Stats::SetInt("MPX_XM22_MISSIONS", 4195327); break;
				default: break;
				}

				Notifications::Show("Los Santos Drug Wars", "Mission Setup Completed");
			}
		};

		class SAMercenariesSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int index = _SAMercenariesMission.GetState();

				if (index != 7)
					Stats::SetInt("MPX_SUM23_AVOP_CURRENT", index - 1);
				else
					Stats::SetInt("MPX_SUM23_AVOP_CURRENT", 0);

				switch (index)
				{
				case 1: Stats::SetInt("MPX_SUM23_AVOP_PROGRESS", 0); break;
				case 2: Stats::SetInt("MPX_SUM23_AVOP_PROGRESS", 1); break;
				case 3: Stats::SetInt("MPX_SUM23_AVOP_PROGRESS", 3); break;
				case 4: Stats::SetInt("MPX_SUM23_AVOP_PROGRESS", 7); break;
				case 5: Stats::SetInt("MPX_SUM23_AVOP_PROGRESS", 15); break;
				case 6: Stats::SetInt("MPX_SUM23_AVOP_PROGRESS", 31); break;
				case 7: Stats::SetInt("MPX_SUM23_AVOP_PROGRESS", 20543); break;
				default: break;
				}

				Notifications::Show("San Andreas Mercenaries", "Mission Setup Completed");
			}
		};

		class CluckinBellFarmRaidSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int index = _CluckinBellFarmRaidMission.GetState();

				switch (index)
				{
				case 1: Stats::SetInt("MPX_SALV23_INST_PROG", 0); break;
				case 2: Stats::SetInt("MPX_SALV23_INST_PROG", 1); break;
				case 3: Stats::SetInt("MPX_SALV23_INST_PROG", 3); break;
				case 4: Stats::SetInt("MPX_SALV23_INST_PROG", 7); break;
				case 5: Stats::SetInt("MPX_SALV23_INST_PROG", 15); break;
				case 6: Stats::SetInt("MPX_SALV23_INST_PROG", 31); break;
				default: break;
				}

				Notifications::Show("Cluckin' Bell Farm Raid", "Mission Setup Completed");
			}
		};

		class CluckinBellFarmRaidRemoveCooldown : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_SALV23_CFR_COOLDOWN", -1);

				Notifications::Show("Cluckin' Bell Farm Raid CoolDown", "CoolDown Removed");
			}
		};


		class TunersCompletePreps : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_TUNER_GEN_BS", -1);

				if (auto thread = Scripts::FindScriptThread("tuner_planning"_J))
					*ScriptLocal(thread, 408).As<int*>() = 2;
			}
		};

		class TunersResetPreps : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_TUNER_GEN_BS", 12467);

				if (auto thread = Scripts::FindScriptThread("tuner_planning"_J))
					*ScriptLocal(thread, 408).As<int*>() = 2;
			}
		};

		class TunersResetContracts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("tuner_planning"_J))
					*ScriptLocal(thread, 408).As<int*>() = 2;
			}
		};

		class TunersRobberySetup : public Command
		{
			using Command::Command;

			void OnCall() override
			{
				int index = _TunersRobbery.GetState();
				int robbery = index - 1;

				Stats::SetInt("MPX_TUNER_CURRENT", robbery);

				if (robbery == 1)
					Stats::SetInt("MPX_TUNER_GEN_BS", 4351);
				else
					Stats::SetInt("MPX_TUNER_GEN_BS", 12543);

				if (auto thread = Scripts::FindScriptThread("tuner_planning"_J))
					*ScriptLocal(thread, 408).As<int*>() = 2;

				Notifications::Show("LS Tuners Robbery", "Preps Applied & Completed");
			}
		};

		class ContractMissionsSetup : public Command
		{
			using Command::Command;

			void OnCall() override
			{
				int index = _ContractMissions.GetState();

				int contract = -1;
				switch (index)
				{
				case 0: contract = 3; break;     // None
				case 1: contract = 4; break;     // Nightclub
				case 2: contract = 12; break;    // Marina
				case 3: contract = 28; break;    // Nightlife Leak
				case 4: contract = 60; break;    // Country Club
				case 5: contract = 123; break;   // Guest List
				case 6: contract = 254; break;   // High Society Leak
				case 7: contract = 508; break;   // Davis
				case 8: contract = 1020; break;  // Ballas
				case 9: contract = 2044; break;  // South Central Leak
				case 10: contract = 2045; break; // Studio Time
				case 11: contract = 4095; break; // Don't F*** With Dre
				default: return;
				}

				Stats::SetInt("MPX_FIXER_STORY_BS", contract);

				if (contract < 18)
					Stats::SetInt("MPX_FIXER_STORY_STRAND", 0);
				else if (contract < 128)
					Stats::SetInt("MPX_FIXER_STORY_STRAND", 1);
				else if (contract < 2044)
					Stats::SetInt("MPX_FIXER_STORY_STRAND", 2);
				else
					Stats::SetInt("MPX_FIXER_STORY_STRAND", -1);

				Stats::SetInt("MPX_FIXER_GENERAL_BS", -1);
				Stats::SetInt("MPX_FIXER_COMPLETED_BS", -1);

				Notifications::Show("Agency Contract", "Preps Applied & Completed");
			}
		};

		class ContractRemoveCooldown : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_FIXER_STORY_COOLDOWN", -1);

				Notifications::Show("Contract Cooldown", "Cooldown Removed");
			}
		}

		class ChopShopRobberySetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int index = _ChopShopRobbery.GetState();

				Stats::SetInt("MPX_SALV23_VEH_ROB", index - 1);
				Stats::SetInt("MPX_MOST_TIME_ON_3_PLUS_STARS", 300000);
				Stats::SetInt("MPX_SALV23_PLAN_DIALOGUE", 4131109);
				Stats::SetInt("MPX_SALV23_FM_PROG", -1);
				Stats::SetInt("MPX_SALV23_GEN_BS", -1);
				Stats::SetInt("MPX_SALV23_DISRUPT", 3);
				Stats::SetInt("MPX_SALV23_VEH_MODS", 0);
				Stats::SetInt("MPX_SALV23_SCOPE_BS", -1);
				Stats::SetInt("MPX_SALV23_INST_PROG", -1);
				Stats::SetBool("MPX_SALV23_CAN_KEEP", true);

				if (auto thread = Scripts::FindScriptThread("vehrob_planning"_J))
					*ScriptLocal(thread, 537).As<int*>() = 2;

				Notifications::Show("The Chop Shop Robbery", "Mission Setup Completed");
			}
		};


		static LowriderSetup _LowriderSetup{"lowridersetup", "LRSetup", "Start selected Lowrider mission"};
		static CasinoStorySetup _CasinoStorySetup{"casinostorysetup", "CSSetup", "Start selected Casino Story mission"};
		static SuperyachtSetup _SuperyachtSetup{"superyachtmissionsetup", "YSetup", "Start selected Superyacht mission"};
		static OperationPaperTrailSetup _OperationPaperTrailSetup{"operationpapertrailsetup", "PaperSetup", "Start selected Operation Paper Trail mission"};
		static DrugWarsSetup _DrugWarsSetup{"drugwarsmissionsetup", "DWSetup", "Start selected Los Santos Drug Wars mission"};
		static SAMercenariesSetup _SAMercenariesSetup{"samerccmissionsetup", "SMSetup", "Start selected San Andreas Mercenaries mission"};
		static CluckinBellFarmRaidSetup _CluckinBellFarmRaidSetup{"cluckinbellfarmraidsetup", "CBSetup", "Start selected Cluckin' Bell Farm Raid mission"};
		static CluckinBellFarmRaidRemoveCooldown _ClukinBellFarmRaidCooldown{"clukinbellfarmraidcooldown", "CB RmCooldown", "Removes cooldown for CluckinBell FarmRaid"};
		static TunersCompletePreps _TunersCompletePreps{"tunerscompletepreps", "TSetup Preps", "Complete all LS Tuners robbery preps"};
		static TunersResetPreps _TunersResetPreps{"tunersresetpreps", "TReset Preps", "Reset LS Tuners robbery preps"};
		static TunersResetContracts _TunersResetContracts{"tunersresetcontracts", "TReset Contracts", "Reset LS Tuners robbery contracts"};
		static TunersRobberySetup _TunersRobberySetup{"tunersrobberysetup", "TSetup", "Start selected LS Tuners robbery"};
		static ContractMissionsSetup _ContractmissionsSetup{"contractmissionssetup", "Contract Setup", "Start selected NightLife Leak mission"};
		static ContractRemoveCooldown _ContractRemoveCooldown{"contractremovecooldown", "Contact Rmcooldown", "Contract Remove Cooldown"};
		static ChopShopRobberySetup _ChopShopRobberySetup{"chopshoprobberysetup", "CSRSetup", "Start selected Chop Shop robbery"};

	}
}