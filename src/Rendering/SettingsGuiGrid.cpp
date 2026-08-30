#include "SettingsGuiGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	SettingsGuiGrid::SettingsGuiGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void SettingsGuiGrid::Populate()
	{
		// General - unloadmenu is added directly to MenuSettings.cpp's
		// gui Category with no wrapping Group of its own.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "General", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "unloadmenu"_J));

		// UI (uiStyle) - styleselector is an unconditional ListCommandItem,
		// now that GridItemCommandList exists.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "UI", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "styleselector"_J));

		// Overlay - only the one unconditional toggle; overlayfps/
		// overlaypos/overlaylock are all ConditionalItems gated on it,
		// skipped like every other ConditionalItem here.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Overlay", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "overlay"_J));

		// Chat - clearchat is a plain CommandItem button.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Chat", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "clearchat"_J));

		LOGF(INFO, "[GridRenderer] SettingsGuiGrid populated with {} items", m_Items.size());
	}
}
