#include "GridItemToggle.hpp"

#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr DirectX::XMFLOAT4 kOnColour{0.2f, 0.75f, 0.35f, 1.f};
		constexpr DirectX::XMFLOAT4 kOffColour{0.35f, 0.35f, 0.35f, 1.f};
		constexpr DirectX::XMFLOAT4 kLabelColour{1.f, 1.f, 1.f, 1.f};

		constexpr float kIndicatorSize = 16.f;
		constexpr float kLabelGap = 10.f;
	}

	void GridItemToggle::Draw()
	{
		// Clamped to 0: if the indicator were ever taller than m_Height
		// this would otherwise centre to a negative offset, drawing above
		// this item's own row into whatever's above it.
		const float indicatorY = m_Y + std::max(0.f, (m_Height - kIndicatorSize) * 0.5f);
		GridRenderer::DrawRect(m_X, indicatorY, kIndicatorSize, kIndicatorSize, m_State ? kOnColour : kOffColour);
	}

	void GridItemToggle::DrawText()
	{
		// Clamped to 0 - see the comment in Draw(): a label taller than
		// m_Height would otherwise centre upward out of this item's row.
		const float textY = m_Y + std::max(0.f, (m_Height - GridRenderer::MeasureText(m_Label.c_str()).y) * 0.5f);
		GridRenderer::DrawText(m_X + kIndicatorSize + kLabelGap, textY, m_Label.c_str(), kLabelColour);
	}

	void GridItemToggle::OnClick(float, float)
	{
		m_State = !m_State;
		LOGF(INFO, "[GridRenderer] Toggle '{}' clicked, now {}", m_Label, m_State ? "on" : "off");
	}
}
