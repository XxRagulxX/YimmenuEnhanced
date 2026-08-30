#include "GridItemButton.hpp"

#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		// A single accent colour standing in for Stand's real (theme-loaded,
		// not present in this snapshot) accent - see the note in
		// GridItemHeader.cpp. Swap this out once a real theme system exists.
		constexpr DirectX::XMFLOAT4 kBackground{0.16f, 0.42f, 0.83f, 0.9f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
	}

	void GridItemButton::Draw()
	{
		GridRenderer::DrawRect(m_X, m_Y, m_Width, m_Height, kBackground);
	}

	void GridItemButton::DrawText()
	{
		// Left-aligned with the same ~10px inset every other widget here
		// uses (GridItemHeader/GridItemToggle/GridItemSidebarList/
		// GridItemTabsHorizontal) - centring text within a uniformly-wide
		// button reads as inconsistent once label lengths vary a lot (a
		// short label floats toward the middle, a long one sits near the
		// edges), which is exactly what centring did here. Vertical
		// centring is still clamped to 0: a label taller than m_Height
		// would otherwise centre upward out of this item's own row.
		const auto size = GridRenderer::MeasureText(m_Label.c_str());
		const float textY = m_Y + std::max(0.f, (m_Height - size.y) * 0.5f);
		GridRenderer::DrawText(m_X + 10.f, textY, m_Label.c_str(), kText);
	}

	void GridItemButton::OnClick(float, float)
	{
		LOGF(INFO, "[GridRenderer] Button '{}' clicked", m_Label);

		if (m_Action)
			m_Action();
	}
}
