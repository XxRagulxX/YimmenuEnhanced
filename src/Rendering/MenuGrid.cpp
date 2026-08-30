#include "MenuGrid.hpp"

#include "GridItemHeader.hpp"
#include "GridItemSidebarList.hpp"
#include "GridRenderer.hpp"
#include "MenuNavigation.hpp"
#include "MiscGrid.hpp"
#include "NetworkGrid.hpp"
#include "PlaceholderGrid.hpp"
#include "RecoveryGrid.hpp"
#include "SelfGrid.hpp"
#include "SettingsGrid.hpp"
#include "TeleportGrid.hpp"
#include "Theme.hpp"
#include "VehicleGrid.hpp"
#include "WorldGrid.hpp"

#include <utility>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr int16_t kHeaderX = 20;
		constexpr int16_t kHeaderY = 20;

		// Same spacer_size Stand's own MenuGrid uses (Grid(default_origin,
		// 3)) - the gap this Grid's own alignment engine (ported from
		// Stand's Grid::setPositions()) puts between header and sidebar,
		// since both are just items in this Grid's own list now.
		constexpr int16_t kSpacer = 3;

		// header's own x is kHeaderX (it's this Grid's first item, so the
		// alignment engine leaves it at origin); its width just needs to
		// reach from there to content's own right edge - see below.
		constexpr int16_t kHeaderW = Theme::kSidebarWidth + kSpacer + Theme::kContentWidth;

		// sidebar is the second item, ALIGN_BOTTOM_LEFT (the default) -
		// the alignment engine stacks it under header keeping header's
		// own x, so sidebar's x is also kHeaderX and doesn't need its own
		// constant. Its y does, since content (a separate Grid entirely -
		// see the class comment in MenuGrid.hpp) needs to sit level with
		// it, and nothing derives that for us across two different Grids.
		constexpr int16_t kContentY = kHeaderY + Theme::kHeaderHeight + kSpacer;
		constexpr int16_t kContentX = kHeaderX + Theme::kSidebarWidth + kSpacer;

		// Every content grid's own constructor hardcodes its origin to
		// (kContentX, kContentY) - (135, 47) as of writing - since none
		// of them are built via this file (no shared header for these
		// yet - if that stops scaling, it's worth factoring out then).

		// Indices into the sidebar's entry list.
		constexpr size_t kSelfIndex = 0;
		constexpr size_t kVehicleIndex = 1;
		constexpr size_t kTeleportIndex = 2;
		constexpr size_t kNetworkIndex = 3;
		constexpr size_t kPlayersIndex = 4;
		constexpr size_t kWorldIndex = 5;
		constexpr size_t kRecoveryIndex = 6;
		constexpr size_t kSettingsIndex = 7;
		constexpr size_t kDebugIndex = 8;

		// The only real content grids this system has so far. Live here
		// (not in GridRenderer.cpp) since MenuGrid is the only thing that
		// decides when any of them is actually shown.
		SelfGrid g_SelfContent{};
		VehicleGrid g_VehicleContent{};
		TeleportGrid g_TeleportContent{};
		NetworkGrid g_NetworkContent{};
		RecoveryGrid g_RecoveryContent{};
		WorldGrid g_WorldContent{};
		SettingsGrid g_SettingsContent{};
		MiscGrid g_MiscContent{};
	}

	MenuGrid::MenuGrid() :
	    Grid(kHeaderX, kHeaderY, kSpacer)
	{
	}

	MenuGrid::~MenuGrid() = default;

	void MenuGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		auto header = std::make_unique<GridItemHeader>(kHeaderW, Theme::kHeaderHeight, "YimMenu");
		m_Header = header.get();
		items_draft.push_back(std::move(header));

		// Defaults to Self, the flagship/first page - matches how the
		// real menu opens on Self by default. ALIGN_BOTTOM_LEFT (the
		// default) stacks this under header, keeping header's own x.
		auto sidebar = std::make_unique<GridItemSidebarList>(Theme::kSidebarWidth,
		    Theme::kSidebarEntryHeight,
		    std::vector<std::string>{
		        "Self",
		        "Vehicle",
		        "Teleport",
		        "Network",
		        "Players",
		        "World",
		        "Recovery",
		        "Settings",
		        "Debug"},
		    kSelfIndex);
		m_Sidebar = sidebar.get();
		items_draft.push_back(std::move(sidebar));

		// Every sidebar entry, real content or not - see the class
		// comment in MenuGrid.hpp for why there's no separate "nothing
		// migrated for this one" path any more.
		m_Roots = {
		    {kSelfIndex, "Self", &g_SelfContent},
		    {kVehicleIndex, "Vehicle", &g_VehicleContent},
		    {kTeleportIndex, "Teleport", &g_TeleportContent},
		    {kNetworkIndex, "Network", &g_NetworkContent},
		    {kPlayersIndex, "Players", &GetPlaceholderGrid()},
		    {kWorldIndex, "World", &g_WorldContent},
		    {kRecoveryIndex, "Recovery", &g_RecoveryContent},
		    {kSettingsIndex, "Settings", &g_SettingsContent},
		    {kDebugIndex, "Debug", &g_MiscContent},
		};

		LOGF(INFO, "[GridRenderer] MenuGrid populated with {} chrome items", items_draft.size());
	}

	void MenuGrid::SyncNavigation()
	{
		if (!m_Sidebar)
			return;

		const auto activeIndex = m_Sidebar->GetActiveIndex();
		if (activeIndex != m_LastSidebarIndex)
		{
			m_LastSidebarIndex = activeIndex;

			for (auto& root : m_Roots)
			{
				if (root.SidebarIndex == activeIndex)
				{
					MenuNavigation::Reset(root.Label, root.Content);
					break;
				}
			}
		}

		// Unconditional (not just on a sidebar change): a GridItemFolder
		// Push()/Backspace Pop() changes MenuNavigation's own path
		// without touching the sidebar at all, and still needs the
		// breadcrumb to catch up.
		if (m_Header)
			m_Header->SetTitle("YimMenu > " + MenuNavigation::BreadcrumbPath());
	}

	void MenuGrid::draw()
	{
		Grid::draw(); // chrome rects: header background + sidebar (also populates on first call)
		SyncNavigation();

		if (auto* content = MenuNavigation::Current())
			content->draw();
	}

	void MenuGrid::drawText()
	{
		// Chrome text: header (title already refreshed by this frame's
		// earlier draw() call - see GridRenderer::DrawImpl, which always
		// runs draw() before drawText() within the same frame) + sidebar
		// labels.
		Grid::drawText();

		if (auto* content = MenuNavigation::Current())
			content->drawText();
	}

	GridItem* MenuGrid::findItemAt(int16_t cursorX, int16_t cursorY)
	{
		if (auto* item = Grid::findItemAt(cursorX, cursorY)) // also populates on first call
			return item;

		SyncNavigation();

		if (auto* content = MenuNavigation::Current())
			return content->findItemAt(cursorX, cursorY);

		return nullptr;
	}
}
