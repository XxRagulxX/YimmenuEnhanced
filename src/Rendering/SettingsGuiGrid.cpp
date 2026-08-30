#include "SettingsGuiGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemHeader.hpp"
#include "Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = 26.f;
		constexpr float kItemH = 28.f;
	}

	// Position matches every other content Grid's (168, 58) - see the
	// comment in MenuGrid.cpp's anonymous namespace for why (no shared
	// header for these yet).
	SettingsGuiGrid::SettingsGuiGrid() :
	    Grid(168.f, 58.f, 300.f)
	{
	}

	void SettingsGuiGrid::Populate()
	{
		// General - unloadmenu is added directly to MenuSettings.cpp's
		// gui Category with no wrapping Group of its own.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "General"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "unloadmenu"_J));

		// UI (uiStyle) - styleselector is an unconditional ListCommandItem,
		// now that GridItemCommandList exists.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "UI"));
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "styleselector"_J));

		// Overlay - only the one unconditional toggle; overlayfps/
		// overlaypos/overlaylock are all ConditionalItems gated on it,
		// skipped like every other ConditionalItem here.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Overlay"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "overlay"_J));

		// Chat - clearchat is a plain CommandItem button.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "Chat"));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "clearchat"_J));

		LOGF(INFO, "[GridRenderer] SettingsGuiGrid populated with {} items", m_Items.size());
	}
}
