#include "GridItemHeader.hpp"

#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		// stand-reference's default bgRectColour/bgTextColour (translucent
		// black background, white text) - see src/Rendering/Renderer.hpp in
		// stand-reference. Most of its other theme colours default to
		// placeholder magenta in the reference source, meaning the actual
		// shipped palette is loaded from an external theme file at runtime
		// that isn't present in this snapshot - alpha here is bumped up
		// from stand's 0.3 default for a header specifically, since it
		// needs to read clearly as a distinct bar rather than a faint panel.
		constexpr DirectX::XMFLOAT4 kBackground{0.f, 0.f, 0.f, 0.75f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
	}

	void GridItemHeader::Draw()
	{
		GridRenderer::DrawRect(m_X, m_Y, m_Width, m_Height, kBackground);
	}

	void GridItemHeader::DrawText()
	{
		// Clamped to 0 - see the identical comment in GridItemToggle.cpp:
		// otherwise a title taller than m_Height centres upward out of
		// this item's own row.
		const float textY = m_Y + std::max(0.f, (m_Height - GridRenderer::MeasureText(m_Title.c_str()).y) * 0.5f);
		GridRenderer::DrawText(m_X + 10.f, textY, m_Title.c_str(), kText);
	}
}
