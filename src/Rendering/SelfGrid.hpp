#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Self > Main: mirrors MenuSelf.cpp's Globals and
	// Tools groups (all real BoolCommand/Command toggles+buttons) plus the
	// two unconditional Special Ability items, wired the same way MiscGrid
	// wires Debug > Misc.
	//
	// Deliberately NOT included (all need things this system doesn't have
	// yet, so nothing here fakes them):
	// - localvis (ConditionalItem gated on invis) and the Special Ability
	//   list dropdown (ConditionalItem gated on mpspecialability) - no
	//   conditional-visibility widget yet.
	// - The whole Wanted group - its ConditionalItem nesting (clearWanted/
	//   setWanted visibility depending on freezewanted/neverwanted) needs
	//   verifying against ConditionalItem's actual show/hide semantics
	//   before faithfully replicating, and it also uses an IntCommandItem
	//   slider, a different control from GridItemIntStepper's buttons.
	// - The whole Movement group - uses FloatCommandItem (no float widget
	//   yet) and more ConditionalItems (superrun/noclip/freecam-gated).
	// All of the above stay reachable via the existing ImGui Self > Main
	// category, untouched.
	class SelfGrid : public Grid
	{
	public:
		SelfGrid();

	protected:
		void Populate() override;
	};
}
