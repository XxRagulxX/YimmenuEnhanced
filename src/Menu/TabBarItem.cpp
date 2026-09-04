#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"

namespace YimMenu
{
	TabBarItem::TabBarItem(const std::string& id) :
	    m_Id(id)
	{
	}

	void TabBarItem::Draw()
	{
		// No real tab strip any more - see Items.hpp's own comment on
		// m_ActiveIndex for why this now owns the active/inactive switch
		// itself instead of a real ImGui tab bar doing it. One row per
		// tab name (the active one shown as plain text, same convention
		// Submenu::DrawCategorySelectors() uses), then that tab's own
		// items drawn below it.
		for (size_t i = 0; i < m_Tabs.size(); i++)
		{
			if (!m_Tabs[i])
				continue;

			if (static_cast<int>(i) == m_ActiveIndex)
				ClassicUI::Text("> " + m_Tabs[i]->GetName());
			else if (ClassicUI::Button(m_Tabs[i]->GetName()))
				m_ActiveIndex = static_cast<int>(i);
		}

		if (m_ActiveIndex >= 0 && static_cast<size_t>(m_ActiveIndex) < m_Tabs.size() && m_Tabs[static_cast<size_t>(m_ActiveIndex)])
		{
			ClassicUI::Separator();
			if (m_Tabs[static_cast<size_t>(m_ActiveIndex)]->CanDraw())
				m_Tabs[static_cast<size_t>(m_ActiveIndex)]->Draw();
		}
	}
}
