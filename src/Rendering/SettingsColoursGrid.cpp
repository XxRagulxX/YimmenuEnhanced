#include "Rendering/SettingsColoursGrid.hpp"

#include "Rendering/GridItemCommandColor.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/Theme.hpp"
#include "Util/Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Origin/spacer match every other content Grid's - see SelfGrid.cpp's
	// identical comment.
	SettingsColoursGrid::SettingsColoursGrid() :
	    Grid(1438, 587, 0)
	{
	}

	void SettingsColoursGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Primary Colour + its own nested Rainbow Mode row, same order
		// real Stand's own CommandTabStand.cpp builds them in.
		AddColorCommandRows(items_draft, Theme::kContentWidth, "primary"_J, "Primary Colour");
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "rainbow"_J, "Rainbow Mode"));

		AddColorCommandRows(items_draft, Theme::kContentWidth, "background"_J, "Background Colour");
	}
}
