#include "Rendering/GridItemButton.hpp"

#include "Rendering/GridRenderer.hpp"
#include "Rendering/Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	void GridItemButton::draw()
	{
		GridRenderer::DrawRect(x, y, width, height, isKeyboardFocused() ? Theme::kAccent : Theme::kPanelBackground);
	}

	void GridItemButton::drawText()
	{
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
