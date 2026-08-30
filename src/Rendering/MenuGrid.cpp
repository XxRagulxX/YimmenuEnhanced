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
#include "VehicleGrid.hpp"
#include "WorldGrid.hpp"

#include <utility>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kHeaderX = 20.f;
		constexpr float kHeaderY = 20.f;
		// Must reach at least kContentX + the content grids' own width
		// below (300 as of writing) - a real command label (e.g. "Skip
		// Conversation") can be wider than expected, and there's no
		// text-wrapping yet, so this needs real margin rather than an
		// exact fit.
		constexpr float kHeaderW = 460.f;
		constexpr float kHeaderH = 30.f;
		constexpr float kChromeGap = 8.f;

		constexpr float kSidebarX = kHeaderX;
		constexpr float kSidebarY = kHeaderY + kHeaderH + kChromeGap;
		constexpr float kSidebarW = 140.f;
		constexpr float kSidebarEntryH = 26.f;

		// Every content grid's own constructor hardcodes its position to
		// (kSidebarX + kSidebarW + kChromeGap, kSidebarY) - (168, 58) as
		// of writing - since none of them are built via this file (no
		// shared header for these yet - if that stops scaling, it's
		// worth factoring out then). Content sits level with the
		// sidebar, right under the header: there's no tab row to leave
		// room for any more (see MenuGrid.hpp's class comment).

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
	    Grid(kHeaderX, kHeaderY, kHeaderW)
	{
	}

	MenuGrid::~MenuGrid() = default;

	void MenuGrid::Populate()
	{
		auto header = std::make_unique<GridItemHeader>(kHeaderH, "YimMenu");
		header->SetPosition(kHeaderX, kHeaderY, kHeaderW);
		m_Header = header.get();
		m_Items.push_back(std::move(header));

		// Defaults to Self, the flagship/first page - matches how the
		// real menu opens on Self by default.
		auto sidebar = std::make_unique<GridItemSidebarList>(kSidebarEntryH,
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
		sidebar->SetPosition(kSidebarX, kSidebarY, kSidebarW);
		m_Sidebar = sidebar.get();
		m_Items.push_back(std::move(sidebar));

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

		LOGF(INFO, "[GridRenderer] MenuGrid populated with {} chrome items", m_Items.size());
	}

	void MenuGrid::SetPositions()
	{
		// No-op: Populate() already gave every chrome item its exact
		// position - the default vertical-stack layout (same x/width for
		// every item) doesn't fit a header + narrower sidebar column.
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

	void MenuGrid::Draw()
	{
		Grid::Draw(); // chrome rects: header background + sidebar (also populates on first call)
		SyncNavigation();

		if (auto* content = MenuNavigation::Current())
			content->Draw();
	}

	void MenuGrid::DrawText()
	{
		// Chrome text: header (title already refreshed by this frame's
		// earlier Draw() call - see GridRenderer::DrawImpl, which always
		// runs Draw() before DrawText() within the same frame) + sidebar
		// labels.
		Grid::DrawText();

		if (auto* content = MenuNavigation::Current())
			content->DrawText();
	}

	GridItem* MenuGrid::FindItemAt(float cursorX, float cursorY)
	{
		if (auto* item = Grid::FindItemAt(cursorX, cursorY)) // also populates on first call
			return item;

		SyncNavigation();

		if (auto* content = MenuNavigation::Current())
			return content->FindItemAt(cursorX, cursorY);

		return nullptr;
	}
}
