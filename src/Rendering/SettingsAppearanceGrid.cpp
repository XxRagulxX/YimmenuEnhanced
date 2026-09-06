#include "Rendering/SettingsAppearanceGrid.hpp"

#include "Rendering/GridItemFolder.hpp"
#include "Rendering/SettingsColoursGrid.hpp"
#include "Rendering/SettingsPositionGrid.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in SettingsGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		SettingsColoursGrid g_ColoursContent{};
		SettingsPositionGrid g_PositionContent{};
	}

	// Origin/spacer match every other content Grid's - see SelfGrid.cpp's
	// identical comment.
	SettingsAppearanceGrid::SettingsAppearanceGrid() :
	    Grid(1438, 587, 0)
	{
	}

	void SettingsAppearanceGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Colours", &g_ColoursContent));
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Position", &g_PositionContent));
	}
}
