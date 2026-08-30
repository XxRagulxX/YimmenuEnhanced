#include "RecoveryGrid.hpp"

#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"
#include "RecoveryBusinessesGrid.hpp"
#include "Theme.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		RecoveryBusinessesGrid g_BusinessesContent{};
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	RecoveryGrid::RecoveryGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void RecoveryGrid::Populate()
	{
		// General (MenuRecovery.cpp's generalGroup) - every unconditional
		// BoolCommandItem maps directly onto GridItemCommandToggle.
		// rpmultiplierinput is skipped: it's a ConditionalItem gated on
		// overriderpmultiplier, and this system has no float widget yet.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "General", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "playallmissionssolo"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "unlockgtaplus"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "overriderpmultiplier"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "freechangeappearance"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "nochangeappearancecooldown"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "allowgenderchange"_J));

		// Recovery's other categories (Businesses/Casino, plus
		// BuildHeistModifierMenu()/BuildDailyActivitiesMenu()/
		// BuildStatEditorMenu()/BuildTransactionsMenu()/
		// BuildUnlockerMenu()). Businesses now has its own content Grid;
		// the other six are still placeholder-only.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Categories", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Businesses", &g_BusinessesContent));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Heists", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Daily Activities", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Stat Editor", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Transactions", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Casino", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Unlocks", &GetPlaceholderGrid()));

		LOGF(INFO, "[GridRenderer] RecoveryGrid populated with {} items", m_Items.size());
	}
}
