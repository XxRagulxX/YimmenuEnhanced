#pragma once
#include "Grid.hpp"

#include <cstddef>
#include <memory>

namespace YimMenu::Rendering
{
	class GridItemSidebarList;
	class GridItemTabsHorizontal;

	// Top-level chrome: header + sidebar (submenu list) + (for the one
	// submenu that has one so far) a tab strip - real navigation, replacing
	// the earlier fixed panel where the tab strip was decorative-only.
	//
	// Only Debug > Misc has real content right now (MiscGrid, owned here).
	// Every other sidebar/tab selection draws a "not yet migrated"
	// placeholder instead of content that doesn't exist - nothing here
	// fakes pages that haven't actually been built.
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
		// Index into the sidebar's entry list corresponding to "Debug" -
		// the only submenu with a tab strip / real content right now.
		static constexpr size_t kDebugIndex = 8;
		// Index into m_DebugTabs' tab list corresponding to "Misc".
		static constexpr size_t kMiscTabIndex = 0;

		bool IsDebugActive() const;
		bool IsDebugMiscActive() const;

		GridItemSidebarList* m_Sidebar = nullptr;
		std::unique_ptr<GridItemTabsHorizontal> m_DebugTabs;
	};
}
