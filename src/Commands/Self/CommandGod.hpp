#pragma once
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandToggle.hpp"

#include "World/Self.hpp"

// First real feature migrated onto the ported Stand tree (the "Self"
// category pilot - see this file's own construction site,
// Commands/Self/CommandGod.cpp, for why it isn't parented into a real
// CommandList yet). Replaces the legacy Commands/Self/CommandGodmode.cpp
// (Stand::Features::Godmode, a LoopedCommand) - SelfGrid.cpp's own
// "godmode" row now points here instead (via GridItemStandCommand, not
// GridItemCommandToggle - see that row's own comment in SelfGrid.cpp).
//
// Matches real Stand's own CommandGod (Commands/Self/CommandGod.hpp on
// origin/stand-reference) for command_names/menu_name/help_text:
//   explicit CommandGod(CommandList* const parent)
//       : CommandToggle(parent, LOC("GOD"), { CMDNAME("godmode"), CMDNAME("immortality") }, LOC("GOD_H"))
// LOC("GOD")/LOC("GOD_H") are translation-table KEYS, not the displayed
// text itself - real Stand's own English text for them (confirmed
// against its own reference screenshot) is "Immortality" and "Makes
// your character unable to die.", used directly here via LIT() since
// this project has no translation table of its own to resolve a LOC key
// through (see Util/Label.hpp's own class comment) - an earlier pass
// here wrongly guessed "God Mode" instead of actually checking what
// real Stand displays. Real Stand's own onEnable()/onDisable() just flip
// its own g_gui.godmode flag, with the actual enforcement happening every
// tick somewhere else entirely in its own renderer (not ported) - this
// project has no such "somewhere else" to hook into, so onEnable()/
// onDisable()/onTick() below instead port the legacy Godmode.cpp's own
// LoopedCommand shape directly onto CommandTickDispatch (see that class's
// own doc comment for why): apply the enforcement immediately on enable/
// disable for instant feedback, same as the legacy version's own
// OnDisable(), and keep re-asserting it every tick while on (forcing it
// back off the instant the ped's actually dead, then back on again once
// alive - e.g. after a respawn) for as long as this stays toggled on,
// exactly the safety behaviour legacy Godmode.cpp's own OnTick() had.
//
// The enforcement itself is Entity::SetProofs() (all 8 SET_ENTITY_PROOFS
// flags), not SetInvincible() - traced real Stand's own actual mechanism
// down through Rendering/Gui.cpp's own per-tick player-ped maintenance
// (isGodmodeActive()/onGodmodeDisable()) into Core/AbstractEntity.cpp's
// own godmodeEnable()/godmodeDisable(), which call SET_ENTITY_PROOFS(
// handle, 1,1,1,1,1,1,1,1) / all-zeros - a materially different,
// more comprehensive native than SET_ENTITY_INVINCIBLE, which real
// Stand's own godmode never calls at all. Real Stand's own
// godmodeEnable() also writes a raw CPed::m_nPhysicalFlags.
// bNotDamagedByAnything(ButHasReactions) struct field alongside the
// native call (gated on a no_ragdoll parameter this project doesn't
// model) - not ported here, since this project has no CPhysical struct
// layout to write that field through yet (see Game/fwEntity.hpp/
// Game/CEntity.hpp's own comments - this project's actual gta_entity.hpp
// equivalent stops one class short of CPhysical). A disclosed gap, not a
// silent one - revisit once CPhysical exists.
//
// onDisable() also ports real Stand's own deferred/race-safe clear -
// onDisable(Click&) is called with m_on already flipped to false (see
// CommandToggleNoCorrelation::toggleState()), matching real Stand's own
// "g_gui.godmode = false" happening synchronously before its own
// ensureScriptThread(click, onGodmodeDisable) call - so the guard below
// (checking m_on again once the deferred callback actually runs) is
// exactly real Stand's own race guard against godmode being toggled back
// on again before the deferred clear executes.
namespace Stand
{
	class CommandGod : public CommandToggle
	{
	public:
		explicit CommandGod(CommandList* parent) :
		    CommandToggle(parent, LIT("Immortality"), CMDNAMES("godmode", "immortality"), LIT("Makes your character unable to die."))
		{
		}

		void onEnable(Click& click) override
		{
			if (auto ped = Stand::Self::GetPed())
				ped.SetProofs(true);

			CommandTickDispatch::AddCommand(this);
		}

		void onDisable(Click& click) override
		{
			CommandTickDispatch::RemoveCommand(this);

			click.ensureScriptThread([this] {
				// m_on already reflects the new (off) state by the time
				// onDisable() runs - only actually clear the ped's own
				// proofs if it hasn't been toggled back on again in the
				// meantime (see this file's own header comment).
				if (m_on)
					return;

				if (auto ped = Stand::Self::GetPed())
					ped.SetProofs(false);
			});
		}

		void onTick() override
		{
			auto ped = Stand::Self::GetPed();
			if (!ped)
				return;

			ped.SetProofs(!ped.IsDead());
		}

		~CommandGod() override
		{
			// Defensive - onDisable() already removes this on a normal
			// user-driven toggle-off, but a still-enabled instance being
			// destroyed (nothing does this today; every real instance is
			// a function-local static that outlives the process) should
			// never leave a dangling pointer behind in the dispatcher.
			CommandTickDispatch::RemoveCommand(this);
		}
	};
}

namespace Stand::Features
{
	// The one real instance - see CommandGod.cpp for why this is a
	// function-local static behind an accessor rather than a plain
	// namespace-scope global. SelfGrid.cpp's own "godmode" row calls
	// this to get the Stand::Command* GridItemStandCommand needs.
	Stand::CommandGod& GetCommandGod();
}
