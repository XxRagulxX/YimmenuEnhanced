#include "Rendering/RecoveryHeistsGrid.hpp"

#include "Rendering/ApartmentHeistGrid.hpp"
#include "Rendering/CayoPericoHeistGrid.hpp"
#include "Rendering/DiamondCasinoHeistGrid.hpp"
#include "Rendering/DoomsdayHeistGrid.hpp"
#include "Rendering/KortzCenterHeistGrid.hpp"
#include "Rendering/MissionsGrid.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid. Each already hardcodes its
		// own origin below where this Grid's own tab strip draws - see
		// their own class comments.
		ApartmentHeistGrid g_ApartmentContent{};
		DiamondCasinoHeistGrid g_DiamondCasinoContent{};
		CayoPericoHeistGrid g_CayoPericoContent{};
		DoomsdayHeistGrid g_DoomsdayContent{};
		MissionsGrid g_MissionsContent{};
		KortzCenterHeistGrid g_KortzCenterContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). This Grid's own item list is just
	// the tab strip below - everything else lives in whichever target is
	// active.
	RecoveryHeistsGrid::RecoveryHeistsGrid() :
	    GridTabbed(1438, 587, 3)
	{
	}

	void RecoveryHeistsGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		InitTabs(items_draft,
		    static_cast<int16_t>(Theme::kContentItemHeight),
		    {"Apartment Heist", "Diamond Casino Heist", "Cayo Perico Heist", "Doomsday Heist", "Missions", "Kortz Center Heist"},
		    {&g_ApartmentContent, &g_DiamondCasinoContent, &g_CayoPericoContent, &g_DoomsdayContent, &g_MissionsContent, &g_KortzCenterContent});

		LOGF(INFO, "[GridRenderer] RecoveryHeistsGrid populated with {} items", items_draft.size());
	}
}
