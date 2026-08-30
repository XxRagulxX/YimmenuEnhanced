#include "WeaponsGrid.hpp"

#include "BoolCommand.hpp"
#include "CommandCustomWeapon.hpp"
#include "Commands.hpp"
#include "GridItemCommandButton.hpp"
#include "GridItemCommandColor.hpp"
#include "GridItemCommandFloat.hpp"
#include "GridItemCommandInt.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandString.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemConditional.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "ListCommand.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Weapons.cpp's own RenderCustomWeaponsMenu() nests
		// customWeapons (gated on customweapon) inside customWeaponsGroup,
		// then further nests cutomWeaponTypes' per-type rows and
		// paintGunGroup (gated on isPaintGunEnabled) inside that -
		// flattened here into combined predicates the same way SelfGrid's
		// Wanted group and VehicleGrid's autodrive rows are, since this
		// system has no literal "Group" container to wrap once (see
		// GridItemConditional's own class comment).
		bool IsCustomWeaponEnabled()
		{
			auto* customweapon = Commands::GetCommand<BoolCommand>("customweapon"_J);
			return customweapon && customweapon->GetState();
		}

		Features::CustomWeapons CustomWeaponType()
		{
			auto* cmd = Commands::GetCommand<ListCommand>("customweapontype"_J);
			return static_cast<Features::CustomWeapons>(cmd ? cmd->GetState() : 0);
		}

		// cutomWeaponTypes' three per-type rows: each needs customweapon
		// on (the group they're nested in) AND its own type predicate
		// (isGravityGunEnabled/isVehicleGunEnabled/isPaintGunEnabled in
		// the original).
		bool IsGravityGunRow()
		{
			return IsCustomWeaponEnabled() && CustomWeaponType() == Features::CustomWeapons::GRAVITY_GUN;
		}

		bool IsVehicleGunRow()
		{
			return IsCustomWeaponEnabled() && CustomWeaponType() == Features::CustomWeapons::VEHICLE_GUN;
		}

		bool IsPaintGunTypeRow()
		{
			return IsCustomWeaponEnabled() && CustomWeaponType() == Features::CustomWeapons::PAINT_GUN;
		}

		// paintguncolor's own row is nested one level deeper still -
		// isPaintGunEnabled AND paintgunrainbowcolorenabled being *off*
		// (the original's inner ConditionalItem negates it).
		bool IsPaintGunColorRow()
		{
			if (!IsPaintGunTypeRow())
				return false;

			auto* rainbow = Commands::GetCommand<BoolCommand>("paintgunrainbowcolorenabled"_J);
			return !(rainbow && rainbow->GetState());
		}

		// paintGunGroup's own two conditional rows (style/speed) both
		// need customweapon on, PAINT_GUN selected, AND
		// paintgunrainbowcolorenabled on - paintGunGroup itself is only
		// added at all when isPaintGunEnabled (PAINT_GUN selected), and
		// customweapon gates the whole customWeapons group it lives in.
		bool IsPaintGunRainbowRow()
		{
			if (!IsPaintGunTypeRow())
				return false;

			auto* rainbow = Commands::GetCommand<BoolCommand>("paintgunrainbowcolorenabled"_J);
			return rainbow && rainbow->GetState();
		}
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	WeaponsGrid::WeaponsGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void WeaponsGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Globals (weaponsGlobalsGroup) - every conditional float/list row
		// is gated on the single BoolCommand right above it.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Globals", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infiniteammo"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infiniteclip"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "rapidfire"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "infiniteparachutes"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "ExplosiveAmmo"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "selectedexplosion"_J),
		    "ExplosiveAmmo"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "explosiondamage"_J),
		    "ExplosiveAmmo"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "explosioncamerashake"_J),
		    "ExplosiveAmmo"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "weapondamage"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "weapondamagescale"_J),
		    "weapondamage"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "meleedamage"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "meleedamagescale"_J),
		    "meleedamage"_J));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "explosionradius"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandFloat>(Theme::kContentWidth, kItemH, "explosionradiusscale"_J),
		    "explosionradius"_J));

		// Tools (weaponsToolsGroup) - all plain CommandItem buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Tools", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "giveallweapons"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "givemaxammo"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "opengunlocker"_J));

		// Ammu-Nation (weaponsAmmuNationGroup) is a hand-rolled ImGui
		// weapon search/stats/list-box UI with no Grid equivalent widgets
		// yet - deferred to Phase 3 once the searchable-list primitive
		// (GridItemSelectList) has a search-list-plus-detail-pane
		// consumer to model it on.

		// Gun Van (weaponsGunVanGroup) - all three items are
		// unconditional (two ListCommandItems, now that
		// GridItemCommandList exists, plus a plain CommandItem button).
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Gun Van", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "gunvan_weapon"_J));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "gunvan_slot"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "gunvan_apply"_J));

		// Aimbot (weaponsAimbotGroup) - the three head/drivers/dead-ped
		// toggles are all gated on aimbot directly.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Aimbot", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "aimbot"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "aimbotaimforhead"_J),
		    "aimbot"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "aimbottargetdrivers"_J),
		    "aimbot"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "aimbotreleasedeadped"_J),
		    "aimbot"_J));

		// Custom Weapons (RenderCustomWeaponsMenu()) - see this file's own
		// IsCustomWeaponEnabled()/CustomWeaponType()/IsGravityGunRow()/
		// IsVehicleGunRow()/IsPaintGunTypeRow()/IsPaintGunColorRow()/
		// IsPaintGunRainbowRow() for how the original's several levels of
		// nested ConditionalItem/Group flatten onto these rows' combined
		// predicates.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Custom Weapons", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "customweapon"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "customweaponenabledonweaponout"_J),
		    IsCustomWeaponEnabled));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "customweapontype"_J),
		    IsCustomWeaponEnabled));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "gravitygunlaunchonrelease"_J),
		    IsGravityGunRow));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandString>(Theme::kContentWidth, kItemH, "vehiclegunmodel"_J),
		    IsVehicleGunRow));
		AddConditionalColorCommandRows(items_draft, Theme::kContentWidth, "paintguncolor"_J, IsPaintGunColorRow);
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "paintgunrainbowcolorenabled"_J),
		    IsPaintGunTypeRow));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "paintgunrainbowcolorstyle"_J),
		    IsPaintGunRainbowRow));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "paintgunrainbowcolorspeed"_J),
		    IsPaintGunRainbowRow));

		LOGF(INFO, "[GridRenderer] WeaponsGrid populated with {} items", items_draft.size());
	}
}
