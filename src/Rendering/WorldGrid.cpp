#include "WorldGrid.hpp"

#include "GridItemCommandButton.hpp"
#include "GridItemCommandList.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemFolder.hpp"
#include "GridItemText.hpp"
#include "Joaat.hpp"
#include "PlaceholderGrid.hpp"
#include "Theme.hpp"
#include "WorldIPLsGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid.
		WorldIPLsGrid g_IPLsContent{};
	}

	// Position matches every other content Grid's (140, 52) via Theme's
	// layout constants - see the comment in MenuGrid.cpp's anonymous
	// namespace for why (no shared header for these yet).
	WorldGrid::WorldGrid() :
	    Grid(140.f, 52.f, Theme::kContentWidth)
	{
	}

	void WorldGrid::Populate()
	{
		// Kill (killPeds) - both plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Kill", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "killallpeds"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "killallenemies"_J));

		// Delete (deleteOpts) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Delete", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delpeds"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delvehs"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delobjs"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "delcams"_J));

		// Bring (bringOpts) - all plain CommandItem buttons.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Bring", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "bringpeds"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "bringvehs"_J));
		m_Items.push_back(std::make_unique<GridItemCommandButton>(kItemH, "bringobjs"_J));

		// Weather (weatherOpts) - weather is an unconditional
		// ListCommandItem, now that GridItemCommandList exists; so is
		// forceweather's own toggle. setweather is still skipped: it's a
		// ConditionalItem only shown while forceweather is off, and this
		// system has no conditional-visibility widget yet.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Weather", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandList>(kItemH, "weather"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "forceweather"_J));

		// Other (otherOpts) - every item here is an unconditional
		// BoolCommandItem in the original, so all five map directly onto
		// GridItemCommandToggle.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Other", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "pedsignore"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "PedRiotMode"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "CopsDispatch"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "enablecreatordevmode"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "infiniteboundary"_J));

		// World's other categories (BuildSpawnPedMenu(), the IPLs
		// Category). IPLs now has its own content Grid; Spawn Ped is
		// still placeholder-only.
		m_Items.push_back(std::make_unique<GridItemText>(kSectionHeaderH, "Categories", Theme::kText));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "Spawn Ped", &GetPlaceholderGrid()));
		m_Items.push_back(std::make_unique<GridItemFolder>(kItemH, "IPLs", &g_IPLsContent));

		LOGF(INFO, "[GridRenderer] WorldGrid populated with {} items", m_Items.size());
	}
}
