#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for Network > Spoofing: mirrors MenuNetwork.cpp's
	// matchmakingGroup and matchmakingSrvGroup - every "enable spoofing
	// this" toggle is unconditional, so all six map directly onto
	// GridItemCommandToggle.
	//
	// Deliberately NOT included: mmregion/mmlanguage/mmplayercount/
	// mmmultiplexsessioncount and the whole spoofMMRegion subgroup
	// (spoofmmregion + its own conditional mmregion list) - every one of
	// these is a ConditionalItem gated on the toggle right next to it
	// being on, skipped for the same reason as every other
	// ConditionalItem in this system (mmplayercount/
	// mmmultiplexsessioncount are also IntCommandItems, a second,
	// independent reason).
	// All of the above stay reachable via the existing ImGui Network >
	// Spoofing category, untouched.
	class NetworkSpoofingGrid : public Grid
	{
	public:
		NetworkSpoofingGrid();

	protected:
		void Populate() override;
	};
}
