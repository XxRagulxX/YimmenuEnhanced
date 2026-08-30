#include "GridItemFolder.hpp"

#include "GridRenderer.hpp"
#include "MenuNavigation.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		// Same neutral row background GridItemSidebarList uses for an
		// inactive entry - a folder row isn't an action (GridItemButton's
		// bright accent) or a bare value, just another row in the list
		// that happens to lead somewhere else.
		constexpr DirectX::XMFLOAT4 kBackground{0.f, 0.f, 0.f, 0.4f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
		constexpr float kArrowGap = 10.f;
	}

	void GridItemFolder::Draw()
	{
		GridRenderer::DrawRect(m_X, m_Y, m_Width, m_Height, kBackground);
	}

	void GridItemFolder::DrawText()
	{
		// Left-aligned label (same ~10px inset as every other row here),
		// right-aligned ">" - both clamped to 0 the same way every other
		// widget in this system is (see GridItemToggle.cpp's comment):
		// otherwise text taller than m_Height centres upward out of this
		// item's own row.
		const auto labelSize = GridRenderer::MeasureText(m_Label.c_str());
		const float labelY = m_Y + std::max(0.f, (m_Height - labelSize.y) * 0.5f);
		GridRenderer::DrawText(m_X + 10.f, labelY, m_Label.c_str(), kText);

		const auto arrowSize = GridRenderer::MeasureText(">");
		const float arrowY = m_Y + std::max(0.f, (m_Height - arrowSize.y) * 0.5f);
		GridRenderer::DrawText(m_X + m_Width - arrowSize.x - kArrowGap, arrowY, ">", kText);
	}

	void GridItemFolder::OnClick(float, float)
	{
		LOGF(INFO, "[GridRenderer] Folder '{}' clicked", m_Label);

		MenuNavigation::Push(m_Label, m_Target);
	}
}
