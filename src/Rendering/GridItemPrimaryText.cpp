#include "GridItemPrimaryText.hpp"

#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemPrimaryText::draw()
	{
		GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);
	}

	void GridItemPrimaryText::drawText()
	{
		const float textY = y + std::max(0.f, (height - GridRenderer::MeasureText(m_Title.c_str()).y) * 0.5f);
		GridRenderer::DrawText(x + 5.f, textY, m_Title.c_str(), Theme::kText);
	}
}
