#include "Rendering/SelfGrid.hpp"

#include "Commands/CommandToggleLegacy.hpp"
#include "Commands/Commands.hpp"
#include "Commands/Self/CommandAutoHeal.hpp"
#include "Commands/Self/CommandFakeWanted.hpp"
#include "Commands/Self/CommandGod.hpp"
#include "Commands/Self/CommandGrace.hpp"
#include "Commands/Self/CommandInfiniteStamina.hpp"
#include "Commands/Self/CommandParalock.hpp"
#include "Commands/Self/CommandSeatglue.hpp"
#include "Commands/Self/CommandWanted.hpp"
#include "Commands/Self/CommandWantedLock.hpp"
#include "Rendering/AppearanceGrid.hpp"
#include "Rendering/FreecamGrid.hpp"
#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandSlider.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemStandCommand.hpp"
#include "Rendering/GridItemText.hpp"
#include "Rendering/MovementGrid.hpp"
#include "Rendering/MpSpecialAbilityGrid.hpp"
#include "Rendering/NoclipGrid.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/WeaponsGrid.hpp"
#include "Util/Joaat.hpp"

namespace Stand::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp: unlike SelfGrid itself
		// (Self's root, registered in MenuGrid's sidebar table), these
		// are only ever reached through their own folder row below -
		// nothing else needs to know they exist.
		MovementGrid g_MovementContent{};
		AppearanceGrid g_AppearanceContent{};
		WeaponsGrid g_WeaponsContent{};
		MpSpecialAbilityGrid g_MpSpecialAbilityContent{};
		NoclipGrid g_NoclipContent{};
		FreecamGrid g_FreecamContent{};

		// Wanted group: MenuSelf.cpp nests setWanted (visible when NOT
		// neverwanted) in its own Group, itself containing a further-
		// conditional row (setwanted gated on !freezewanted). Flattened
		// (there's no literal "Group" container here - see
		// GridItemConditional's own class comment) onto
		// GridItemConditional's plain joaat_t overload directly.
		bool ShouldSetWanted()
		{
			auto* neverwanted = Commands::GetCommand<CommandToggleLegacy>("neverwanted"_J);
			return !Features::GetCommandWantedLock().m_on && (!neverwanted || !neverwanted->GetState());
		}
	}

	// Origin (1438, 587) matches every other content Grid's. Spacer is
	// 0, not 3 - confirmed against real Stand's own source (origin/
	// stand-reference) that individual list rows have zero gap between
	// them; the 3-unit spacer real Stand does use is only ever between
	// distinct chrome pieces (addressbar/tabs/list), never between rows -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	SelfGrid::SelfGrid() :
	    Grid(Theme::GetContentOrigin(), 0)
	{
	}

	void SelfGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Categories - real Stand's own 4 top-level categories under
		// Self (CommandTabSelf.cpp), in its own order - Movement/
		// Appearance/Weapons are each their own folder page now
		// (MovementGrid/AppearanceGrid/WeaponsGrid), matching Stand's
		// real tree instead of this project's old flat grouping (a
		// leftover of the classic StandEnhanced menu's own categories,
		// unrelated to Stand's). Bodyguards omitted: nothing's ported
		// there yet, and an empty folder that opens to nothing is worse
		// than no row at all - same reasoning this project already
		// applies to every other not-yet-ported category.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Movement", &g_MovementContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Appearance", &g_AppearanceContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Weapons", &g_WeaponsContent));

		// Real Stand's own "Self" tab loose top-level rows (everything
		// after its 4 categories) - verified against origin/stand-
		// reference's own src/Commands/Self/CommandTabSelf.cpp, in its
		// exact order. godmode/noragdoll (now CommandGod/CommandGrace)
		// have since migrated onto the ported Stand tree below, under
		// Stand's own real command names directly - suicide is still a
		// legacy command aliased via labelOverride (matches Stand's own
		// label without touching the underlying command or its internal
		// name, so nothing else referencing it - Lua scripts, saved
		// config, the sections below - breaks). Still missing from this
		// list: No Roll Cooldown
		// (real Stand's own version NOPs a private engine function found
		// by address pattern-scanning - not safe to guess an offset for
		// here), Respawn Delay (pokes a raw script-global bitset - same
		// "wrong offset breaks something real" risk), and Regeneration
		// Rate (needs its own CommandSliderRegenerationRate, a Stand
		// class not yet looked at) - flagged rather than guessed at.
		//
		// No section header of its own here (unlike every other section
		// in this file) - one repeating "Self" while already inside the
		// Self tab (MenuGrid's own breadcrumb already reads "... > Self")
		// is a redundant label, not a distinguishing one; the loose rows
		// below read fine directly following "Categories" above.
		// Migrations off the legacy system onto the ported Stand tree
		// (Self category pilot - CommandGod, then CommandAutoHeal, then
		// CommandGrace) - GridItemStandCommand takes a live
		// Stand::Command* directly (there's no Stand::CommandList tree
		// for "Self" to walk generically yet, so this is still one
		// hand-written row per command here, same as every other line in
		// this function - see each command's own Commands/Self/Command*.hpp
		// for its actual logic).
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandGod()));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandAutoHeal()));
		items_draft.push_back(std::make_unique<GridItemCommandSlider>(Theme::kContentWidth, kItemH, "maxhealth"_J, std::nullopt, 25));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandGrace()));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandSeatglue()));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandWanted()));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandWantedLock()));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandFakeWanted()));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandInfiniteStamina()));
		items_draft.push_back(std::make_unique<GridItemStandCommand>(Theme::kContentWidth, kItemH, &Features::GetCommandParalock()));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "clumsiness"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "respawnrecall"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "refillhealth"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "refillarmour"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "suicide"_J, "End It All"));

		// Not part of Stand's own Self tab at all - MP Special Ability/
		// Noclip/Freecam actually belong to a different Stand tab
		// entirely (confirmed: CommandTabGame.cpp, not CommandTabSelf.cpp,
		// via origin/stand-reference). Kept reachable here rather than
		// deleted or hidden - moving them to wherever that tab maps to in
		// this project's own sidebar is its own separate piece of work,
		// not done yet.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Other (not Self in Stand)", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "MP Special Ability", &g_MpSpecialAbilityContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Noclip", &g_NoclipContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Freecam", &g_FreecamContent));

		// Globals (MenuSelf.cpp's globalsGroup) - godmode/noragdoll moved
		// into the real Stand "Self" section above (see its own
		// comment) - the rest have no Stand equivalent found yet, kept
		// as this project's own extras rather than dropped.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Globals", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "otr"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "noidlekick"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "unlimitedoxygen"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "mobileradio"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "keepplayerclean"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "disablecriticalhits"_J));

		// Tools (toolsGroup) - all plain CommandItem buttons. suicide/heal
		// moved into the real Stand "Self" section above (End It All/
		// Refill Health+Armour) - the rest are this project's own extras.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Tools", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "skipcutscene"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "skipconversation"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "cleardamage"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "fillinventory"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "openwardrobe"_J));

		// Special Ability (specialAbilityGroup) - mpspecialability moved
		// into the "Other" section above (see its own comment);
		// infspecialability has no dependent option of its own and stays
		// a plain toggle here.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Special Ability", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infspecialability"_J));

		// Wanted (wantedGroup) - see ShouldSetWanted()'s own comment above
		// for how the original's nested ConditionalItem groups flatten
		// onto individual rows. watchCondition() (not GridItemConditional)
		// so a hidden row here doesn't reserve its own layout slot - see
		// its own doc comment in Grid.hpp. wantedslider/freezewanted's
		// own rows moved into the real Stand "Self" section above (Set/
		// Lock Wanted Level) - neverwanted/setwanted have no Stand
		// equivalent in its own top-level list and stay here as this
		// project's own extras.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Wanted", Theme::kText));
		if (watchCondition([] {
			    return !Features::GetCommandWantedLock().m_on;
		    }))
			items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "neverwanted"_J));
		if (watchCondition(ShouldSetWanted))
			items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "setwanted"_J));

		// Movement Extras - standonvehicles/disableactionmode have no
		// confirmed Stand equivalent (unlike MP Special Ability/Noclip/
		// Freecam above, nothing's turned up showing these belong to a
		// specific other tab either) - kept here rather than folded into
		// the real Movement folder above, since that one's meant to
		// mirror Stand's own content exactly.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Movement Extras", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "standonvehicles"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "disableactionmode"_J));
	}
}
