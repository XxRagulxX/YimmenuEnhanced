#include "GridItemTabsHorizontal.hpp"

#include "GridRenderer.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr DirectX::XMFLOAT4 kActiveBackground{0.16f, 0.42f, 0.83f, 0.9f};
		constexpr DirectX::XMFLOAT4 kInactiveBackground{0.f, 0.f, 0.f, 0.4f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};

		constexpr float kTabPaddingX = 12.f;
		constexpr float kTabGap = 6.f;
	}

	void GridItemTabsHorizontal::Draw()
	{
		float x = m_X;
		for (size_t i = 0; i < m_Tabs.size(); ++i)
		{
			const float tabWidth = GridRenderer::MeasureText(m_Tabs[i].c_str()).x + kTabPaddingX * 2.f;
			GridRenderer::DrawRect(
			    x,
			    m_Y,
			    tabWidth,
			    m_Height,
			    i == m_ActiveIndex ? kActiveBackground : kInactiveBackground);
			x += tabWidth + kTabGap;
		}
	}

	void GridItemTabsHorizontal::DrawText()
	{
		float x = m_X;
		for (const auto& tab : m_Tabs)
		{
			const auto size = GridRenderer::MeasureText(tab.c_str());
			const float tabWidth = size.x + kTabPaddingX * 2.f;
			const float textY = m_Y + (m_Height - size.y) * 0.5f;
			GridRenderer::DrawText(x + kTabPaddingX, textY, tab.c_str(), kText);
			x += tabWidth + kTabGap;
		}
	}

	void GridItemTabsHorizontal::OnClick(float cursorX, float)
	{
		// Recompute the same per-tab segment boundaries Draw() lays out,
		// and find which one cursorX falls into.
		float x = m_X;
		for (size_t i = 0; i < m_Tabs.size(); ++i)
		{
			const float tabWidth = GridRenderer::MeasureText(m_Tabs[i].c_str()).x + kTabPaddingX * 2.f;
			if (cursorX >= x && cursorX < x + tabWidth)
			{
				m_ActiveIndex = i;
				LOGF(INFO, "[GridRenderer] Tab '{}' clicked", m_Tabs[i]);
				return;
			}
			x += tabWidth + kTabGap;
		}
	}
}
