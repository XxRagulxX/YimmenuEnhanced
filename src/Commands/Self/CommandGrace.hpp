#pragma once
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandToggle.hpp"

#include "Scripting/Natives.hpp"
#include "World/Self.hpp"

// Third real feature migrated onto the ported Stand tree (Self, after
// Commands/Self/CommandGod.hpp/CommandAutoHeal.hpp). Replaces the legacy
// Commands/Self/CommandNoRagdoll.cpp (Stand::Features::NoRagdoll, a
// LoopedCommand, previously shown via a plain GridItemCommandToggle with
// a "Gracefulness" labelOverride on its underlying "noragdoll" command) -
// SelfGrid.cpp's own row now points here instead, via GridItemStandCommand.
//
// Matches real Stand's own CommandGrace (Commands/Self/CommandGrace.hpp
// on origin/stand-reference) for command_names/class name:
//   explicit CommandGrace(CommandList* const parent)
//       : CommandToggle(parent, LOC("NRGDL"), { CMDNAME("grace"), CMDNAME("gracefulness"), CMDNAME("noragdoll") }, LOC("NRGDL_H"))
// menu_name/help_text below reuse this project's own already-confirmed
// text for this exact feature (SelfGrid.cpp's own "Gracefulness"
// labelOverride, CommandNoRagdoll.cpp's own "Prevents your ped from
// ragdolling" description) rather than guessing at LOC("NRGDL")/
// LOC("NRGDL_H")'s real English text from scratch - this repo's own
// origin/stand-reference branch carries no localisation/lang table at
// all (see Util/Label.hpp's own class comment), and no screenshot to
// confirm one exists either. Flagged, not silently guessed as fact -
// correct it if real Stand's own actual text differs.
//
// Real Stand's own onEnable()/onDisable() just increment/decrement its
// own shared g_gui.grace counter (a ref-count - CommandSuperFlight and
// the seatglue-driven no_ragdoll flag in Gui.cpp's own per-tick player-
// ped maintenance also contribute to the same counter, and the actual
// PED::SET_PED_CAN_RAGDOLL(false)/SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_
// RAGDOLL_OVERRIDE enforcement happens once per tick from there, gated
// on grace being non-zero) - this project has no such shared counter or
// per-tick maintenance routine to hook into (same gap CommandGod.hpp's
// own header comment already discloses), so onEnable()/onDisable()/
// onTick() below instead port the legacy CommandNoRagdoll.cpp's own
// LoopedCommand shape directly onto CommandTickDispatch: apply Self::
// GetPed().SetRagdoll(false)/Self::GetPlayer().SetFallDistanceOverride(
// 99999.0f) every tick while this is on, and restore SetRagdoll(true)/
// SetFallDistanceOverride(0.0f) on disable - exactly the legacy
// version's own OnTick()/OnDisable(). A simple on/off toggle, not a
// ref-count, so this doesn't compose with CommandSuperFlight/seatglue
// the way real Stand's own grace counter does - a disclosed
// simplification, not a silent one.
namespace Stand
{
	class CommandGrace : public CommandToggle
	{
	public:
		explicit CommandGrace(CommandList* parent) :
		    CommandToggle(parent, LIT("Gracefulness"), CMDNAMES("grace", "gracefulness", "noragdoll"), LIT("Prevents your ped from ragdolling."))
		{
		}

		void onEnable(Click& click) override
		{
			CommandTickDispatch::AddCommand(this);
			onTick();
		}

		void onDisable(Click& click) override
		{
			CommandTickDispatch::RemoveCommand(this);

			// Both calls guarded together, matching the legacy
			// CommandNoRagdoll.cpp's own OnDisable() exactly - not just
			// SetRagdoll().
			if (auto ped = Stand::Self::GetPed())
			{
				ped.SetRagdoll(true);
				Stand::Self::GetPlayer().SetFallDistanceOverride(0.0f);
			}
		}

		void onTick() override
		{
			auto ped = Stand::Self::GetPed();
			if (!ped)
				return;

			ped.SetRagdoll(false);
			Stand::Self::GetPlayer().SetFallDistanceOverride(99999.0f);
		}

		~CommandGrace() override
		{
			// Defensive - see CommandGod.hpp's own destructor comment.
			CommandTickDispatch::RemoveCommand(this);
		}
	};
}

namespace Stand::Features
{
	// The one real instance - see CommandGod.cpp's own comment for why
	// this is a function-local static behind an accessor rather than a
	// plain namespace-scope global. SelfGrid.cpp's own Gracefulness row
	// calls this to get the Stand::Command* GridItemStandCommand needs.
	Stand::CommandGrace& GetCommandGrace();
}
