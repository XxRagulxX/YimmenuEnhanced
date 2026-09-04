#include "Rendering/HotkeysGrid.hpp"

#include "Commands/Command.hpp"
#include "Commands/Commands.hpp"
#include "Config/HotkeySystem.hpp"
#include "Rendering/GridItemButton.hpp"
#include "Rendering/GridItemHotkeyCapture.hpp"
#include "Rendering/GridItemText.hpp"
#include "Rendering/Theme.hpp"

#include <map>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	HotkeysGrid::HotkeysGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void HotkeysGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Press Enter on a row to capture a hotkey", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kItemH, "Press Enter again (or wait) to stop; Clear removes it", Theme::kText));

		// Same filter/sort as the original's own sortedCommands - every
		// registered command with an entry in m_CommandHotkeys (in
		// practice all of them - HotkeySystem::RegisterCommands() seeds
		// one for each up front), alphabetical by label, skipping an
		// empty one.
		std::map<std::string, CommandLink*> sortedCommands;
		for (auto& [hash, command] : Commands::GetCommands())
		{
			if (auto it = g_HotkeySystem.m_CommandHotkeys.find(hash); it != g_HotkeySystem.m_CommandHotkeys.end())
				if (!command->GetLabel().empty())
					sortedCommands.emplace(command->GetLabel(), &it->second);
		}

		for (auto& [label, link] : sortedCommands)
		{
			items_draft.push_back(std::make_unique<GridItemHotkeyCapture>(Theme::kContentWidth, kItemH, label, link));
			items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, kItemH, "Clear", [link] {
				link->m_Chain.clear();
				g_HotkeySystem.MarkStateDirty();
			}));
		}
	}
}
