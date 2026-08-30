#include "GridItemHeader.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemHeader::Draw()
	{
		// Stand's own focusRectColour (the one accent) - its address bar
		// always shows in this, unlike a plain list row's translucent
		// Theme::kPanelBackground, since it's always "the thing that's
		// currently in focus" (where you are right now).
		GridRenderer::DrawRect(m_X, m_Y, m_Width, m_Height, Theme::kAccent);
	}

	void GridItemHeader::DrawText()
	{
		// Clamped to 0 - see the identical comment in GridItemToggle.cpp:
		// otherwise a title taller than m_Height centres upward out of
		// this item's own row.
		const float textY = m_Y + std::max(0.f, (m_Height - GridRenderer::MeasureText(m_Title.c_str()).y) * 0.5f);
		GridRenderer::DrawText(m_X + 10.f, textY, m_Title.c_str(), Theme::kText);
	}
}
