#include "GridItemText.hpp"

#include "GridRenderer.hpp"

namespace YimMenu::Rendering
{
	void GridItemText::DrawText()
	{
		GridRenderer::DrawText(m_X, m_Y, m_Text.c_str(), m_Colour);
	}
}
