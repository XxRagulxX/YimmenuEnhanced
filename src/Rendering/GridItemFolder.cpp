#include "GridItemFolder.hpp"

#include "GridRenderer.hpp"
#include "MenuNavigation.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kArrowGap = 10.f;
	}

	void GridItemFolder::draw()
	{
		// Same neutral row background GridItemTabsVertical uses for an
		// inactive entry, swapping to Theme::kAccent while keyboard
		// focus is on this row - see GridItem.hpp's class comment.
		GridRenderer::DrawRect(x, y, width, height, isKeyboardFocused() ? Theme::kAccent : Theme::kPanelBackground);
	}

	void GridItemFolder::drawText()
	{
		// Left-aligned label (same ~10px inset as every other row here),
		// right-aligned ">" - both clamped to 0 the same way every other
		// widget in this system is (see GridItemToggle.cpp's comment):
		// otherwise text taller than height centres upward out of this
		// item's own row.
		const auto labelSize = GridRenderer::MeasureText(m_Label.c_str());
		const float labelY = y + std::max(0.f, (height - labelSize.y) * 0.5f);
		GridRenderer::DrawText(x + 10.f, labelY, m_Label.c_str(), Theme::kText);

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
