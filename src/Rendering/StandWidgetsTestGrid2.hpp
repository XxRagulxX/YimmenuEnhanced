#pragma once
#include "Rendering/Grid.hpp"

namespace YimMenu::Rendering
{
	// Reachable from Settings > Debug > "Stand Widgets Test 2" -
	// exercises ListPointer/SliderRainbow live, on their own page, same
	// treatment as the first round of stand_widgets got (see
	// CommandStandWidgetsTest2.cpp's own class comment). Delete this
	// whole class (and its .cpp, and CommandStandWidgetsTest2.cpp/.hpp,
	// and the folder row in MiscGrid.cpp) once both are confirmed
	// working in-game.
	class StandWidgetsTestGrid2 : public Grid
	{
	public:
		StandWidgetsTestGrid2();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
