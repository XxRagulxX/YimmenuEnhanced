#include "GridItemText.hpp"

#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemText::drawText()
	{
		// Same ~10px left inset + vertical centring (clamped to 0 - see
		// the identical comment in GridItemToggle.cpp) every other
		// left-aligned widget in this system uses.
		const auto size = GridRenderer::MeasureText(m_Text.c_str());
		const float textY = y + std::max(0.f, (height - size.y) * 0.5f);
		GridRenderer::DrawText(x + 10.f, textY, m_Text.c_str(), m_Colour);
	}
}
