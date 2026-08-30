#pragma once
#include "Grid.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	class GridItemSidebarList;
	class GridItemTabsHorizontal;

	// Top-level chrome: header + sidebar (submenu list) + (for submenus
	// that have one) a tab strip - real navigation, replacing the earlier
	// fixed panel where the tab strip was decorative-only.
	//
	// Which sidebar entries have a tab strip + real content is
	// data-driven (m_Submenus) rather than per-submenu if/else branches -
	// the refactor the previous (two-submenu) version of this file
	// deferred "until a third needs its own tab strip", now that
	// VehicleGrid is that third. A sidebar entry with no matching
	// m_Submenus entry (Teleport, Network, Players, World, Recovery,
	// Settings as of writing) just draws the "not yet migrated"
	// placeholder with no tab strip at all, same as before this refactor.
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
		static constexpr size_t kVehicleIndex = 1;
		static constexpr size_t kTeleportIndex = 2;
		static constexpr size_t kWorldIndex = 5;
		static constexpr size_t kRecoveryIndex = 6;
		static constexpr size_t kDebugIndex = 8;

		// One sidebar entry that has its own tab strip. Tabs owns the
		// strip; TabContent is parallel to Tabs' own entries and
		// non-owning (the actual Grids are file-scope statics in
		// MenuGrid.cpp, same lifetime/ownership as before this refactor)
		// - nullptr means that particular tab has no content yet, so
		// DrawText() falls back to the "not yet migrated" placeholder.
		struct SubmenuEntry
		{
			size_t SidebarIndex;
			std::unique_ptr<GridItemTabsHorizontal> Tabs;
			std::vector<Grid*> TabContent;
		};

		static SubmenuEntry MakeSubmenu(size_t sidebarIndex, std::vector<std::string> tabNames, std::vector<Grid*> tabContent);

		// Returns the SubmenuEntry matching the sidebar's current
		// selection, or nullptr if the active sidebar entry has no tab
		// strip of its own.
		SubmenuEntry* ActiveSubmenu();
		static Grid* ActiveTabContent(SubmenuEntry& submenu);

		GridItemSidebarList* m_Sidebar = nullptr;
		std::vector<SubmenuEntry> m_Submenus;
	};
}
