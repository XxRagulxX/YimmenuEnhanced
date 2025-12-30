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

		static std::vector<std::pair<int, const char*>> ContractNightlifeLeak = {
		    {1, "The Nightclub"},
		    {2, "The Marina"},
		    {3, "NightLife Leak"}};

		static ListCommand _ContractNightlifeLeak{"contractnightlife", "NightLife Leak", "Select NightLife Leak mission", ContractNightlifeLeak, 1};

		static std::vector<std::pair<int, const char*>> ContractHighSocietyLeak = {
		    {1, "The Country Club"},
		    {2, "Guest List"},
		    {3, "High Society"}};

		static ListCommand _ContractHighSocietyLeak{"contractsociety", "High Society Leak", "Select High Society Leak mission", ContractHighSocietyLeak, 1};

		static std::vector<std::pair<int, const char*>> ContractSouthCentralLeak = {
		    {1, "Davis"},
		    {2, "The Ballas"},
		    {3, "Agency Studio"},
		    {4, "Don't Fuck with Dre"}};

		static ListCommand _ContractSouthCentralLeak{"contractcentral", "South Central Leak", "Select South Central Leak mission", ContractSouthCentralLeak, 1};

		static std::vector<std::pair<int, const char*>> ContractRecordAStudios = {
		    {1, "Seed Capital"},
		    {2, "Fire It Up"},
		    {3, "OG Kush"}};

		static ListCommand _ContractRecordAStudios{"contractrecord", "Record A Studios", "Select Short Trip mission", ContractRecordAStudios, 1};

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

				Stats::SetInt("LOW_FLOW_CURRENT_PROG", mission);
				Stats::SetInt("LOW_FLOW_CURRENT_CALL", mission);
				Stats::SetInt("LOWRIDER_FLOW_COMPLETE", 0);


				Notifications::Show("Lowrider", "Mission Setup Completed");
			}
		};

		class CasinoStorySetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int missionIndex = _CasinoStoryMission.GetState();

				Stats::SetInt("VCM_STORY_PROGRESS", missionIndex - 1);
				Stats::SetInt("VCM_FLOW_PROGRESS", 1311695);

				Notifications::Show("Casino Story", "Mission Setup Completed ");
			}
		};

		class SuperyachtSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int missionIndex = _SuperyachtMission.GetState();

				Stats::SetInt("YACHT_MISSION_PROG", missionIndex - 1);
				Stats::SetInt("YACHT_MISSION_FLOW", 21845);

				Notifications::Show("A Superyacht Life", "Mission Setup Completed");
			}
		};

		class OperationPaperTrailSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int missionIndex = _OperationPaperTrailMission.GetState();

				Stats::SetInt("ULP_MISSION_CURRENT", missionIndex - 1);
				Stats::SetInt("ULP_MISSION_PROGRESS", 127);

				Notifications::Show("Operation Paper Trail", "Mission Setup Completed");
			}
		};

		class DrugWarsSetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int index = _DrugWarsMission.GetState();

				Stats::SetInt("XM22_CURRENT", index - 1);

				switch (index)
				{
				case 1: Stats::SetInt("XM22_MISSIONS", 0); break;
				case 2: Stats::SetInt("XM22_MISSIONS", 2); break;
				case 3: Stats::SetInt("XM22_MISSIONS", 3); break;
				case 4: Stats::SetInt("XM22_MISSIONS", 7); break;
				case 5: Stats::SetInt("XM22_MISSIONS", 15); break;
				case 6: Stats::SetInt("XM22_MISSIONS", 31); break;
				case 7: Stats::SetInt("XM22_MISSIONS", 4194367); break;
				case 8: Stats::SetInt("XM22_MISSIONS", 4194431); break;
				case 9: Stats::SetInt("XM22_MISSIONS", 4194559); break;
				case 10: Stats::SetInt("XM22_MISSIONS", 4194815); break;
				case 11: Stats::SetInt("XM22_MISSIONS", 4195327); break;
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
					Stats::SetInt("SUM23_AVOP_CURRENT", index - 1);
				else
					Stats::SetInt("SUM23_AVOP_CURRENT", 0);

				switch (index)
				{
				case 1: Stats::SetInt("SUM23_AVOP_PROGRESS", 0); break;
				case 2: Stats::SetInt("SUM23_AVOP_PROGRESS", 1); break;
				case 3: Stats::SetInt("SUM23_AVOP_PROGRESS", 3); break;
				case 4: Stats::SetInt("SUM23_AVOP_PROGRESS", 7); break;
				case 5: Stats::SetInt("SUM23_AVOP_PROGRESS", 15); break;
				case 6: Stats::SetInt("SUM23_AVOP_PROGRESS", 31); break;
				case 7: Stats::SetInt("SUM23_AVOP_PROGRESS", 20543); break;
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

				Stats::SetInt("SALV23_CFR_COOLDOWN", -1);

				switch (index)
				{
				case 1: Stats::SetInt("SALV23_INST_PROG", 0); break;
				case 2: Stats::SetInt("SALV23_INST_PROG", 1); break;
				case 3: Stats::SetInt("SALV23_INST_PROG", 3); break;
				case 4: Stats::SetInt("SALV23_INST_PROG", 7); break;
				case 5: Stats::SetInt("SALV23_INST_PROG", 15); break;
				case 6: Stats::SetInt("SALV23_INST_PROG", 31); break;
				default: break;
				}

				Notifications::Show("Cluckin' Bell Farm Raid","Mission Setup Completed");
			}
		};

		class TunersCompletePreps : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("TUNER_GEN_BS", -1);
			}
		};

		class TunersResetPreps : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("TUNER_GEN_BS", 12467);
			}
		};

		class TunersResetContracts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("TUNER_GEN_BS", 8371);
			}
		};

		class TunersRobberySetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int index = _TunersRobbery.GetState();

				if (index != 2)
					Stats::SetInt("TUNER_GEN_BS", 12543);
				else
					Stats::SetInt("TUNER_GEN_BS", 4351);

				Stats::SetInt("TUNER_CURRENT", index - 1);
				Stats::SetInt("TUNER_CURRENT", -1);

				Notifications::Show("LS Tuners Robbery", "Robbery Setup Completed");
			}
		};

		class ContractNightlifeSetup : public Command
		{
			using Command::Command;

			void OnCall() override
			{
				int index = _ContractNightlifeLeak.GetState();

				if (index != 3)
					Stats::SetInt("FIXER_STORY_BS", index + 2);
				else
					Stats::SetInt("FIXER_STORY_BS", 12);

				Stats::SetInt("FIXER_GENERAL_BS", -1);
				Stats::SetInt("FIXER_COMPLETED_BS", -1);
				Stats::SetInt("FIXER_STORY_COOLDOWN", -1);
			}
		};

		class ContractHighSocietySetup : public Command
		{
			using Command::Command;

			void OnCall() override
			{
				int index = _ContractHighSocietyLeak.GetState();

				switch (index)
				{
				case 1: Stats::SetInt("FIXER_STORY_BS", 28); break;
				case 2: Stats::SetInt("FIXER_STORY_BS", 60); break;
				case 3: Stats::SetInt("FIXER_STORY_BS", 124); break;
				}

				Stats::SetInt("FIXER_GENERAL_BS", -1);
				Stats::SetInt("FIXER_COMPLETED_BS", -1);
				Stats::SetInt("FIXER_STORY_STRAND", -1);
				Stats::SetInt("FIXER_STORY_COOLDOWN", -1);
			}
		};

		class ContractSouthCentralSetup : public Command
		{
			using Command::Command;

			void OnCall() override
			{
				int index = _ContractSouthCentralLeak.GetState();

				switch (index)
				{
				case 1: Stats::SetInt("FIXER_STORY_BS", 252); break;
				case 2: Stats::SetInt("FIXER_STORY_BS", 508); break;
				case 3: Stats::SetInt("FIXER_STORY_BS", 2044); break;
				case 4: Stats::SetInt("FIXER_STORY_BS", 4092); break;
				}

				Stats::SetInt("FIXER_GENERAL_BS", -1);
				Stats::SetInt("FIXER_COMPLETED_BS", -1);
				Stats::SetInt("FIXER_STORY_STRAND", -1);
				Stats::SetInt("FIXER_STORY_COOLDOWN", -1);
			}
		};

		class ContractRecordAStudiosSetup : public Command
		{
			using Command::Command;

			void OnCall() override
			{
				Stats::SetInt("FIXER_SHORT_TRIPS", _ContractRecordAStudios.GetState());
				Stats::SetInt("FIXER_GENERAL_BS", -259160457);
			}
		};

		class ChopShopRobberySetup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int index = _ChopShopRobbery.GetState();

				Stats::SetInt("SALV23_VEH_ROB", index - 1);
				Stats::SetInt("MOST_TIME_ON_3_PLUS_STARS", 300000);
				Stats::SetInt("SALV23_PLAN_DIALOGUE", 4131109);
				Stats::SetInt("SALV23_FM_PROG", 126);
				Stats::SetInt("SALV23_GEN_BS", -10241);
				Stats::SetInt("SALV23_DISRUPT", 3);
				Stats::SetInt("SALV23_VEH_MODS", 0);
				Stats::SetInt("SALV23_SCOPE_BS", -1);
				Stats::SetBool("SALV23_CAN_KEEP", true);

				Notifications::Show("The Chop Shop Robbery","Mission Setup Completed");
			}
		};


		static LowriderSetup _LowriderSetup{"lowridersetup", "LRSetup", "Start selected Lowrider mission"};
		static CasinoStorySetup _CasinoStorySetup{"casinostorysetup", "CSSetup", "Start selected Casino Story mission"};
		static SuperyachtSetup _SuperyachtSetup{"superyachtmissionsetup", "YSetup", "Start selected Superyacht mission"};
		static OperationPaperTrailSetup _OperationPaperTrailSetup{"operationpapertrailsetup", "PaperSetup", "Start selected Operation Paper Trail mission"};
		static DrugWarsSetup _DrugWarsSetup{"drugwarsmissionsetup", "DWSetup", "Start selected Los Santos Drug Wars mission"};
		static SAMercenariesSetup _SAMercenariesSetup{"samerccmissionsetup", "SMSetup", "Start selected San Andreas Mercenaries mission"};
		static CluckinBellFarmRaidSetup _CluckinBellFarmRaidSetup{"cluckinbellfarmraidsetup", "CBSetup", "Start selected Cluckin' Bell Farm Raid mission"};
		static TunersCompletePreps _TunersCompletePreps{"tunerscompletepreps", "TSetup Preps", "Complete all LS Tuners robbery preps"};
		static TunersResetPreps _TunersResetPreps{"tunersresetpreps", "TReset Preps", "Reset LS Tuners robbery preps"};
		static TunersResetContracts _TunersResetContracts{"tunersresetcontracts", "TReset Contracts", "Reset LS Tuners robbery contracts"};
		static TunersRobberySetup _TunersRobberySetup{"tunersrobberysetup", "TSetup", "Start selected LS Tuners robbery"};
		static ContractNightlifeSetup _ContractNightlifeSetup{"contractnightlifesetup", "CSetup Night", "Start selected NightLife Leak mission"};
		static ContractHighSocietySetup _ContractHighSocietySetup{"contracthighsocietysetup", "CSetup High", "Start selected High Society Leak mission"};
		static ContractSouthCentralSetup _ContractSouthCentralSetup{"contractsouthcentralsetup", "CSetup South", "Start selected South Central Leak mission"};
		static ContractRecordAStudiosSetup _ContractRecordAStudiosSetup{"contractrecordsetup", "CSetup Studio", "Start selected Record A Studios mission"};
        static ChopShopRobberySetup _ChopShopRobberySetup{"chopshoprobberysetup","CSRSetup","Start selected Chop Shop robbery"};

	}
}