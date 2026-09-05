#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Reachable from Settings > Debug > "Stand Widgets Test" - exercises
	// every new Commands/stand_widgets/ base class live, on its own page,
	// so none of it touches SelfGrid or any other real content while
	// it's being verified (see CommandStandWidgetsTest.cpp's own class
	// comment). Delete this whole class (and its .cpp, and
	// CommandStandWidgetsTest.cpp/.hpp, and the folder row in
	// MiscGrid.cpp) once every widget here is confirmed working in-game.
	class StandWidgetsTestGrid : public Grid
	{
	public:
		StandWidgetsTestGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
