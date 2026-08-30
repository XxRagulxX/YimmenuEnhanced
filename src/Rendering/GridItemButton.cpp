#include "GridItemButton.hpp"

#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		// A single accent colour standing in for Stand's real (theme-loaded,
		// not present in this snapshot) accent - see the note in
		// GridItemHeader.cpp. Swap this out once a real theme system exists.
		constexpr DirectX::XMFLOAT4 kBackground{0.16f, 0.42f, 0.83f, 0.9f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
	}

	void GridItemButton::Draw()
	{
		GridRenderer::DrawRect(m_X, m_Y, m_Width, m_Height, kBackground);
	}

	void GridItemButton::DrawText()
	{
		const auto size = GridRenderer::MeasureText(m_Label.c_str());
		// Clamped to 0: a label wider than m_Width would otherwise centre
		// to a negative offset, starting to the left of the button itself
		// (there's no text-wrapping yet, so an oversized label just
		// overflows the right edge instead once clamped - still readable,
		// unlike drifting off the left edge of the whole panel).
		const float textX = m_X + std::max(0.f, (m_Width - size.x) * 0.5f);
		const float textY = m_Y + std::max(0.f, (m_Height - size.y) * 0.5f);
		GridRenderer::DrawText(textX, textY, m_Label.c_str(), kText);
	}

	void GridItemButton::OnClick(float, float)
	{
		LOGF(INFO, "[GridRenderer] Button '{}' clicked", m_Label);

		if (m_Action)
			m_Action();
	}
}
