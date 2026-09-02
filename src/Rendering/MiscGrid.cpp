#include "Rendering/MiscGrid.hpp"

#include "Scripting/FiberPool.hpp"
#include "Rendering/GridItemButton.hpp"
#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemIntStepper.hpp"
#include "Rendering/GridItemText.hpp"
#include "Rendering/GridItemToggle.hpp"
#include "Util/Joaat.hpp"
#include "Scripting/Natives.hpp"
#include "Rendering/PlaceholderGrid.hpp"
#include "Network/ScriptEvent.hpp"
#include "Scripting/ScriptFunction.hpp"
#include "World/Self.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	MiscGrid::MiscGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void MiscGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// "Network Bail" isn't a registered Command in src/Misc.cpp (it's
		// an inline ImGui button + FiberPool job) - reused verbatim as a
		// GridItemButton action callback rather than wrapping it in a
		// Command just for this.
		items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, Theme::kContentItemHeight, "Network Bail", [] {
			FiberPool::queueJob([] {
				NETWORK::NETWORK_BAIL(0, 24, 0);
			});
		}));

		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, Theme::kContentItemHeight, "dumpdatahash"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, Theme::kContentItemHeight, "standrenderertest"_J));

		// DoTeleport: interiorIndex stepper + enterOwnerInterior toggle,
		// same default values (0, false) as Misc.cpp's own function-local
		// statics. The button reads both at click time and sends the
		// exact same SCRIPT_EVENT_SEND_TO_INTERIOR Misc.cpp's DoTeleport
		// button does.
		auto interiorIndexStepper = std::make_unique<GridItemIntStepper>(Theme::kContentWidth, Theme::kContentItemHeight, "interiorIndex", 0, 0, 999);
		m_InteriorIndexStepper = interiorIndexStepper.get();
		items_draft.push_back(std::move(interiorIndexStepper));

		auto enterOwnerInteriorToggle = std::make_unique<GridItemToggle>(Theme::kContentWidth, Theme::kContentItemHeight, "enterOwnerInterior", false);
		m_EnterOwnerInteriorToggle = enterOwnerInteriorToggle.get();
		items_draft.push_back(std::move(enterOwnerInteriorToggle));

		items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, Theme::kContentItemHeight, "DoTeleport", [this] {
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
		auto teamStepper = std::make_unique<GridItemIntStepper>(Theme::kContentWidth, Theme::kContentItemHeight, "Team", 0, 0, 8);
		m_TeamStepper = teamStepper.get();
		items_draft.push_back(std::move(teamStepper));

		// Display label shortened from Misc.cpp's literal button text
		// ("fm_mission_controller DoTeamSwap") - it overflows this panel's
		// width since GridItemButton has no text-wrapping yet. The action
		// underneath (the ScriptFunction call below) is unchanged.
		items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, Theme::kContentItemHeight, "DoTeamSwap", [this] {
			const int team = m_TeamStepper ? m_TeamStepper->GetValue() : 0;

			FiberPool::queueJob([team] {
				static ScriptFunction DoTeamSwap("fm_mission_controller"_J, ScriptPointer("DoTeamSwap", "2D 02 04 00 00 38 00 50"));
				DoTeamSwap.Call<void>(team, true);
			});
		}));

		// Debug's other categories (BuildGlobalsMenu()/BuildLocalsMenu()/
		// BuildScriptsMenu()) - all three still placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, Theme::kContentItemHeight, "Globals", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, Theme::kContentItemHeight, "Locals", &GetPlaceholderGrid()));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, Theme::kContentItemHeight, "Scripts", &GetPlaceholderGrid()));
	}
}
