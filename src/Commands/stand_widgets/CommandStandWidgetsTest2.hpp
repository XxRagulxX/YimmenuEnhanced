#pragma once

namespace YimMenu::Features
{
	// Read-back accessor for CommandStandWidgetsTest2.cpp's own
	// ListPointer test target - see that file's own comment.
	// StandWidgetsTestGrid2.cpp (Rendering/) watches this to prove the
	// pointer-bound command actually wrote through.
	int GetTestListPtr();
}
