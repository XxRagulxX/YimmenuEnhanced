#pragma once
#include "Grid.hpp"

#include <cstddef>
#include <memory>

namespace YimMenu::Rendering
{
	class GridItemSidebarList;
	class GridItemTabsHorizontal;

	// Top-level chrome: header + sidebar (submenu list) + (for submenus
	// that have one) a tab strip - real navigation, replacing the earlier
	// fixed panel where the tab strip was decorative-only.
	//
	// Only Self > Main (SelfGrid) and Debug > Misc (MiscGrid) have real
	// content right now, both owned here. Every other sidebar/tab
	// selection draws a "not yet migrated" placeholder instead of content
	// that doesn't exist - nothing here fakes pages that haven't actually
	// been built.
	//
	// The Self/Debug handling below is duplicated per-submenu rather than
	// data-driven (a table of {sidebar index, tabs, content grids}) -
	// fine at two submenus, worth refactoring once a third needs its own
	// tab strip.
	class MenuGrid : public Grid
	{
	public:
		MenuGrid();
		~MenuGrid() override;

		void Draw() override;
		void DrawText() override;
		GridItem* FindItemAt(float cursorX, float cursorY) override;

	protected:
		void Populate() override;
		void SetPositions() override; // no-op: Populate() positions everything itself

	private:
		// Indices into the sidebar's entry list.
		static constexpr size_t kSelfIndex = 0;
		static constexpr size_t kDebugIndex = 8;
		// Indices into m_SelfTabs'/m_DebugTabs' own tab lists.
		static constexpr size_t kSelfMainTabIndex = 0;
		static constexpr size_t kMiscTabIndex = 0;

		bool IsSelfActive() const;
		bool IsSelfMainActive() const;
		bool IsDebugActive() const;
		bool IsDebugMiscActive() const;

		GridItemSidebarList* m_Sidebar = nullptr;
		std::unique_ptr<GridItemTabsHorizontal> m_SelfTabs;
		std::unique_ptr<GridItemTabsHorizontal> m_DebugTabs;
	};
}
