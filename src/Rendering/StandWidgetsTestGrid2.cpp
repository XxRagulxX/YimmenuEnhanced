#include "Rendering/StandWidgetsTestGrid2.hpp"

#include "Commands/stand_widgets/CommandStandWidgetsTest2.hpp"
#include "Rendering/GridItemButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemText.hpp"
#include "Rendering/Notifications.hpp"
#include "Rendering/Theme.hpp"
#include "Util/Joaat.hpp"

#include <format>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Origin/spacer match every other content Grid's - see SelfGrid.cpp's
	// identical comment.
	StandWidgetsTestGrid2::StandWidgetsTestGrid2() :
	    Grid(1438, 587, 0)
	{
	}

	void StandWidgetsTestGrid2::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Slider Rainbow (set speed, watch Target count up)", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "standwidgets_testrainbow"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "standwidgets_testrainbowtarget"_J));

		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "List Pointer", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "standwidgets_testlistptr"_J));
		items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, kItemH, "Check Pointer Value", [] {
			Notifications::Show("Stand Widgets Test 2", std::format("int* = {}", Features::GetTestListPtr()), NotificationType::Info);
		}));
	}
}
