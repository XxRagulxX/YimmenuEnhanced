#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Recovery > Businesses: mirrors MenuRecovery.cpp's
	// businessSafe, businessOverlay and businessManager groups.
	//
	// Deliberately NOT included:
	// - showwarehouse/showhangar/showbusinesses/shownightclub - all four
	//   are ConditionalItems gated on businessoverlay being on, skipped
	//   for the same reason as every other ConditionalItem in this
	//   system. businessoverlay's own toggle is unconditional and is
	//   included.
	// All of the above stay reachable via the existing ImGui Recovery >
	// Businesses category, untouched.
	class RecoveryBusinessesGrid : public Grid
	{
	public:
		RecoveryBusinessesGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
