#include "GridItemHeader.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemHeader::draw()
	{
		// Stand's own focusRectColour (the one accent) - its address bar
		// always shows in this, unlike a plain list row's translucent
		// Theme::kPanelBackground, since it's always "the thing that's
		// currently in focus" (where you are right now).
		GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);
	}

	void GridItemHeader::drawText()
	{
		// Clamped to 0 - see the identical comment in GridItemToggle.cpp:
		// otherwise a title taller than height centres upward out of
		// this item's own row.
		const float textY = y + std::max(0.f, (height - GridRenderer::MeasureText(m_Title.c_str()).y) * 0.5f);
		GridRenderer::DrawText(x + 10.f, textY, m_Title.c_str(), Theme::kText);
	}
}
