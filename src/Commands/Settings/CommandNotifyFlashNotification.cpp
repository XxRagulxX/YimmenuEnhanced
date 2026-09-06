#include "Commands/stand_widgets/LambdaAction.hpp"
#include "Rendering/Notifications.hpp"

namespace YimMenu::Features
{
	// Ported from real Stand's own "Flash Notification" (Commands/Online/
	// CommandListNotifySettings.cpp on origin/stand-reference) - real
	// Stand's own version keeps a persistent preview toast alive tied to
	// this settings page's own visibility and re-flashes it on request;
	// this project's overlay has no equivalent "preview toast tied to a
	// page being open" concept, so this is a plain button instead,
	// showing one real sample notification - which already flashes
	// Flash Colour automatically on every creation/re-trigger (see
	// Notifications.cpp's own ShowImpl()), demonstrating the same
	// automatic behaviour real Stand's own preview toast does, just
	// without staying pinned open while this page is.
	static StandWidgets::LambdaAction _NotifyFlashNotification{"notifyflashnow",
	    "Flash Notification",
	    "Shows a sample notification, demonstrating the Flash Colour/Border Colour transition above.",
	    [] {
		    Notifications::Show("Sample Notification", "This is what a notification looks like.");
	    }};
}
