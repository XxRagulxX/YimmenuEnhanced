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
	//
	// Also the Self submenu's root as far as MenuGrid/MenuNavigation are
	// concerned: Populate() appends a GridItemFolder row for each of
	// Self's other categories (Weapons, Outfit Editor) after the items
	// above, matching how Stand's own menu nests a category inside
	// another's list instead of a tab/sidebar entry. Weapons' folder
	// points at a real content Grid (WeaponsGrid, owned here since
	// nothing else reaches it) - see WeaponsGrid.hpp for what it covers.
	// Outfit Editor still points at the shared placeholder.
	class SelfGrid : public Grid
	{
	public:
		SelfGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
