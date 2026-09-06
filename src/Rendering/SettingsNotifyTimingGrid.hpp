#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Settings > Notifications > Timing - real Stand's own Reading
	// Speed/Reading Start Delay/Min Duration/Max Duration + "Show Sample
	// Notification" (Small/Medium/Large) - see
	// Commands/Settings/CommandNotifyTiming.cpp.
	class SettingsNotifyTimingGrid : public Grid
	{
	public:
		SettingsNotifyTimingGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
