#include "GridItemRect.hpp"

#include "GridRenderer.hpp"

namespace YimMenu::Rendering
{
	void GridItemRect::draw()
	{
		GridRenderer::DrawRect(x, y, width, height, m_Colour);
	}
}
