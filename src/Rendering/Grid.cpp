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

	void Grid::EnsurePopulated()
	{
		if (m_Populated)
			return;

		Populate();
		SetPositions();
		m_Populated = true;
	}

	void Grid::Draw()
	{
		EnsurePopulated();

		for (auto& item : m_Items)
			item->Draw();
	}

	void Grid::DrawText()
	{
		EnsurePopulated();

		for (auto& item : m_Items)
			item->DrawText();
	}

	GridItem* Grid::FindItemAt(float cursorX, float cursorY)
	{
		EnsurePopulated();

		for (auto& item : m_Items)
		{
			if (item->Contains(cursorX, cursorY))
				return item.get();
		}

		return nullptr;
	}
}
