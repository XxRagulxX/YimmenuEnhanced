#include "Rendering/ApartmentHeistGrid.hpp"

#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Origin sits right below where RecoveryHeistsGrid's own tab strip
	// draws (587 + 32-tall strip + 3 spacer) - see this class's own
	// header comment.
	ApartmentHeistGrid::ApartmentHeistGrid() :
	    Grid(1438, 622, 3)
	{
	}

	void ApartmentHeistGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Heist Cuts (cuts)
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Heist Cuts", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "apartmentheistcut1"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "apartmentheistcut3"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "apartmentheistcut2"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "apartmentheistcut4"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistforceready"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistsetcuts"_J));

		// Heist Setups (setups)
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Heist Setups", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistsetup"_J));

		// Hacking (hacks)
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Hacking", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistskiphacking"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistskipdrilling"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistskipswiping"_J));

		// Misc (misc)
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Misc", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistinstantfinish"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "apartmentheistinstantfinishpacific"_J));

		LOGF(INFO, "[GridRenderer] ApartmentHeistGrid populated with {} items", items_draft.size());
	}
}
