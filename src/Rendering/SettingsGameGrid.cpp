#include "Rendering/SettingsGameGrid.hpp"

#include "Commands/BoolCommand.hpp"
#include "Commands/Commands.hpp"
#include "Rendering/GridItemCommandColor.hpp"
#include "Rendering/GridItemCommandToggle.hpp"
#include "Rendering/GridItemConditional.hpp"
#include "Rendering/GridItemText.hpp"
#include "Util/Joaat.hpp"
#include "Rendering/Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Each group's own colour-swatch rows repeat the same
		// espdraw*-is-on condition their plain toggles already use -
		// named here once each rather than re-typing the same lambda at
		// every AddConditionalColorCommandRows() call site below.
		bool IsPlayerEspOn()
		{
			auto* espdrawplayers = Commands::GetCommand<BoolCommand>("espdrawplayers"_J);
			return espdrawplayers && espdrawplayers->GetState();
		}

		bool IsPedEspOn()
		{
			auto* espdrawpeds = Commands::GetCommand<BoolCommand>("espdrawpeds"_J);
			return espdrawpeds && espdrawpeds->GetState();
		}

		bool IsObjectEspOn()
		{
			auto* espdrawobjects = Commands::GetCommand<BoolCommand>("espdrawobjects"_J);
			return espdrawobjects && espdrawobjects->GetState();
		}
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	SettingsGameGrid::SettingsGameGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void SettingsGameGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Player ESP (playerEsp) - every row below espdrawplayers is
		// gated on it; namecolorplayers/skeletoncolorplayers are
		// ColorCommand swatches via AddConditionalColorCommandRows.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Player ESP", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdrawplayers"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdrawdeadplayers"_J),
		    "espdrawplayers"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espnameplayers"_J, "Player Name"),
		    "espdrawplayers"_J));
		AddConditionalColorCommandRows(items_draft, Theme::kContentWidth, "namecolorplayers"_J, IsPlayerEspOn);
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdistanceplayers"_J, "Player Distance"),
		    "espdrawplayers"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espskeletonplayers"_J, "Player Skeleton"),
		    "espdrawplayers"_J));
		AddConditionalColorCommandRows(items_draft, Theme::kContentWidth, "skeletoncolorplayers"_J, IsPlayerEspOn);

		// Ped ESP (pedEsp) - same shape as Player ESP above, gated on
		// espdrawpeds instead.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Ped ESP", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdrawpeds"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdrawdeadpeds"_J),
		    "espdrawpeds"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espmodelspeds"_J, "Ped Hashes"),
		    "espdrawpeds"_J));
		AddConditionalColorCommandRows(items_draft, Theme::kContentWidth, "hashcolorpeds"_J, IsPedEspOn);
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espnetinfopeds"_J, "Ped Net Info"),
		    "espdrawpeds"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espscriptinfopeds"_J, "Ped Script Info"),
		    "espdrawpeds"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdistancepeds"_J, "Ped Distance"),
		    "espdrawpeds"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espskeletonpeds"_J, "Ped Skeleton"),
		    "espdrawpeds"_J));
		AddConditionalColorCommandRows(items_draft, Theme::kContentWidth, "skeletoncolorpeds"_J, IsPedEspOn);

		// Object ESP (objectEsp) - gated on espdrawobjects.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Object ESP", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdrawobjects"_J));
		AddConditionalColorCommandRows(items_draft, Theme::kContentWidth, "hashcolorobjects"_J, IsObjectEspOn);
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espnetinfoobjects"_J, "Object Net Info"),
		    "espdrawobjects"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espscriptinfoobjects"_J, "Object Script Info"),
		    "espdrawobjects"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "espdistanceobjects"_J, "Object Distance"),
		    "espdrawobjects"_J));
	}
}
