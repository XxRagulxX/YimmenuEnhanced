#include "Rendering/StandWidgetsTestGrid.hpp"

#include "Commands/stand_widgets/CommandStandWidgetsTest.hpp"
#include "Rendering/GridItemButton.hpp"
#include "Rendering/GridItemCommandButton.hpp"
#include "Rendering/GridItemCommandInt.hpp"
#include "Rendering/GridItemCommandList.hpp"
#include "Rendering/GridItemCommandNamedValueSlider.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
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
	StandWidgetsTestGrid::StandWidgetsTestGrid() :
	    Grid(1438, 587, 0)
	{
	}

	void StandWidgetsTestGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Lambda widgets (watch for a toast on each)", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "standwidgets_testtoggle"_J));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "standwidgets_testaction"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "standwidgets_testslider"_J));
		items_draft.push_back(std::make_unique<GridItemCommandList>(Theme::kContentWidth, kItemH, "standwidgets_testlist"_J));

		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Pointer-bound widgets", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "standwidgets_testtoggleptr"_J));
		items_draft.push_back(std::make_unique<GridItemCommandInt>(Theme::kContentWidth, kItemH, "standwidgets_testsliderptr"_J));

		// Reads Features::GetTestBool()/GetTestInt() directly, independent
		// of what the two rows above display themselves - proves the
		// write actually reached the bound bool*/int*, not just each
		// command's own internal copy (which would look right even if
		// OnEnable()/OnDisable()/OnChange() were broken and never wrote
		// through at all).
		items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, kItemH, "Check Pointer Values", [] {
			Notifications::Show("Stand Widgets Test",
			    std::format("bool* = {}, int* = {}", Features::GetTestBool(), Features::GetTestInt()),
			    NotificationType::Info);
		}));

		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Named value slider (0 = \"Don't Override\")", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandNamedValueSlider>(Theme::kContentWidth, kItemH, "standwidgets_testnamedvalue"_J));
	}
}
