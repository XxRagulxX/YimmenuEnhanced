#include "SelfGrid.hpp"

#include "BoolCommand.hpp"
#include "Commands.hpp"
#include "GridItemCommandButton.hpp"
#include "GridItemCommandFloat.hpp"
#include "GridItemCommandInt.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemConditional.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"
#include "Theme.hpp"
#include "WeaponsGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp: unlike SelfGrid itself
		// (Self's root, registered in MenuGrid's sidebar table),
		// WeaponsGrid is only ever reached through the "Weapons" folder
		// row below - nothing else needs to know it exists.
		WeaponsGrid g_WeaponsContent{};

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
		// unconditional BoolCommandItem in the original except localvis,
		// gated on invis (GridItemConditional's plain joaat_t overload).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Globals", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "godmode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "invis"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "localvis"_J),
		    "invis"_J));
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

		// Special Ability (specialAbilityGroup) - the ListCommandItem
		// dropdown is gated behind mpspecialability, same technique as
		// localvis above.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Special Ability", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infspecialability"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mpspecialability"_J, "Enable in MP"));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "selspecialability"_J, "Special Ability"),
		    "mpspecialability"_J));

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

		// Movement (movementGroup) - the four speed multipliers are each
		// gated on the toggle right above them (superrun/superrun/
		// noclip/freecam), same single-BoolCommand GridItemConditional
		// as localvis/mpspecialability above, just non-negated (shown
		// when the gate is *on*, matching FloatCommandItem's own
		// ConditionalItem calls here having no explicit negate arg).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Movement", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "standonvehicles"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "disableactionmode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "superrun"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "moverateoverride"_J),
		    "superrun"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "runsprintswimmultiplier"_J),
		    "superrun"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "superjump"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "noclip"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "noclipspeed"_J),
		    "noclip"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freecam"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "freecamspeed"_J),
		    "freecam"_J));
		// Levitation - flat here rather than its own nested folder page
		// (like MenuSelf.cpp's CollapsingHeaderItem gives it), since the
		// Grid renderer is still the opt-in debug-only alternate UI - a
		// dedicated LevitationGrid folder page is a reasonable follow-up
		// once more of this system's content gets its own nested pages.
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "levitate"_J));
		for (auto hash : {"levitateignorepitch"_J,
		         "keepmomentum"_J,
		         "levitateapplypitch"_J,
		         "levitaterotate"_J,
		         "levitatebuttoninstructions"_J})
		{
			items_draft.push_back(std::make_unique<GridItemConditional>(
			    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, hash),
			    "levitate"_J));
		}
		for (auto hash : {"levitatespeed"_J,
		         "levitatesprintmultiplier"_J,
		         "levitateaccel"_J,
		         "levitatepassivemin"_J,
		         "levitatepassivemax"_J,
		         "levitateassistup"_J,
		         "levitateassistdown"_J,
		         "levitateassistsnap"_J})
		{
			items_draft.push_back(std::make_unique<GridItemConditional>(
			    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, hash),
			    "levitate"_J));
		}
		for (auto hash : {"levitatepassivespeed"_J, "levitateassistdeadzone"_J})
		{
			items_draft.push_back(std::make_unique<GridItemConditional>(
			    std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, hash),
			    "levitate"_J));
		}

		// Self's other categories (MenuSelf.cpp's BuildWeaponsMenu()/
		// CreateOutfitsMenu()). Weapons now has its own content Grid
		// (WeaponsGrid); Outfit Editor is still placeholder-only.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Weapons", &g_WeaponsContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Outfit Editor", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] SelfGrid populated with {} items", items_draft.size());
	}
}
