#pragma once

namespace YimMenu::Features
{
	// Read-back accessors for CommandStandWidgetsTest.cpp's own
	// TogglePointer/SliderPointer test targets - see that file's own
	// comment. StandWidgetsTestGrid.cpp (Rendering/) watches these to
	// prove the pointer-bound commands actually wrote through.
	bool GetTestBool();
	int GetTestInt();
}
