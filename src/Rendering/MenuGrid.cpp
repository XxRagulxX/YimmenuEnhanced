#include "MenuGrid.hpp"

#include "GridItemHeader.hpp"
#include "GridItemSidebarList.hpp"
#include "GridItemTabsHorizontal.hpp"
#include "GridRenderer.hpp"
#include "MiscGrid.hpp"
#include "SelfGrid.hpp"
#include "VehicleGrid.hpp"

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

		constexpr float kTabsX = kSidebarX + kSidebarW + kChromeGap;
		constexpr float kTabsY = kSidebarY;
		constexpr float kTabsH = 28.f;

		// SelfGrid.cpp's/VehicleGrid.cpp's/MiscGrid.cpp's constructors
		// must match these exactly (no shared header for these yet - if
		// a fourth content grid needs the same position, that's worth
		// factoring out then).
		constexpr float kContentX = kTabsX;
		constexpr float kContentY = kTabsY + kTabsH + kChromeGap;

		constexpr DirectX::XMFLOAT4 kPlaceholderColour{0.7f, 0.7f, 0.7f, 1.f};

		// The only real content grids this system has so far. Live here
		// (not in GridRenderer.cpp) since MenuGrid is the only thing that
		// decides when any of them is actually shown.
		SelfGrid g_SelfContent{};
		VehicleGrid g_VehicleContent{};
		MiscGrid g_MiscContent{};
	}

	MenuGrid::MenuGrid() :
	    Grid(kHeaderX, kHeaderY, kHeaderW)
	{
	}

	MenuGrid::~MenuGrid() = default;

	MenuGrid::SubmenuEntry MenuGrid::MakeSubmenu(size_t sidebarIndex, std::vector<std::string> tabNames, std::vector<Grid*> tabContent)
	{
		auto tabs = std::make_unique<GridItemTabsHorizontal>(kTabsH, std::move(tabNames), 0);
		// GetTotalWidth() (not kTabsH/some fixed guess) so GridItem::Contains()
		// hit-tests exactly the region Draw() actually paints.
		tabs->SetPosition(kTabsX, kTabsY, tabs->GetTotalWidth());

		return SubmenuEntry{sidebarIndex, std::move(tabs), std::move(tabContent)};
	}

	void MenuGrid::Populate()
	{
		auto header = std::make_unique<GridItemHeader>(kHeaderH, "YimMenu (Stand-style)");
		header->SetPosition(kHeaderX, kHeaderY, kHeaderW);
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

		m_Submenus.push_back(MakeSubmenu(kSelfIndex, {"Main", "Weapons", "Outfit Editor"}, {&g_SelfContent, nullptr, nullptr}));
		m_Submenus.push_back(MakeSubmenu(kVehicleIndex, {"Main", "Spawn", "Edit", "Saved"}, {&g_VehicleContent, nullptr, nullptr, nullptr}));
		m_Submenus.push_back(MakeSubmenu(kDebugIndex, {"Misc", "Globals", "Locals", "Scripts"}, {&g_MiscContent, nullptr, nullptr, nullptr}));

		LOGF(INFO, "[GridRenderer] MenuGrid populated with {} chrome items", m_Items.size());
	}

	void MenuGrid::SetPositions()
	{
		// No-op: Populate() already gave every chrome item its exact
		// position - the default vertical-stack layout (same x/width for
		// every item) doesn't fit a header + narrower sidebar column.
	}

	MenuGrid::SubmenuEntry* MenuGrid::ActiveSubmenu()
	{
		if (!m_Sidebar)
			return nullptr;

		const auto activeIndex = m_Sidebar->GetActiveIndex();
		for (auto& submenu : m_Submenus)
		{
			if (submenu.SidebarIndex == activeIndex)
				return &submenu;
		}

		return nullptr;
	}

	Grid* MenuGrid::ActiveTabContent(SubmenuEntry& submenu)
	{
		const auto tabIndex = submenu.Tabs->GetActiveIndex();
		return tabIndex < submenu.TabContent.size() ? submenu.TabContent[tabIndex] : nullptr;
	}

	void MenuGrid::Draw()
	{
		Grid::Draw(); // chrome: header + sidebar

		if (auto* submenu = ActiveSubmenu())
		{
			submenu->Tabs->Draw();

			if (auto* content = ActiveTabContent(*submenu))
				content->Draw();
		}
	}

	void MenuGrid::DrawText()
	{
		Grid::DrawText(); // chrome: header + sidebar labels

		if (auto* submenu = ActiveSubmenu())
		{
			submenu->Tabs->DrawText();

			if (auto* content = ActiveTabContent(*submenu))
				content->DrawText();
			else
				GridRenderer::DrawText(kContentX, kContentY, "Not yet migrated.", kPlaceholderColour);
		}
		else
		{
			GridRenderer::DrawText(kContentX, kContentY, "Not yet migrated.", kPlaceholderColour);
		}
	}

	GridItem* MenuGrid::FindItemAt(float cursorX, float cursorY)
	{
		if (auto* item = Grid::FindItemAt(cursorX, cursorY))
			return item;

		auto* submenu = ActiveSubmenu();
		if (!submenu)
			return nullptr;

		if (submenu->Tabs->Contains(cursorX, cursorY))
			return submenu->Tabs.get();

		if (auto* content = ActiveTabContent(*submenu))
			return content->FindItemAt(cursorX, cursorY);

		return nullptr;
	}
}
