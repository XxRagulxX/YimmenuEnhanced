#include "Rendering/GridItemRect.hpp"

#include "Rendering/GridRenderer.hpp"

namespace StandEnhanced::Rendering
{
	void GridItemRect::draw()
	{
		GridRenderer::DrawRect(x, y, width, height, m_Colour);
	}
}
