#include "core/commands/Command.hpp"
#include <unordered_map>
#include <array>
#include <cmath>
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Tunables.hpp"
#include "game/backend/DeleteObjectsByHash.hpp"
#include "core/backend/FiberPool.hpp"

namespace YimMenu::Features
{
	namespace CayoPericoHeist
	{
		static IntCommand _CayoPericoHeistCut1{"cayopericoheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut2{"cayopericoheistcut2", "Player 2", "Player 2 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut3{"cayopericoheistcut3", "Player 3", "Player 3 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut4{"cayopericoheistcut4", "Player 4", "Player 4 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPavelCut{"cayopavelcut","Pavel Cut (%)","Pavel cut percentage",std::nullopt,std::nullopt, 2};
		static IntCommand _CayoFencingCut{"cayofencecut","Fencing Fee (%)","Fencing fee percentage",std::nullopt,std::nullopt, 10};


		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1980035).At(831).At(56);

				*base.At(0, 1).As<int*>() = _CayoPericoHeistCut1.GetState();
				*base.At(1, 1).As<int*>() = _CayoPericoHeistCut2.GetState();
				*base.At(2, 1).As<int*>() = _CayoPericoHeistCut3.GetState();
				*base.At(3, 1).As<int*>() = _CayoPericoHeistCut4.GetState();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1981146);

				for (int i = 0; i <= 3; i++)
				{
					*base.At(i, 27).At(7).At(i, 1).As<int*>() = 1;
				}
			}
		};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistDifficulty = {
		    {126823, "Normal"},
		    {131055, "Hard"}};
		static ListCommand _CayoPericoHeistDifficulty{"cayopericoheistdifficulty", "Difficulty", "Heist difficulty", cayoPericoHeistDifficulty, 126823};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistPrimaryTarget = {
		    {5, "Panther Statue"},
		    {3, "Pink Diamond"},
		    {4, "Madrazo Files"},
		    {2, "Bearer Bonds"},
		    {1, "Ruby Necklace"},
		    {0, "Sinsimito Tequila"}};
		static ListCommand _CayoPericoHeistPrimaryTarget{"cayopericoheistprimarytarget", "Primary Target", "Primary target", cayoPericoHeistPrimaryTarget, 5};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistWeapon = {
		    {1, "Aggressor"},
		    {2, "Conspirator"},
		    {3, "Crack Shot"},
		    {4, "Saboteur"},
		    {5, "Marksman"}};
		static ListCommand _CayoPericoHeistWeapon{"cayopericoheistweapon", "Weapon", "Weapon category", cayoPericoHeistWeapon, 1};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_H4CNF_TARGET", _CayoPericoHeistPrimaryTarget.GetState()); // Primary target
				Stats::SetInt("MPX_H4LOOT_CASH_I", 16711680);
				Stats::SetInt("MPX_H4LOOT_CASH_I_SCOPED", 16711680);
				Stats::SetInt("MPX_H4LOOT_CASH_C", 0);
				Stats::SetInt("MPX_H4LOOT_CASH_C_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_COKE_I", 255);
				Stats::SetInt("MPX_H4LOOT_COKE_I_SCOPED", 255);
				Stats::SetInt("MPX_H4LOOT_COKE_C", 0);
				Stats::SetInt("MPX_H4LOOT_COKE_C_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_GOLD_I", 0);
				Stats::SetInt("MPX_H4LOOT_GOLD_I_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_GOLD_C", 255);
				Stats::SetInt("MPX_H4LOOT_GOLD_C_SCOPED", 255);
				Stats::SetInt("MPX_H4LOOT_WEED_I", 65280);
				Stats::SetInt("MPX_H4LOOT_WEED_I_SCOPED", 65280);
				Stats::SetInt("MPX_H4LOOT_WEED_C", 0);
				Stats::SetInt("MPX_H4LOOT_WEED_C_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_PAINT", 127);
				Stats::SetInt("MPX_H4LOOT_PAINT_SCOPED", 127);
				Stats::SetInt("MPX_H4LOOT_CASH_V", 83250);
				Stats::SetInt("MPX_H4LOOT_COKE_V", 202500);
				Stats::SetInt("MPX_H4LOOT_GOLD_V", 333333);
				Stats::SetInt("MPX_H4LOOT_WEED_V", 135000);
				Stats::SetInt("MPX_H4LOOT_PAINT_V", 180000);
				Stats::SetInt("MPX_H4_PROGRESS", _CayoPericoHeistDifficulty.GetState()); // Difficulty
				Stats::SetInt("MPX_H4CNF_BS_GEN", 262143);
				Stats::SetInt("MPX_H4CNF_BS_ENTR", 63);
				Stats::SetInt("MPX_H4CNF_BS_ABIL", 63);
				Stats::SetInt("MPX_H4CNF_WEP_DISRP", 3);
				Stats::SetInt("MPX_H4CNF_ARM_DISRP", 3);
				Stats::SetInt("MPX_H4CNF_HEL_DISRP", 3);
				Stats::SetInt("MPX_H4CNF_APPROACH", -1);
				Stats::SetInt("MPX_H4CNF_BOLTCUT", 4424);
				Stats::SetInt("MPX_H4CNF_UNIFORM", 5256);
				Stats::SetInt("MPX_H4CNF_GRAPPEL", 5156);
				Stats::SetInt("MPX_H4_MISSIONS", -1);
				Stats::SetInt("MPX_H4CNF_WEAPONS", _CayoPericoHeistWeapon.GetState()); // Weapon
				Stats::SetInt("MPX_H4CNF_TROJAN", 5);
				Stats::SetInt("MPX_H4_PLAYTHROUGH_STATUS", 100);

				ScriptMgr::Yield(500ms);

				if (auto thread = Scripts::FindScriptThread("heist_island_planning"_J))
					*ScriptLocal(thread, 1570).As<int*>() = 2;
			}
		};

		static IntCommand _CayoPericoHeistPrimaryTargetValue{"cayopericoheistprimarytargetvalue", "Primary Target Value", "Updates primary target value", std::nullopt, std::nullopt, 0};

		class SetPrimaryTargetValue : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto primary_target = Stats::GetInt("MPX_H4CNF_TARGET");

				switch (primary_target)
				{
				case 0:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_TEQUILA"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 1:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_PEARL_NECKLACE"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 2:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_BEARER_BONDS"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 3:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_PINK_DIAMOND"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 4:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_MADRAZO_FILES"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 5:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_SAPPHIRE_PANTHER_STATUE"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				default: break;
				}
			}
		};

		static IntCommand _CayoPericoHeistSecondaryTakeValue{"cayopericoheistsecondarytakevalue", "Secondary Take Value", "Updates secondary take value", std::nullopt, std::nullopt, 0};

		class SetSecondaryTakeValue : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 59705).At(1376).At(53).As<int*>() = _CayoPericoHeistSecondaryTakeValue.GetState();
			}
		};
		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 26486).As<int*>() = 5;
			}
		};
		class CutSewer : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 31349).As<int*>() = 6;
				Hash drainagePipeHash = "prop_chem_grill_bit"_J;
				YimMenu::DeleteObjectsByHash(drainagePipeHash);
			}
		};

		class CutGlass : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 32589).At(3).As<float*>() = 100.0f;
			}
		};

		class TakePrimaryTarget : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
				{
					auto ped = Self::GetPed();

					if (!ped)
						return;

					auto pos = ped.GetPosition();
					auto heading = ped.GetHeading();
					auto primary_target = Stats::GetInt("MPX_H4CNF_TARGET");

					FiberPool::Push([&] {
						TASK::TASK_GO_STRAIGHT_TO_COORD(ped.GetHandle(), 5006.917, -5755.931, 15.484, 1.0, 3, 15, 5);

						switch (primary_target)
						{
						case 0:
						case 1:
						case 3:
						case 5:
							*ScriptLocal(thread, 32588).As<int*>() = 5;
							*ScriptLocal(thread, 32589).As<int*>() = 3;
							break;
						case 2:
						case 4:
							*ScriptLocal(thread, 32563).As<int*>() = 7;
							break;
						default: break;
						}

						ScriptMgr::Yield(4000ms);

						TASK::TASK_GO_STRAIGHT_TO_COORD(ped.GetHandle(), pos.x, pos.y, pos.z, 1.0, 3, heading, 5);
					});
				}
			}
		};
		class InfinitePlasmaCutterHeat : public LoopedCommand
		{
			using LoopedCommand::LoopedCommand;

			virtual void OnTick() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
				{
					*ScriptLocal(thread, 32589).At(4).As<float*>() = 0.0f;
				}
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
				{
					Scripts::ForceScriptHost(thread);
					ScriptMgr::Yield(500ms);

					*ScriptLocal(thread, 56223).As<int*>() = 9;
					*ScriptLocal(thread, 56223).At(1776).At(0, 1).As<int*>() = 50;
				}
			}
		};

		class Removethefencingfeeandpavelcut : public LoopedCommand
		{
			using LoopedCommand::LoopedCommand;

		private:
			Tunable m_pavel{"IH_DEDUCTION_PAVEL_CUT"_J};
			Tunable m_fee{"IH_DEDUCTION_FENCING_FEE"_J};

			void Apply()
			{
				if (m_pavel.IsReady())
					m_pavel.Set(0.0f);

				if (m_fee.IsReady())
					m_fee.Set(0.0f);
				
				_CayoPavelCut.SetState(0);
				_CayoFencingCut.SetState(0);
			}

			void Reset()
			{
				if (m_pavel.IsReady())
					m_pavel.Set(-0.02f);

				if (m_fee.IsReady())
					m_fee.Set(-0.1f);

				_CayoPavelCut.SetState(2);
				_CayoFencingCut.SetState(10);
			}

		public:
			virtual void OnEnable() override
			{
				Apply();
			}

			virtual void OnDisable() override
			{
				Reset();
			}

			virtual void OnTick() override
			{
				Apply();
			}
		};

		class AutoCollectTargets : public LoopedCommand
		{
			using LoopedCommand::LoopedCommand;

			virtual void OnTick() override
			{
				if (HUD::IS_PAUSE_MENU_ACTIVE())
					return;
				INPUT input = {0};
				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				SendInput(1, &input, sizeof(INPUT));

				ZeroMemory(&input, sizeof(INPUT));
				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(1, &input, sizeof(INPUT));

				ScriptMgr::Yield(50ms);
			}

			virtual void OnDisable() override
			{
				// No cleanup needed for mouse clicks, but you can add logic here if required
			}
		};


		class SetCayoMaxPayout : public Command
		{
			using Command::Command;

		public:
			virtual void OnCall() override
			{
				int target = _CayoPericoHeistPrimaryTarget.GetState();
				bool hardMode = (_CayoPericoHeistDifficulty.GetState() == 131055);
				float pavel = _CayoPavelCut.GetState()/ 100.0f;
				float fencing = _CayoFencingCut.GetState() / 100.0f;
				int players = GetPlayerCount();
				if (players < 1)
				   players = 1;

				int cut = CalculateCut(target, hardMode, pavel, fencing);
				if (cut <= 0)
					return;

				ApplyCuts(cut, players);
			}

		private:
			int GetPlayerCount()
			{
				return 1;
			}

			int CalculateCut(int target, bool hard, float pavel, float fencing)
			{
				static std::unordered_map<int, std::pair<int, int>> payouts = {
				    {0, {630000, 693000}},
				    {1, {700000, 770000}},
				    {2, {770000, 847000}},
				    {3, {1300000, 1430000}},
				    {4, {1100000, 1210000}},
				    {5, {1900000, 2090000}}};

				if (!payouts.contains(target))
					return 0;

				int payout = hard ? payouts[target].second : payouts[target].first;
				constexpr int maxPayout = 2'550'000;

				int cut = static_cast<int>(std::floor(maxPayout / (payout / 100.0)));
				int finalPayout = static_cast<int>(std::floor(payout * (cut / 100.0)));

				int difference = 1000;
				bool found = false;

				while (!found)
				{
					int pavelFee = static_cast<int>(std::floor(finalPayout * std::abs(pavel)));
					int fencingFee = static_cast<int>(std::floor(finalPayout * std::abs(fencing)));
					int feePayout = finalPayout - (pavelFee + fencingFee);

					if (feePayout >= maxPayout - difference && feePayout <= maxPayout)
						found = true;
					else
					{
						cut++;
						finalPayout = static_cast<int>(std::floor(payout * (cut / 100.0)));

						if (cut > 500)
						{
							cut = static_cast<int>(std::floor(maxPayout / (payout / 100.0)));
							finalPayout = static_cast<int>(std::floor(payout * (cut / 100.0)));
							difference += 1000;
						}
					}
				}

				return cut;
			}

			void ApplyCuts(int totalCut, int players)
			{
				std::array<IntCommand*, 4> cmds = {
				    &_CayoPericoHeistCut1,
				    &_CayoPericoHeistCut2,
				    &_CayoPericoHeistCut3,
				    &_CayoPericoHeistCut4};

				int perPlayer = totalCut / players;
				int remainder = totalCut % players;

				for (int i = 0; i < 4; ++i)
				{
					if (i < players)
					{
						int value = perPlayer + (i == 0 ? remainder : 0); // host gets remainder
						cmds[i]->SetState(value);
					}
					else
					{
						cmds[i]->SetState(0);
					}
				}
			}
		};


		class RemoveCayoPericoCameras : public Command
		{
			using Command::Command;

			static const inline std::vector<Hash> CayoPericoCameraHashes = {
			    ("prop_cctv_cam_01a"_J),
			    ("prop_cctv_cam_01b"_J),
			    ("prop_cctv_cam_02a"_J),
			    ("prop_cctv_cam_03a"_J),
			    ("prop_cctv_cam_04a"_J),
			    ("prop_cctv_cam_04c"_J),
			    ("prop_cctv_cam_05a"_J),
			    ("prop_cctv_cam_06a"_J),
			    ("prop_cctv_cam_07a"_J),
			    ("prop_cs_cctv"_J),
			    ("p_cctv_s"_J),
			    ("hei_prop_bank_cctv_01"_J),
			    ("hei_prop_bank_cctv_02"_J),
			    ("ch_prop_ch_cctv_cam_02a"_J),
			    ("xm_prop_x17_server_farm_cctv_01"_J),
			};

			virtual void OnCall() override
			{
				for (auto cam_hash : CayoPericoCameraHashes)
				{
					YimMenu::DeleteObjectsByHash(cam_hash);
				}
			}
		};

		static SetCuts _CayoPericoHeistSetCuts{"cayopericoheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _CayoPericoHeistForceReady{"cayopericoheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _CayoPericoHeistSetup{"cayopericoheistsetup", "Setup", "Sets up cayo perico heist"};
		static SetPrimaryTargetValue _CayoPericoHeistSetPrimaryTargetValue{"cayopericoheistsetprimarytargetvalue", "Set Primary Target Value", "Updates primary target value"};
		static SetSecondaryTakeValue _CayoPericoHeistSetSecondaryTakeValue{"cayopericoheistsetsecondarytakevalue", "Set Secondary Take Value", "Updates secondary take value"};
		static SkipHacking _CayoPericoHeistSkipHacking{"cayopericoheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static CutSewer _CayoPericoHeistCutSewer{"cayopericoheistcutsewer", "Cut Sewer", "Cuts the sewer"};
		static CutGlass _CayoPericoHeistCutGlass{"cayopericoheistcutglass", "Cut Glass", "Cuts the glass"};
		static InfinitePlasmaCutterHeat _InfinitePlasmaCutterHeat{"infiniteplasmacutterheat", "Infinite Plasma", "Infinite Plasma Cutter Heat"};
		static TakePrimaryTarget _CayoPericoHeistTakePrimaryTarget{"cayopericoheisttakeprimarytarget", "Take Primary Target", "Takes primary target"};
		static InstantFinish _CayoPericoHeistInstantFinish{"cayopericoheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
		static Removethefencingfeeandpavelcut _CayoPericoHeistRemoveFencingFeeAndPavelCut{"cayopericoheistremovefencingfeeandpavelcut", "Remove Fee&Cut", "Removes fencing fee and pavel cut"};
		static RemoveCayoPericoCameras _RemoveCayoPericoCameras{"removecayopericocameras", "Remove Cams", "Removes all cameras"};
		static AutoCollectTargets _AutoCollectTargets{"autocollecttargets", "Auto Collect", "Automatically collects targets"};
		static SetCayoMaxPayout _CayoPericoHeistSetCayoMaxPayout{"cayopericoheistsetmaxpayout","Auto Set Cuts","Automatically calculates and sets player cuts"};

	}
}