#include "SettingsGrid.hpp"

#include "GridItemFolder.hpp"
#include "GridItemHeader.hpp"
#include "PlaceholderGrid.hpp"
#include "SettingsGuiGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = 26.f;
		constexpr float kItemH = 28.f;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		SettingsGuiGrid g_GuiContent{};
	}

	// Position matches every other content Grid's (168, 58) - see the
	// comment in MenuGrid.cpp's anonymous namespace for why (no shared
	// header for these yet).
	SettingsGrid::SettingsGrid() :
	    Grid(168.f, 58.f, 300.f)
	{
	}

	void SettingsGrid::Populate()
	{
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Categories"));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Hotkeys", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "GUI", &g_GuiContent));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Game", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Customize", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Lua Scripts", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] SettingsGrid populated with {} items", m_Items.size());
	}
}
