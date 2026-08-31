#include "GridItemTabsVertical.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemTabsVertical::draw()
	{
		for (size_t i = 0; i < m_Entries.size(); ++i)
		{
			const float rowY = y + m_EntryHeight * static_cast<float>(i);
			GridRenderer::DrawRect(
			    x,
			    rowY,
			    width,
			    m_EntryHeight,
			    i == m_ActiveIndex ? Theme::kAccent : Theme::kPanelBackground);
		}
	}

	void GridItemTabsVertical::drawText()
	{
		for (size_t i = 0; i < m_Entries.size(); ++i)
		{
			const float rowY = y + m_EntryHeight * static_cast<float>(i);
			const auto size = GridRenderer::MeasureText(m_Entries[i].c_str());
			GridRenderer::DrawText(
			    x + 5.f,
			    rowY + std::max(0.f, (m_EntryHeight - size.y) * 0.5f),
			    m_Entries[i].c_str(),
			    Theme::kText);
		}
	}

	void GridItemTabsVertical::onClick(int16_t, int16_t cursorY)
	{
		const auto index = static_cast<size_t>((cursorY - y) / m_EntryHeight);
		if (index < m_Entries.size())
		{
			m_ActiveIndex = index;
			LOGF(INFO, "[GridRenderer] Sidebar entry '{}' clicked", m_Entries[index]);
		}
	}

	void GridItemTabsVertical::MoveActive(int delta)
	{
		if (m_Entries.empty())
			return;

		const auto count = static_cast<int>(m_Entries.size());
		const auto clamped = std::clamp(static_cast<int>(m_ActiveIndex) + delta, 0, count - 1);
		m_ActiveIndex = static_cast<size_t>(clamped);
	}
}
