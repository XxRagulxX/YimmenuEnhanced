#pragma once
#include "GridItem.hpp"

#include <DirectXMath.h>
#include <string>

namespace YimMenu::Rendering
{
	// A plain text label, drawn via GridRenderer::DrawText (DirectXTK12
	// SpriteFont). No background of its own - Draw() is a no-op; only
	// DrawText() does anything, since text is drawn in a separate pass
	// (SpriteBatch) from solid rectangles (PrimitiveBatch) - see
	// GridRenderer::DrawImpl.
	class GridItemText : public GridItem
	{
	public:
		GridItemText(float height, std::string text, DirectX::XMFLOAT4 colour) :
		    GridItem(height),
		    m_Text(std::move(text)),
		    m_Colour(colour)
		{
		}

		void Draw() override
		{
		}

		void DrawText() override;

	private:
		std::string m_Text;
		DirectX::XMFLOAT4 m_Colour;
	};
}
