#include "Rendering/MenuGrid.hpp"

#include "Rendering/GridItemAddressbar.hpp"
#include "Rendering/GridItemTabsVertical.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/MenuFocus.hpp"
#include "Rendering/MenuNavigation.hpp"
#include "Rendering/MiscGrid.hpp"
#include "Rendering/NetworkGrid.hpp"
#include "Rendering/PlayersGrid.hpp"
#include "Rendering/RecoveryGrid.hpp"
#include "Rendering/SelfGrid.hpp"
#include "Rendering/SettingsGrid.hpp"
#include "Rendering/TeleportGrid.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/VehicleGrid.hpp"
#include "Rendering/WorldGrid.hpp"

#include <utility>
#include <windows.h>

namespace YimMenu::Rendering
{
	namespace
	{
		// Stand's own real default_origin (src/Menu/MenuGrid.hpp's
		// MenuGrid::default_origin, { 1323, 560 }), not an arbitrary
		// top-left placement - Stand's menu opens on the right side of
		// the screen, roughly vertically centred, and this was wrongly
		// placed at (20, 20) (top-left) before. Both this and every
		// Theme.hpp geometry constant are H-space coordinates (Stand's
		// own virtual 1920x1080 canvas - see GridRenderer::PosH2C/
		// SizeH2C for how that's mapped onto the real screen
		// resolution), not literal screen pixels.
		constexpr int16_t kHeaderX = 1323;
		constexpr int16_t kHeaderY = 560;

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
		// (kContentX, kContentY) - (1438, 587) as of writing - since none
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
		PlayersGrid g_PlayersContent{};
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
		auto header = std::make_unique<GridItemAddressbar>(kHeaderW, Theme::kHeaderHeight, "YimMenu");
		m_Header = header.get();
		items_draft.push_back(std::move(header));

		// Defaults to Self, the flagship/first page - matches how the
		// real menu opens on Self by default. ALIGN_BOTTOM_LEFT (the
		// default) stacks this under header, keeping header's own x.
		auto sidebar = std::make_unique<GridItemTabsVertical>(Theme::kSidebarWidth,
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
		    {kPlayersIndex, "Players", &g_PlayersContent},
		    {kWorldIndex, "World", &g_WorldContent},
		    {kRecoveryIndex, "Recovery", &g_RecoveryContent},
		    {kSettingsIndex, "Settings", &g_SettingsContent},
		    {kDebugIndex, "Debug", &g_MiscContent},
		};
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
		{
			content->draw();

			m_ContentScrollbar.SetView(content);
			m_ContentScrollbar.x = static_cast<int16_t>(content->origin.x + Theme::kContentWidth + Theme::kScrollbarGap);
			m_ContentScrollbar.y = content->origin.y;
			m_ContentScrollbar.width = Theme::kScrollbarWidth;
			m_ContentScrollbar.height = static_cast<int16_t>(Theme::kHudHeight - content->origin.y - Theme::kContentBottomMargin);
			m_ContentScrollbar.draw();
		}
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

	void MenuGrid::HandleKey(unsigned int vkCode)
	{
		// Keeps m_Sidebar/MenuNavigation::Current() in sync before we
		// read either below - same call draw()/findItemAt() already
		// make every frame, safe (and cheap) to call again here too.
		SyncNavigation();

		switch (vkCode)
		{
		case VK_BACK:
		case VK_NUMPAD0:
			// Same "go back" gesture as before this method existed -
			// moved here (from GridRenderer::WndProcImpl directly) so
			// every key this system handles lives in one place. Content
			// focus doesn't need resetting explicitly: MenuFocus detects
			// MenuNavigation::Current() changing underneath it on its
			// own - see MenuFocus.hpp's class comment.
			MenuNavigation::Pop();
			break;

		case VK_UP:
		case VK_NUMPAD8:
		case VK_DOWN:
		case VK_NUMPAD2:
		{
			// Real Stand feel: Up/Down only ever drive the currently-shown
			// submenu's own item list, never the main menu (sidebar) - see
			// VK_CONTROL/VK_SHIFT below for that. Also claims Content focus
			// outright, same as SetFocusedItem() already does for a mouse
			// move/click, so a follow-up Enter activates the item just
			// moved to instead of needing a separate "enter Content" press
			// first.
			if (auto* content = MenuNavigation::Current())
			{
				const int delta = (vkCode == VK_DOWN || vkCode == VK_NUMPAD2) ? 1 : -1;
				MenuFocus::MoveContent(content, delta);
				MenuFocus::SetRegion(MenuFocus::Region::Content);
			}
			break;
		}

		case VK_CONTROL:
		case VK_SHIFT:
			// Real Stand feel: the main menu (sidebar) isn't Up/Down-driven -
			// Left Ctrl moves it down, Left Shift moves it up, from
			// anywhere (not just while focus is already on the sidebar),
			// same as Stand's own scheme. WM_KEYDOWN reports the generic
			// VK_CONTROL/VK_SHIFT for either side, so GetKeyState() (not
			// vkCode) is what tells Left apart from Right here - same
			// pattern GUI::WndProc already uses for its own modifier
			// checks.
			if (m_Sidebar)
			{
				if (vkCode == VK_CONTROL && (GetKeyState(VK_LCONTROL) & 0x8000) != 0)
					m_Sidebar->MoveActive(1);
				else if (vkCode == VK_SHIFT && (GetKeyState(VK_LSHIFT) & 0x8000) != 0)
					m_Sidebar->MoveActive(-1);
			}
			break;

		case VK_LEFT:
		case VK_NUMPAD4:
			// Unhandled (nothing focused, or the focused item has no
			// directly-adjustable value - see GridItem::onArrow()) falls
			// back to moving focus back to the sidebar, the same
			// direction Left points visually (sidebar sits to Content's
			// left).
			if (MenuFocus::GetRegion() == MenuFocus::Region::Content)
			{
				auto* focused = MenuNavigation::Current() ? MenuFocus::GetFocusedItem(MenuNavigation::Current()) : nullptr;
				if (!focused || !focused->onArrow(-1))
					MenuFocus::SetRegion(MenuFocus::Region::Sidebar);
			}
			break;

		case VK_RIGHT:
		case VK_NUMPAD6:
			if (MenuFocus::GetRegion() == MenuFocus::Region::Sidebar)
			{
				MenuFocus::SetRegion(MenuFocus::Region::Content);
			}
			else if (auto* content = MenuNavigation::Current())
			{
				if (auto* focused = MenuFocus::GetFocusedItem(content))
					focused->onArrow(1);
			}
			break;

		case VK_RETURN:
		case VK_NUMPAD5:
			if (MenuFocus::GetRegion() == MenuFocus::Region::Sidebar)
			{
				// Selecting a sidebar entry (Ctrl/Shift - see above) already
				// switches content live, same as Stand's own tab strip;
				// Enter here just moves focus into what's already showing.
				MenuFocus::SetRegion(MenuFocus::Region::Content);
			}
			else if (auto* content = MenuNavigation::Current())
			{
				if (auto* focused = MenuFocus::GetFocusedItem(content))
					focused->activate();
			}
			break;

		default:
			break;
		}

		// Whatever just happened above (a focus move, a page switch, a
		// Backspace pop, ...) may have left keyboard focus on a row
		// that's scrolled out of view - bring it back into view rather
		// than leaving focus on something invisible. Harmless/idempotent
		// otherwise (an already-visible focused item, or no content at
		// all). See Grid::ScrollToShow()'s own doc comment in Grid.hpp.
		if (auto* content = MenuNavigation::Current())
		{
			const auto visibleHeight = static_cast<int16_t>(Theme::kHudHeight - content->origin.y - Theme::kContentBottomMargin);
			content->ScrollToShow(MenuFocus::GetFocusedItem(content), visibleHeight);
		}
	}
}
