#include "Rendering/SelfGrid.hpp"

#include "Commands/BoolCommand.hpp"
#include "Commands/Commands.hpp"
#include "Rendering/FreecamGrid.hpp"
#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemConditional.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemText.hpp"
#include "Rendering/InvisibilityGrid.hpp"
#include "Rendering/LevitationGrid.hpp"
#include "Rendering/MpSpecialAbilityGrid.hpp"
#include "Rendering/NoclipGrid.hpp"
#include "Rendering/SuperRunGrid.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/PlaceholderGrid.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/WeaponsGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp: unlike SelfGrid itself
		// (Self's root, registered in MenuGrid's sidebar table), these
		// are only ever reached through their own folder row below -
		// nothing else needs to know they exist.
		WeaponsGrid g_WeaponsContent{};
		InvisibilityGrid g_InvisibilityContent{};
		MpSpecialAbilityGrid g_MpSpecialAbilityContent{};
		SuperRunGrid g_SuperRunContent{};
		NoclipGrid g_NoclipContent{};
		FreecamGrid g_FreecamContent{};
		LevitationGrid g_LevitationContent{};

		// Wanted group: MenuSelf.cpp nests clearWanted (visible when NOT
		// freezewanted) and setWanted (visible when NOT neverwanted) as
		// their own Groups, each itself containing a further-conditional
		// row (clearwanted gated on !neverwanted inside clearWanted;
		// setwanted gated on !freezewanted inside setWanted). Flattened
		// (there's no literal "Group" container here - see
		// GridItemConditional's own class comment), both the clearwanted
		// and setwanted buttons end up needing the exact same combined
		// condition: neither freezewanted nor neverwanted is on. The
		// other three Wanted rows (neverwanted/wantedslider/freezewanted
		// toggles) each still only need the single outer gate they
		// already had, so they use GridItemConditional's plain joaat_t
		// overload directly instead.
		bool ShouldClearOrSetWanted()
		{
			auto* freezewanted = Commands::GetCommand<BoolCommand>("freezewanted"_J);
			auto* neverwanted = Commands::GetCommand<BoolCommand>("neverwanted"_J);
			return (!freezewanted || !freezewanted->GetState()) && (!neverwanted || !neverwanted->GetState());
		}
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	SelfGrid::SelfGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void SelfGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Globals (MenuSelf.cpp's globalsGroup) - every item here is an
		// unconditional BoolCommandItem in the original except invis,
		// which owns a dependent option of its own (localvis) and so
		// gets a real folder page instead (see InvisibilityGrid.hpp) -
		// listed first, ahead of the plain toggles, same as every other
		// section here (folders first, then checkboxes - a hidden
		// GridItemConditional row still reserves its own layout slot, so
		// a toggle's own dependent options are better off on their own
		// page than left flat and blank here while off).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Globals", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Invisibility", &g_InvisibilityContent));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "godmode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "otr"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "noragdoll"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "noidlekick"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "unlimitedoxygen"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mobileradio"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "keepplayerclean"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "disablecriticalhits"_J));

		// Tools (toolsGroup) - all plain CommandItem buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Tools", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "skipcutscene"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "skipconversation"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "suicide"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "heal"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "cleardamage"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "fillinventory"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "openwardrobe"_J));

		// Special Ability (specialAbilityGroup) - mpspecialability owns a
		// dependent option (the selspecialability dropdown), so it gets
		// its own folder page (MpSpecialAbilityGrid), listed first;
		// infspecialability has no dependent option of its own and stays
		// a plain toggle after it.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Special Ability", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "MP Special Ability", &g_MpSpecialAbilityContent));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infspecialability"_J));

		// Wanted (wantedGroup) - see ShouldClearOrSetWanted()'s own
		// comment above for how the original's nested ConditionalItem
		// groups flatten onto individual rows.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Wanted", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "clearwanted"_J),
		    ShouldClearOrSetWanted));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "neverwanted"_J),
		    "freezewanted"_J,
		    true));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "wantedslider"_J, "Level"),
		    "neverwanted"_J,
		    true));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "setwanted"_J),
		    ShouldClearOrSetWanted));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freezewanted"_J),
		    "neverwanted"_J,
		    true));

		// Movement (movementGroup) - superrun/noclip/freecam/levitate
		// each own one or more dependent options, so each gets its own
		// folder page, listed first; standonvehicles/disableactionmode/
		// superjump have no dependent options of their own and stay
		// plain toggles after them.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Movement", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Super Run", &g_SuperRunContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Noclip", &g_NoclipContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Freecam", &g_FreecamContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Levitation", &g_LevitationContent));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "standonvehicles"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "disableactionmode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "superjump"_J));

		// Self's other categories (MenuSelf.cpp's BuildWeaponsMenu()/
		// CreateOutfitsMenu()). Weapons now has its own content Grid
		// (WeaponsGrid); Outfit Editor is still placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Weapons", &g_WeaponsContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Outfit Editor", &GetPlaceholderGrid()));
	}
}
