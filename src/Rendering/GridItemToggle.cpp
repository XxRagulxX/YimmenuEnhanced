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

	void GridItemToggle::draw()
	{
		// Clamped to 0: if the indicator were ever taller than height
		// this would otherwise centre to a negative offset, drawing above
		// this item's own row into whatever's above it.
		const float indicatorY = y + std::max(0.f, (height - kIndicatorSize) * 0.5f);
		GridRenderer::DrawRect(x, indicatorY, kIndicatorSize, kIndicatorSize, m_State ? Theme::kAccent : Theme::kToggleOff);
	}

	void GridItemToggle::drawText()
	{
		// Clamped to 0 - see the comment in draw(): a label taller than
		// height would otherwise centre upward out of this item's row.
		const float textY = y + std::max(0.f, (height - GridRenderer::MeasureText(m_Label.c_str()).y) * 0.5f);
		GridRenderer::DrawText(x + kIndicatorSize + kLabelGap, textY, m_Label.c_str(), Theme::kText);
	}

	void GridItemToggle::onClick(int16_t, int16_t)
	{
		m_State = !m_State;
		LOGF(INFO, "[GridRenderer] Toggle '{}' clicked, now {}", m_Label, m_State ? "on" : "off");
	}
}
