#include "GridItemRect.hpp"

#include "GridRenderer.hpp"

namespace YimMenu::Rendering
{
	void GridItemRect::Draw()
	{
		GridRenderer::DrawRect(m_X, m_Y, m_Width, m_Height, m_Colour);
	}
}
