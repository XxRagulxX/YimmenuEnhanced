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
		// x+5 (not the usual x+10 elsewhere in this system) - confirmed
		// against stand-reference's own GridItemPrimaryText::draw(),
		// which does exactly `drawTextH(float(x + 5), float(y), ...)`.
		// Vertically centred within height rather than Stand's own plain
		// `float(y)` - this project doesn't have Stand's own TextSettings
		// glyph-anchoring to know whether that's already vertically
		// centred internally, so centring within the row here is the
		// safer equivalent.
		const float textY = y + std::max(0.f, (height - GridRenderer::MeasureText(m_Title.c_str()).y) * 0.5f);
		GridRenderer::DrawText(x + 5.f, textY, m_Title.c_str(), Theme::kText);
	}
}
