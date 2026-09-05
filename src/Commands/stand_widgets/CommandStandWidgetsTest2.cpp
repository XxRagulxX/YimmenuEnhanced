#include "Commands/stand_widgets/CommandStandWidgetsTest2.hpp"
#include "Commands/stand_widgets/ListPointer.hpp"
#include "Commands/stand_widgets/SliderRainbow.hpp"

namespace YimMenu::Features
{
	// Test-only commands for ListPointer/SliderRainbow (see Commands/
	// stand_widgets/'s own files) - reachable from Settings > Debug >
	// "Stand Widgets Test 2", a page of its own so none of this touches
	// any real feature. Once both are confirmed working in-game, this
	// whole file (and its test page) gets deleted, same as the first
	// round of these did.
	namespace
	{
		int g_TestListPtr = 0;
	}

	// A plain IntCommand (0-10) for SliderRainbow to drive - its own row
	// on the test page should visibly count up on its own once the
	// rainbow speed below is set above 0.
	static IntCommand _TestRainbowTarget{"standwidgets_testrainbowtarget", "Test: Rainbow Target", "SliderRainbow should drive this up on its own", 0, 10, 0};

	static StandWidgets::SliderRainbow _TestSliderRainbow{"standwidgets_testrainbow",
	    "Test: Slider Rainbow (speed, ms)",
	    "0 = off; otherwise ms per step - watch the Rainbow Target row above count up on its own",
	    &_TestRainbowTarget};

	static StandWidgets::ListPointer _TestListPointer{"standwidgets_testlistptr",
	    "Test: List Pointer",
	    "Confirms ListPointer writes through to the bound int*",
	    {{0, "Alpha"}, {1, "Bravo"}, {2, "Charlie"}},
	    &g_TestListPtr};

	int GetTestListPtr()
	{
		return g_TestListPtr;
	}
}
