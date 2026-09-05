#include "Commands/stand_widgets/CommandStandWidgetsTest.hpp"
#include "Commands/stand_widgets/LambdaAction.hpp"
#include "Commands/stand_widgets/LambdaListSelect.hpp"
#include "Commands/stand_widgets/LambdaSlider.hpp"
#include "Commands/stand_widgets/LambdaToggle.hpp"
#include "Commands/stand_widgets/NamedValueSlider.hpp"
#include "Commands/stand_widgets/SliderPointer.hpp"
#include "Commands/stand_widgets/TogglePointer.hpp"
#include "Rendering/Notifications.hpp"

#include <format>

namespace YimMenu::Features
{
	// Test-only commands for the new stand_widgets base classes (see
	// Commands/stand_widgets/'s own files) - reachable from Settings >
	// Debug > "Stand Widgets Test" (Rendering/StandWidgetsTestGrid.cpp),
	// a page of its own so none of this touches SelfGrid or any other
	// real content. Every one just posts a toast confirming its own
	// callback actually fired with the right value - nothing here has a
	// real gameplay effect. Once every new widget type here is confirmed
	// working in-game, this whole file (and its test page) gets deleted.
	namespace
	{
		bool g_TestBool = false;
		int g_TestInt = 0;
	}

	static StandWidgets::LambdaToggle _TestLambdaToggle{"standwidgets_testtoggle",
	    "Test: Lambda Toggle",
	    "Confirms LambdaToggle's onEnable/onDisable callbacks fire",
	    [] {
		    Notifications::Show("Stand Widgets Test", "LambdaToggle enabled", NotificationType::Success);
	    },
	    [] {
		    Notifications::Show("Stand Widgets Test", "LambdaToggle disabled", NotificationType::Info);
	    }};

	static StandWidgets::LambdaAction _TestLambdaAction{"standwidgets_testaction",
	    "Test: Lambda Action",
	    "Confirms LambdaAction's onCall callback fires",
	    [] {
		    Notifications::Show("Stand Widgets Test", "LambdaAction clicked", NotificationType::Success);
	    }};

	static StandWidgets::LambdaSlider _TestLambdaSlider{"standwidgets_testslider",
	    "Test: Lambda Slider",
	    "Confirms LambdaSlider's onChange callback fires with the new value",
	    0,
	    10,
	    0,
	    [](int value) {
		    Notifications::Show("Stand Widgets Test", std::format("LambdaSlider changed to {}", value), NotificationType::Info);
	    }};

	static StandWidgets::LambdaListSelect _TestLambdaListSelect{"standwidgets_testlist",
	    "Test: Lambda List Select",
	    "Confirms LambdaListSelect's onChange callback fires with the new value",
	    {{0, "Alpha"}, {1, "Bravo"}, {2, "Charlie"}},
	    0,
	    [](int value) {
		    Notifications::Show("Stand Widgets Test", std::format("LambdaListSelect changed to {}", value), NotificationType::Info);
	    }};

	// TogglePointer/SliderPointer's own test is different from the three
	// above: what matters is that *ptr actually gets written, not that a
	// callback fires (they have none) - StandWidgetsTestGrid.cpp's own
	// "Check Pointer Values" button reads g_TestBool/g_TestInt back
	// through GetTestBool()/GetTestInt() below to prove it, independent
	// of what each row's own widget already displays (see that button's
	// own comment for why that independence matters).
	static StandWidgets::TogglePointer _TestTogglePointer{"standwidgets_testtoggleptr",
	    "Test: Toggle Pointer",
	    "Confirms TogglePointer writes through to the bound bool*",
	    &g_TestBool};

	static StandWidgets::SliderPointer _TestSliderPointer{"standwidgets_testsliderptr",
	    "Test: Slider Pointer",
	    "Confirms SliderPointer writes through to the bound int*",
	    &g_TestInt,
	    0,
	    100};

	static StandWidgets::NamedValueSlider _TestNamedValueSlider{"standwidgets_testnamedvalue",
	    "Test: Named Value Slider",
	    "Confirms 0 displays as \"Don't Override\" instead of the number",
	    0,
	    100,
	    0,
	    0,
	    "Don't Override"};

	bool GetTestBool()
	{
		return g_TestBool;
	}

	int GetTestInt()
	{
		return g_TestInt;
	}
}
