#include "SettingsGrid.hpp"

#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "PlaceholderGrid.hpp"
#include "SettingsGuiGrid.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		SettingsGuiGrid g_GuiContent{};
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	SettingsGrid::SettingsGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void SettingsGrid::Populate()
	{
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Categories", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Hotkeys", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "GUI", &g_GuiContent));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Game", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Customize", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Lua Scripts", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] SettingsGrid populated with {} items", m_Items.size());
	}
}
