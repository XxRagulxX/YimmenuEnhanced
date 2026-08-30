#include "GridItemText.hpp"

#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemText::DrawText()
	{
		// Same ~10px left inset + vertical centring (clamped to 0 - see
		// the identical comment in GridItemToggle.cpp) every other
		// left-aligned widget in this system uses.
		const auto size = GridRenderer::MeasureText(m_Text.c_str());
		const float textY = m_Y + std::max(0.f, (m_Height - size.y) * 0.5f);
		GridRenderer::DrawText(m_X + 10.f, textY, m_Text.c_str(), m_Colour);
	}
}
