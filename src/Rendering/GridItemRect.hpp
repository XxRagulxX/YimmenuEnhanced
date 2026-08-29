#pragma once
#include "GridItem.hpp"

#include <DirectXMath.h>

namespace YimMenu::Rendering
{
	// A plain solid-colour rectangle. The simplest possible concrete
	// GridItem, used to prove out the Grid/GridItem tree before real
	// widget types (text, buttons, tabs, ...) land.
	class GridItemRect : public GridItem
	{
	public:
		GridItemRect(float height, DirectX::XMFLOAT4 colour) :
		    GridItem(height),
		    m_Colour(colour)
		{
		}

		void Draw() override;

	private:
		DirectX::XMFLOAT4 m_Colour;
	};
}
