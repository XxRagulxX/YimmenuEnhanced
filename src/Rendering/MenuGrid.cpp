#include "MenuGrid.hpp"

#include "GridItemHeader.hpp"
#include "GridItemSidebarList.hpp"
#include "GridItemTabsHorizontal.hpp"
#include "GridRenderer.hpp"
#include "MiscGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kHeaderX = 20.f;
		constexpr float kHeaderY = 20.f;
		constexpr float kHeaderW = 440.f;
		constexpr float kHeaderH = 30.f;
		constexpr float kChromeGap = 8.f;

		constexpr float kSidebarX = kHeaderX;
		constexpr float kSidebarY = kHeaderY + kHeaderH + kChromeGap;
		constexpr float kSidebarW = 140.f;
		constexpr float kSidebarEntryH = 26.f;

		constexpr float kTabsX = kSidebarX + kSidebarW + kChromeGap;
		constexpr float kTabsY = kSidebarY;
		constexpr float kTabsH = 28.f;

		// MiscGrid.cpp's constructor must match these exactly (no shared
		// header for these yet - if a second content grid needs the same
		// position, that's worth factoring out then).
		constexpr float kContentX = kTabsX;
		constexpr float kContentY = kTabsY + kTabsH + kChromeGap;

		constexpr DirectX::XMFLOAT4 kPlaceholderColour{0.7f, 0.7f, 0.7f, 1.f};

		// The one real content grid this system has so far. Lives here
		// (not in GridRenderer.cpp) since MenuGrid is the only thing that
		// decides when it's actually shown.
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
		    kDebugIndex);
		sidebar->SetPosition(kSidebarX, kSidebarY, kSidebarW);
		m_Sidebar = sidebar.get();
		m_Items.push_back(std::move(sidebar));

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

		if (!IsDebugActive())
			return;

		m_DebugTabs->Draw();

		if (IsDebugMiscActive())
			g_MiscContent.Draw();
	}

	void MenuGrid::DrawText()
	{
		Grid::DrawText(); // chrome: header + sidebar labels

		if (!IsDebugActive())
		{
			GridRenderer::DrawText(kContentX, kContentY, "Not yet migrated.", kPlaceholderColour);
			return;
		}

		m_DebugTabs->DrawText();

		if (IsDebugMiscActive())
			g_MiscContent.DrawText();
		else
			GridRenderer::DrawText(kContentX, kContentY, "Not yet migrated.", kPlaceholderColour);
	}

	GridItem* MenuGrid::FindItemAt(float cursorX, float cursorY)
	{
		if (auto* item = Grid::FindItemAt(cursorX, cursorY))
			return item;

		if (!IsDebugActive())
			return nullptr;

		if (m_DebugTabs->Contains(cursorX, cursorY))
			return m_DebugTabs.get();

		if (IsDebugMiscActive())
			return g_MiscContent.FindItemAt(cursorX, cursorY);

		return nullptr;
	}
}
