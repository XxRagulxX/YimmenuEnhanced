#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Settings > Notifications - real Stand's own CommandListNotifySettings
	// (Commands/Online/CommandListNotifySettings.cpp on origin/stand-reference):
	// Type, Custom Position (a nested folder, only relevant while Type is
	// "Stand, Custom Position"), Invert Flow, Width, Padding, Border/
	// Flash/Background Colour, a "Flash Notification" sample button, and
	// a Timing folder (Reading Speed/Start Delay/Min/Max Duration + Show
	// Sample Notification). See Commands/Settings/CommandNotify*.cpp for
	// the real commands behind every row here, and each of those files'
	// own comments for what's simplified from real Stand's version
	// (no live minimap-rect query for "Next To Map", no literal "Copy
	// Primary/Background Colour" button widgets, no persistent preview
	// toast tied to this page's own visibility).
	class SettingsNotificationsGrid : public Grid
	{
	public:
		SettingsNotificationsGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
