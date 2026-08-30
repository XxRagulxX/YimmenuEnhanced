#include "MenuGrid.hpp"

#include "GridItemHeader.hpp"
#include "GridItemSidebarList.hpp"
#include "GridItemTabsHorizontal.hpp"
#include "GridRenderer.hpp"
#include "MiscGrid.hpp"
#include "SelfGrid.hpp"

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

		// SelfGrid.cpp's/MiscGrid.cpp's constructors must match these
		// exactly (no shared header for these yet - if a third content
		// grid needs the same position, that's worth factoring out then).
		constexpr float kContentX = kTabsX;
		constexpr float kContentY = kTabsY + kTabsH + kChromeGap;

		constexpr DirectX::XMFLOAT4 kPlaceholderColour{0.7f, 0.7f, 0.7f, 1.f};

		// The only real content grids this system has so far. Live here
		// (not in GridRenderer.cpp) since MenuGrid is the only thing that
		// decides when either is actually shown.
		SelfGrid g_SelfContent{};
		MiscGrid g_MiscContent{};
	}

	MenuGrid::MenuGrid() :
	    Grid(kHeaderX, kHeaderY, kHeaderW)
	{
	}

	MenuGrid::~MenuGrid() = default;

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

		m_SelfTabs = std::make_unique<GridItemTabsHorizontal>(
		    kTabsH,
		    std::vector<std::string>{"Main", "Weapons", "Outfit Editor"},
		    kSelfMainTabIndex);
		m_SelfTabs->SetPosition(kTabsX, kTabsY, m_SelfTabs->GetTotalWidth());

		m_DebugTabs = std::make_unique<GridItemTabsHorizontal>(
		    kTabsH,
		    std::vector<std::string>{"Misc", "Globals", "Locals", "Scripts"},
		    kMiscTabIndex);
		// GetTotalWidth() (not kTabsH/some fixed guess) so GridItem::Contains()
		// hit-tests exactly the region Draw() actually paints.
		m_DebugTabs->SetPosition(kTabsX, kTabsY, m_DebugTabs->GetTotalWidth());

		LOGF(INFO, "[GridRenderer] MenuGrid populated with {} chrome items", m_Items.size());
	}

	void MenuGrid::SetPositions()
	{
		// No-op: Populate() already gave every chrome item its exact
		// position - the default vertical-stack layout (same x/width for
		// every item) doesn't fit a header + narrower sidebar column.
	}

	bool MenuGrid::IsSelfActive() const
	{
		return m_Sidebar && m_Sidebar->GetActiveIndex() == kSelfIndex;
	}

	bool MenuGrid::IsSelfMainActive() const
	{
		return IsSelfActive() && m_SelfTabs && m_SelfTabs->GetActiveIndex() == kSelfMainTabIndex;
	}

	bool MenuGrid::IsDebugActive() const
	{
		return m_Sidebar && m_Sidebar->GetActiveIndex() == kDebugIndex;
	}

	bool MenuGrid::IsDebugMiscActive() const
	{
		return IsDebugActive() && m_DebugTabs && m_DebugTabs->GetActiveIndex() == kMiscTabIndex;
	}

	void MenuGrid::Draw()
	{
		Grid::Draw(); // chrome: header + sidebar

		if (IsSelfActive())
		{
			m_SelfTabs->Draw();

			if (IsSelfMainActive())
				g_SelfContent.Draw();
		}
		else if (IsDebugActive())
		{
			m_DebugTabs->Draw();

			if (IsDebugMiscActive())
				g_MiscContent.Draw();
		}
	}

	void MenuGrid::DrawText()
	{
		Grid::DrawText(); // chrome: header + sidebar labels

		if (IsSelfActive())
		{
			m_SelfTabs->DrawText();

			if (IsSelfMainActive())
				g_SelfContent.DrawText();
			else
				GridRenderer::DrawText(kContentX, kContentY, "Not yet migrated.", kPlaceholderColour);
		}
		else if (IsDebugActive())
		{
			m_DebugTabs->DrawText();

			if (IsDebugMiscActive())
				g_MiscContent.DrawText();
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

		if (IsSelfActive())
		{
			if (m_SelfTabs->Contains(cursorX, cursorY))
				return m_SelfTabs.get();

			if (IsSelfMainActive())
				return g_SelfContent.FindItemAt(cursorX, cursorY);

			return nullptr;
		}

		if (IsDebugActive())
		{
			if (m_DebugTabs->Contains(cursorX, cursorY))
				return m_DebugTabs.get();

			if (IsDebugMiscActive())
				return g_MiscContent.FindItemAt(cursorX, cursorY);

			return nullptr;
		}

		return nullptr;
	}
}
