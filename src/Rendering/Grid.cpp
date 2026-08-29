#include "Grid.hpp"

namespace YimMenu::Rendering
{
	void Grid::SetPositions()
	{
		float y = m_Y;
		for (auto& item : m_Items)
		{
			item->SetPosition(m_X, y, m_Width);
			y += item->GetHeight();
		}
	}

	void Grid::Draw()
	{
		if (!m_Populated)
		{
			Populate();
			SetPositions();
			m_Populated = true;
		}

		for (auto& item : m_Items)
			item->Draw();
	}
}
