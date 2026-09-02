#include "Rendering/GridItemFolder.hpp"

#include "Rendering/GridRenderer.hpp"
#include "Rendering/MenuNavigation.hpp"
#include "Rendering/Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kArrowGap = 5.f;
	}

	void GridItemFolder::draw()
	{
		GridRenderer::DrawRect(x, y, width, height, isKeyboardFocused() ? Theme::kAccent : Theme::kPanelBackground);
	}

	void GridItemFolder::drawText()
	{
		const auto labelSize = GridRenderer::MeasureText(m_Label.c_str());
		const float labelY = y + std::max(0.f, (height - labelSize.y) * 0.5f);
		GridRenderer::DrawText(x + 5.f, labelY, m_Label.c_str(), Theme::kText);

		const auto arrowSize = GridRenderer::MeasureText(">");
		const float arrowY = y + std::max(0.f, (height - arrowSize.y) * 0.5f);
		GridRenderer::DrawText(x + width - arrowSize.x - kArrowGap, arrowY, ">", Theme::kText);
	}

	void GridItemFolder::onClick(int16_t, int16_t)
	{
		activate();
	}

	void GridItemFolder::activate()
	{
		LOGF(INFO, "[GridRenderer] Folder '{}' activated", m_Label);

		MenuNavigation::Push(m_Label, m_Target);
	}
}
