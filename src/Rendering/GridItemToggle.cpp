#include "GridItemToggle.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kIndicatorSize = 16.f;
		constexpr float kLabelGap = 10.f;
	}

	void GridItemToggle::Draw()
	{
		// Clamped to 0: if the indicator were ever taller than m_Height
		// this would otherwise centre to a negative offset, drawing above
		// this item's own row into whatever's above it.
		const float indicatorY = m_Y + std::max(0.f, (m_Height - kIndicatorSize) * 0.5f);
		GridRenderer::DrawRect(m_X, indicatorY, kIndicatorSize, kIndicatorSize, m_State ? Theme::kAccent : Theme::kToggleOff);
	}

	void GridItemToggle::DrawText()
	{
		// Clamped to 0 - see the comment in Draw(): a label taller than
		// m_Height would otherwise centre upward out of this item's row.
		const float textY = m_Y + std::max(0.f, (m_Height - GridRenderer::MeasureText(m_Label.c_str()).y) * 0.5f);
		GridRenderer::DrawText(m_X + kIndicatorSize + kLabelGap, textY, m_Label.c_str(), Theme::kText);
	}

	void GridItemToggle::OnClick(float, float)
	{
		m_State = !m_State;
		LOGF(INFO, "[GridRenderer] Toggle '{}' clicked, now {}", m_Label, m_State ? "on" : "off");
	}
}
