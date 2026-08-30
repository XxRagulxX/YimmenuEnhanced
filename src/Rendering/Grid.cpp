#include "Grid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		// Without this, two adjacent items with the same full-width
		// background colour (e.g. a run of GridItemButton/
		// GridItemCommandButton rows) render as one indistinguishable
		// merged block - there's no other visual boundary between rows.
		constexpr float kItemGap = 3.f;
	}

	void Grid::SetPositions()
	{
		float y = m_Y;
		for (auto& item : m_Items)
		{
			item->SetPosition(m_X, y, m_Width);
			y += item->GetHeight() + kItemGap;
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
