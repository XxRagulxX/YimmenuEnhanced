#include "GridItemToggle.hpp"

#include "GridRenderer.hpp"

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
		const float indicatorY = m_Y + (m_Height - kIndicatorSize) * 0.5f;
		GridRenderer::DrawRect(m_X, indicatorY, kIndicatorSize, kIndicatorSize, m_State ? kOnColour : kOffColour);
	}

	void GridItemToggle::DrawText()
	{
		const float textY = m_Y + (m_Height - GridRenderer::MeasureText(m_Label.c_str()).y) * 0.5f;
		GridRenderer::DrawText(m_X + kIndicatorSize + kLabelGap, textY, m_Label.c_str(), kLabelColour);
	}
}
