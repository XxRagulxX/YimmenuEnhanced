#include "GridItemButton.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemButton::draw()
	{
		// Theme::kAccent only while keyboard-focused, Theme::kPanelBackground
		// otherwise - matches Stand's own action-item rows (a plain
		// translucent row, like any other, that turns its one accent
		// colour only when the cursor is actually on it). Permanently
		// accent-filled (this widget's own look before) doesn't match
		// real Stand at all, and made every button row read as "selected"
		// simultaneously - see GridItem.hpp's class comment for what
		// isKeyboardFocused() is.
		GridRenderer::DrawRect(x, y, width, height, isKeyboardFocused() ? Theme::kAccent : Theme::kPanelBackground);
	}

	void GridItemButton::drawText()
	{
		// Left-aligned with the same ~10px inset every other widget here
		// uses (GridItemPrimaryText/GridItemToggle/GridItemTabsVertical/
		// GridItemTabsHorizontal) - centring text within a uniformly-wide
		// button reads as inconsistent once label lengths vary a lot (a
		// short label floats toward the middle, a long one sits near the
		// edges), which is exactly what centring did here. Vertical
		// centring is still clamped to 0: a label taller than height
		// would otherwise centre upward out of this item's own row.
		const auto size = GridRenderer::MeasureText(m_Label.c_str());
		const float textY = y + std::max(0.f, (height - size.y) * 0.5f);
		GridRenderer::DrawText(x + 5.f, textY, m_Label.c_str(), Theme::kText);
	}

	void GridItemButton::onClick(int16_t, int16_t)
	{
		activate();
	}

	void GridItemButton::activate()
	{
		LOGF(INFO, "[GridRenderer] Button '{}' activated", m_Label);

		if (m_Action)
			m_Action();
	}
}
