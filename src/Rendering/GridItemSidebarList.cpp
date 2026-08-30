#include "GridItemSidebarList.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemSidebarList::Draw()
	{
		for (size_t i = 0; i < m_Entries.size(); ++i)
		{
			const float y = m_Y + m_EntryHeight * static_cast<float>(i);
			GridRenderer::DrawRect(
			    m_X,
			    y,
			    m_Width,
			    m_EntryHeight,
			    i == m_ActiveIndex ? Theme::kAccent : Theme::kPanelBackground);
		}
	}

	void GridItemSidebarList::DrawText()
	{
		for (size_t i = 0; i < m_Entries.size(); ++i)
		{
			const float y = m_Y + m_EntryHeight * static_cast<float>(i);
			const auto size = GridRenderer::MeasureText(m_Entries[i].c_str());
			// Clamped to 0 - see the identical comment in
			// GridItemToggle.cpp: otherwise a label taller than
			// m_EntryHeight centres upward out of this entry's own row.
			GridRenderer::DrawText(
			    m_X + 10.f,
			    y + std::max(0.f, (m_EntryHeight - size.y) * 0.5f),
			    m_Entries[i].c_str(),
			    Theme::kText);
		}
	}

	void GridItemSidebarList::OnClick(float, float cursorY)
	{
		const auto index = static_cast<size_t>((cursorY - m_Y) / m_EntryHeight);
		if (index < m_Entries.size())
		{
			m_ActiveIndex = index;
			LOGF(INFO, "[GridRenderer] Sidebar entry '{}' clicked", m_Entries[index]);
		}
	}
}
