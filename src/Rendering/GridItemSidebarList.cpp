#include "GridItemSidebarList.hpp"

#include "GridRenderer.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr DirectX::XMFLOAT4 kActiveBackground{0.16f, 0.42f, 0.83f, 0.9f};
		constexpr DirectX::XMFLOAT4 kInactiveBackground{0.f, 0.f, 0.f, 0.4f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
	}

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
			    i == m_ActiveIndex ? kActiveBackground : kInactiveBackground);
		}
	}

	void GridItemSidebarList::DrawText()
	{
		for (size_t i = 0; i < m_Entries.size(); ++i)
		{
			const float y = m_Y + m_EntryHeight * static_cast<float>(i);
			const auto size = GridRenderer::MeasureText(m_Entries[i].c_str());
			GridRenderer::DrawText(m_X + 10.f, y + (m_EntryHeight - size.y) * 0.5f, m_Entries[i].c_str(), kText);
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
