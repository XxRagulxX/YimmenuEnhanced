#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Self > Main: mirrors MenuSelf.cpp's Globals, Tools,
	// Special Ability, Wanted and Movement groups in full. localvis and
	// the Special Ability list dropdown are each a single GridItemConditional
	// gated on invis/mpspecialability directly (matching ConditionalItem's
	// own single-BoolCommand gate). Wanted's two-level ConditionalItem
	// nesting (clearWanted/setWanted groups, each itself containing a
	// further-conditional row) is flattened into per-row conditions - see
	// SelfGrid.cpp's own comment on ShouldClearOrSetWanted() for the
	// combined-AND case neither BoolCommand alone can express. Movement's
	// four speed multipliers (moverateoverride/runsprintswimmultiplier/
	// noclipspeed/freecamspeed) are plain single-BoolCommand
	// GridItemConditionals (superrun/superrun/noclip/freecam).
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
