#include "GridItemToggle.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kIndicatorSize = 16.f;
		constexpr float kBorderWidth = 2.f;
		constexpr float kLabelGap = 10.f;
	}

	void GridItemToggle::draw()
	{
		// Full-row keyboard-focus highlight, drawn first so the checkbox
		// below layers on top of it - see GridItem.hpp's class comment
		// and MenuFocus.hpp for what this is.
		if (isKeyboardFocused())
			GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);

		// Clamped to 0: if the indicator were ever taller than height
		// this would otherwise centre to a negative offset, drawing above
		// this item's own row into whatever's above it.
		const float indicatorY = y + std::max(0.f, (height - kIndicatorSize) * 0.5f);

		// A real checkbox - a border, drawn full-size first, with the
		// actual on/off fill inset by kBorderWidth on top of it - rather
		// than a single flat-coloured square with nothing distinguishing
		// its edge from the row behind it.
		GridRenderer::DrawRect(x, indicatorY, kIndicatorSize, kIndicatorSize, Theme::kText);
		GridRenderer::DrawRect(x + kBorderWidth,
		    indicatorY + kBorderWidth,
		    kIndicatorSize - kBorderWidth * 2.f,
		    kIndicatorSize - kBorderWidth * 2.f,
		    m_State ? Theme::kAccent : Theme::kPanelBackground);
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
		activate();
	}

	void GridItemToggle::activate()
	{
		m_State = !m_State;
		LOGF(INFO, "[GridRenderer] Toggle '{}' toggled, now {}", m_Label, m_State ? "on" : "off");
	}
}
