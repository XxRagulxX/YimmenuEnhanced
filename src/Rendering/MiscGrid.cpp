#include "MiscGrid.hpp"

#include "FiberPool.hpp"
#include "GridItemButton.hpp"
#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemIntStepper.hpp"
#include "GridItemText.hpp"
#include "GridItemToggle.hpp"
#include "Joaat.hpp"
#include "Natives.hpp"
#include "PlaceholderGrid.hpp"
#include "ScriptEvent.hpp"
#include "ScriptFunction.hpp"
#include "Self.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	MiscGrid::MiscGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void MiscGrid::Populate()
	{
		// "Network Bail" isn't a registered Command in src/Misc.cpp (it's
		// an inline ImGui button + FiberPool job) - reused verbatim as a
		// GridItemButton action callback rather than wrapping it in a
		// Command just for this.
		m_Items.push_back(std::make_unique<GridItemButton>(Theme::kContentItemHeight, "Network Bail", [] {
			FiberPool::queueJob([] {
				NETWORK::NETWORK_BAIL(0, 24, 0);
			});
		}));

		m_Items.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentItemHeight, "dumpdatahash"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentItemHeight, "standrenderertest"_J));

		// DoTeleport: interiorIndex stepper + enterOwnerInterior toggle,
		// same default values (0, false) as Misc.cpp's own function-local
		// statics. The button reads both at click time and sends the
		// exact same SCRIPT_EVENT_SEND_TO_INTERIOR Misc.cpp's DoTeleport
		// button does.
		auto interiorIndexStepper = std::make_unique<GridItemIntStepper>(Theme::kContentItemHeight, "interiorIndex", 0, 0, 999);
		m_InteriorIndexStepper = interiorIndexStepper.get();
		m_Items.push_back(std::move(interiorIndexStepper));

		auto enterOwnerInteriorToggle = std::make_unique<GridItemToggle>(Theme::kContentItemHeight, "enterOwnerInterior", false);
		m_EnterOwnerInteriorToggle = enterOwnerInteriorToggle.get();
		m_Items.push_back(std::move(enterOwnerInteriorToggle));

		m_Items.push_back(std::make_unique<GridItemButton>(Theme::kContentItemHeight, "DoTeleport", [this] {
			const int interiorIndex = m_InteriorIndexStepper ? m_InteriorIndexStepper->GetValue() : 0;
			const bool enterOwnerInterior = m_EnterOwnerInteriorToggle && m_EnterOwnerInteriorToggle->GetState();

			FiberPool::queueJob([interiorIndex, enterOwnerInterior] {
				SCRIPT_EVENT_SEND_TO_INTERIOR message;
				message.Interior = interiorIndex;
				message.EnterOwnerInterior = enterOwnerInterior;
				message.GoonsOnly = false;
				message.InstanceId = 0;
				message.SubInstanceId = -1;
				message.Owner = Self::GetPlayer().GetId();
				message.Distance = 99999;
				message.Position = {0, 0, 0};

				message.SetAllPlayers();
				message.Send();
			});
		}));

		// fm_mission_controller DoTeamSwap: Team stepper, same default (0)
		// as Misc.cpp's own function-local static int team.
		auto teamStepper = std::make_unique<GridItemIntStepper>(Theme::kContentItemHeight, "Team", 0, 0, 8);
		m_TeamStepper = teamStepper.get();
		m_Items.push_back(std::move(teamStepper));

		// Display label shortened from Misc.cpp's literal button text
		// ("fm_mission_controller DoTeamSwap") - it overflows this panel's
		// width since GridItemButton has no text-wrapping yet. The action
		// underneath (the ScriptFunction call below) is unchanged.
		m_Items.push_back(std::make_unique<GridItemButton>(Theme::kContentItemHeight, "DoTeamSwap", [this] {
			const int team = m_TeamStepper ? m_TeamStepper->GetValue() : 0;

			FiberPool::queueJob([team] {
				static ScriptFunction DoTeamSwap("fm_mission_controller"_J, ScriptPointer("DoTeamSwap", "2D 02 04 00 00 38 00 50"));
				DoTeamSwap.Call<void>(team, true);
			});
		}));

		// Debug's other categories (BuildGlobalsMenu()/BuildLocalsMenu()/
		// BuildScriptsMenu()) - all three still placeholder-only.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Categories", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemFolder>(Theme::kContentItemHeight, "Globals", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(Theme::kContentItemHeight, "Locals", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(Theme::kContentItemHeight, "Scripts", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] MiscGrid populated with {} items", m_Items.size());
	}
}
