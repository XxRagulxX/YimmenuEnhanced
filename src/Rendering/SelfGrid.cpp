#include "Rendering/SelfGrid.hpp"

#include "Commands/BoolCommand.hpp"
#include "Commands/Commands.hpp"
#include "Rendering/FreecamGrid.hpp"
#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/GridItemText.hpp"
#include "Rendering/InvisibilityGrid.hpp"
#include "Rendering/LevitationGrid.hpp"
#include "Rendering/MpSpecialAbilityGrid.hpp"
#include "Rendering/NoclipGrid.hpp"
#include "Rendering/OutfitEditorGrid.hpp"
#include "Rendering/SuperRunGrid.hpp"
#include "Util/Joaat.hpp"
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
		OutfitEditorGrid g_OutfitEditorContent{};
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
	    Grid(1438, 587, 0)
	{
	}

	void SelfGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Categories - every GridItemFolder this page has, grouped
		// together at the very top of the whole list rather than
		// scattered one per section: MenuSelf.cpp's BuildWeaponsMenu()/
		// CreateOutfitsMenu() (Weapons/Outfit Editor) plus every toggle
		// below that owns dependent options of its own and so got a real
		// folder page instead of leaving them flat as GridItemConditional
		// rows (a hidden conditional row still reserves its own layout
		// slot - see its own class comment) - Invisibility, MP Special
		// Ability, Super Run, Noclip, Freecam, Levitation.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Categories", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Weapons", &g_WeaponsContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Outfit Editor", &g_OutfitEditorContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Invisibility", &g_InvisibilityContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "MP Special Ability", &g_MpSpecialAbilityContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Super Run", &g_SuperRunContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Noclip", &g_NoclipContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Freecam", &g_FreecamContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Levitation", &g_LevitationContent));

		// Real Stand's own "Self" tab loose top-level rows (everything
		// after its 4 categories - Movement/Appearance/Weapons/
		// Bodyguards, not yet ported here; see the Categories folder
		// above for what's covered so far instead) - verified against
		// origin/stand-reference's own src/Commands/Self/CommandTabSelf.cpp,
		// in its exact order. Three are aliases of commands this project
		// already had under its own name (godmode, noragdoll, suicide) -
		// labelOverride matches Stand's own label without touching the
		// underlying command or its internal name, so nothing else
		// referencing them (Lua scripts, saved config, the sections
		// below) breaks. Still missing from this list: No Roll Cooldown
		// (real Stand's own version NOPs a private engine function found
		// by address pattern-scanning - not safe to guess an offset for
		// here), Respawn Delay (pokes a raw script-global bitset - same
		// "wrong offset breaks something real" risk), and Regeneration
		// Rate (needs its own CommandSliderRegenerationRate, a Stand
		// class not yet looked at) - flagged rather than guessed at.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Self", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "godmode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "autoheal"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "maxhealth"_J, std::nullopt, 25));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "noragdoll"_J, "Gracefulness"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "seatglue"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "wantedslider"_J, "Set Wanted Level"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "freezewanted"_J, "Lock Wanted Level"));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "fakewanted"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infinitestamina"_J));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "paralock"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "clumsiness"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "respawnrecall"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "refillhealth"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "refillarmour"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "suicide"_J, "End It All"));

		// Globals (MenuSelf.cpp's globalsGroup) - invis moved into the
		// Categories folder above, godmode/noragdoll moved into the real
		// Stand "Self" section above (see its own comment) - the rest
		// have no Stand equivalent found yet, kept as this project's own
		// extras rather than dropped.
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
		// into the Categories folder above (see its own comment);
		// infspecialability has no dependent option of its own and stays
		// a plain toggle here.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Special Ability", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infspecialability"_J));

		// Wanted (wantedGroup) - see ShouldClearOrSetWanted()'s own
		// comment above for how the original's nested ConditionalItem
		// groups flatten onto individual rows. watchCondition() (not
		// GridItemConditional) so a hidden row here doesn't reserve its
		// own layout slot - see its own doc comment in Grid.hpp.
		// wantedslider/freezewanted's own rows moved into the real Stand
		// "Self" section above (Set/Lock Wanted Level) - the remaining
		// three (clearwanted/neverwanted/setwanted) have no Stand
		// equivalent in its own top-level list and stay here as this
		// project's own extras. Still watching both flags below even
		// with those two rows gone: ShouldClearOrSetWanted() (clearwanted/
		// setwanted's own gate) and neverwanted's own gate between them
		// already cover every case that mattered for invalidation.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Wanted", Theme::kText));
		if (watchCondition(ShouldClearOrSetWanted))
			items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "clearwanted"_J));
		if (watchCondition("freezewanted"_J, true))
			items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "neverwanted"_J));
		if (watchCondition(ShouldClearOrSetWanted))
			items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "setwanted"_J));

		// Movement (movementGroup) - superrun/noclip/freecam/levitate
		// moved into the Categories folder above (see its own comment).
		// The next 7 rows (Water Walk through Self Freeze) are real
		// Stand's own Movement category (CommandTabSelf.cpp), in its own
		// order, each backed by a genuinely new command - see each one's
		// own file (src/Commands/Self/) for what it does and, where it
		// applies, what's simplified from Stand's real version and why.
		// Still missing from Stand's own Movement, deliberately (not
		// guessed at - see each new command file's own sibling notes on
		// this same gap): Walk Speed/Swim Speed (need a slider that
		// keeps re-applying every tick, not just on change - the same
		// gap already disclosed for Maximum Health/Fake Wanted, worse
		// here since it's not even optional - Stand's own version has to
		// re-assert every tick or the game's default speed wins back),
		// Friction (needs camera-relative input directions this project
		// has no equivalent Input:: helpers for), Graceful Landing/Move
		// Freedom (both need Stand's own hooking/ControlMgr
		// infrastructure), Drunk Mode (steering-drift timer logic not
		// yet ported), and the Fly/Floppy Mode subcategories (each needs
		// its own folder page, same treatment as Self's own 4 categories).
		// standonvehicles/disableactionmode have no Stand equivalent
		// found yet and stay as this project's own extras at the end.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Movement", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "superjump"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "waterwalk"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "airwalk"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "airswim"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "tennismode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "ghostmode"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "nocollision"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "selffreeze"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "standonvehicles"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "disableactionmode"_J));
	}
}
