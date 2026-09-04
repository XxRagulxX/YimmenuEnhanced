#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"

namespace YimMenu
{
	CollapsingHeaderItem::CollapsingHeaderItem(const std::string& name) :
	    m_Name(name)
	{
	}

	void CollapsingHeaderItem::Draw()
	{
		// See Items.hpp's own comment on m_Expanded for why this now owns
		// its own expanded/collapsed state instead of a real ImGui
		// CollapsingHeader doing it.
		if (ClassicUI::Button((m_Expanded ? "v " : "> ") + m_Name))
			m_Expanded = !m_Expanded;

		if (!m_Expanded)
			return;

		for (auto& item : m_Items)
		{
			if (item->CanDraw())
				item->Draw();
		}
	}
}
