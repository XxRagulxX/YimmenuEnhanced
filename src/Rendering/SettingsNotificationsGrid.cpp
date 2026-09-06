#include "Rendering/SettingsNotificationsGrid.hpp"

#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandColor.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemFolder.hpp"
#include "Rendering/SettingsNotifyPositionGrid.hpp"
#include "Rendering/SettingsNotifyTimingGrid.hpp"
#include "Rendering/Theme.hpp"
#include "Util/Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in SettingsGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		SettingsNotifyPositionGrid g_PositionContent{};
		SettingsNotifyTimingGrid g_TimingContent{};
	}

	// Origin/spacer match every other content Grid's - see SelfGrid.cpp's
	// identical comment.
	SettingsNotificationsGrid::SettingsNotificationsGrid() :
	    Grid(1438, 587, 0)
	{
	}

	void SettingsNotificationsGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "notifytype"_J, "Type"));

		// Only takes effect with Type set to "Stand, Custom Position" -
		// same as Invert Flow below (see CommandNotifyPosition.cpp/
		// CommandNotifyFlow.cpp's own comments) - not gated behind a
		// GridItemConditional here since both remain meaningful to look
		// at (and safely no-op) regardless of the current Type.
		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Custom Position", &g_PositionContent));

		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "notifyinvertflow"_J, "Invert Flow"));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "notifywidth"_J, "Width", 10));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "notifypadding"_J, "Padding", 10));

		AddColorCommandRows(items_draft, Theme::kContentWidth, "notifyborder"_J, "Border Colour");
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "notifyborderrainbow"_J, "Rainbow Mode"));

		AddColorCommandRows(items_draft, Theme::kContentWidth, "notifyflash"_J, "Flash Colour");
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "notifyflashrainbow"_J, "Rainbow Mode"));

		AddColorCommandRows(items_draft, Theme::kContentWidth, "notifybg"_J, "Background Colour");

		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "notifyflashnow"_J, "Flash Notification"));

		items_draft.push_back(std::make_unique<GridItemFolder>(Theme::kContentWidth, kItemH, "Timing", &g_TimingContent));
	}
}
