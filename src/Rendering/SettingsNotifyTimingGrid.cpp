#include "Rendering/SettingsNotifyTimingGrid.hpp"

#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemText.hpp"
#include "Rendering/Theme.hpp"
#include "Util/Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = Theme::kContentItemHeight;
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
	}

	// Origin/spacer match every other content Grid's - see SelfGrid.cpp's
	// identical comment.
	SettingsNotifyTimingGrid::SettingsNotifyTimingGrid() :
	    Grid(1438, 587, 0)
	{
	}

	void SettingsNotifyTimingGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "readspeed"_J, "Reading Speed (WPM)", 10));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "readstartdelay"_J, "Reading Start Delay (ms)", 10));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "notifyminduration"_J, "Min Duration (ms)", 100));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "notifymaxduration"_J, "Max Duration (ms)", 100));

		// Real Stand's own nested "Show Sample Notification" group
		// (Small/Medium/Large) - a plain text sub-header followed by its
		// three buttons in this same page, same "no folder for a group
		// this small" precedent Settings > Game's own ESP groups already
		// use, rather than a separate Grid page just for three buttons.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Show Sample Notification", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "notifysamplesmall"_J, "Small"));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "notifysamplemedium"_J, "Medium"));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "notifysamplelarge"_J, "Large"));
	}
}
