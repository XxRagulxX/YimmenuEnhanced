#pragma once
#include "Grid.hpp"
#include "GridItemScrollbar.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	class GridItemAddressbar;
	class GridItemTabsVertical;

	// Top-level chrome: a breadcrumb header + sidebar (submenu list) +
	// whatever content MenuNavigation currently has on top of its stack.
	//
	// Real navigation, replacing the earlier fixed panel where the
	// content area was decorative-only, and - as of this version - also
	// replacing an even earlier horizontal-tab-strip design for
	// switching between a submenu's categories. Stand's own menu has no
	// tab strip: a submenu's "Main" category IS the top-level list, and
	// every other category is just a GridItemFolder row within that same
	// list ("Spawner >", "Garage >", ...) that replaces the content in
	// place when clicked (MenuNavigation::Push()), poppable with
	// Backspace (MenuNavigation::Pop(), wired in GridRenderer.cpp).
	//
	// Every sidebar entry has a root Grid (m_Roots below) - real content
	// where it exists (SelfGrid, VehicleGrid, ..., NetworkGrid,
	// SettingsGrid), the shared PlaceholderGrid for anything not ported
	// yet (Players as of writing). There's no separate "nothing
	// selected" placeholder path any more: MenuNavigation::Current() is
	// always valid once populate() has run once.
	//
	// header/sidebar are just two GRIDITEM_PRIMARYTEXT/GRIDITEM_TABS
	// items in this Grid's own list now, positioned by the ported
	// alignment engine (sidebar's default ALIGN_BOTTOM_LEFT stacks it
	// under header, keeping header's own x) rather than hardcoded
	// SetPosition() calls - see populate().
	class MenuGrid : public Grid
	{
	public:
		MenuGrid();
		~MenuGrid() override;

		void draw() override;
		void drawText() override;
		GridItem* findItemAt(int16_t cursorX, int16_t cursorY) override;

		// All keyboard navigation lives here rather than split across
		// GridRenderer/GridItemTabsVertical/MenuFocus - see MenuFocus.hpp
		// for the model (one of Sidebar/Content has focus at a time) and
		// GridItem.hpp for why isFocusable()/activate()/onArrow() exist.
		// vkCode is a plain Win32 virtual-key code (VK_UP, VK_RETURN,
		// ...) - taken as an unsigned rather than WPARAM so this header
		// doesn't need <windows.h>; GridRenderer::WndProcImpl (which
		// already includes it for WM_KEYDOWN itself) casts wparam before
		// calling this.
		void HandleKey(unsigned int vkCode);

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;

	private:
		struct SubmenuRoot
		{
			size_t SidebarIndex;
			std::string Label; // breadcrumb root label, e.g. "Vehicle"
			Grid* Content;     // non-owning - see the class comment above
		};

		// Resets MenuNavigation to the sidebar's currently active entry's
		// root, but only when that selection actually changed since the
		// last call - cheap to call every frame (draw()/drawText()/
		// findItemAt() all do), and idempotent otherwise.
		void SyncNavigation();

		GridItemAddressbar* m_Header = nullptr;
		GridItemTabsVertical* m_Sidebar = nullptr;
		GridItemScrollbar m_ContentScrollbar;
		std::vector<SubmenuRoot> m_Roots;
		size_t m_LastSidebarIndex = static_cast<size_t>(-1);
	};
}
