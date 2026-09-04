#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"

namespace YimMenu
{
	Group::Group(const std::string& name, int items_per_column) :
	    m_Name(name),
	    m_ItemsPerColumn(items_per_column)
	{
	}

	void Group::Draw()
	{
		// m_ItemsPerColumn no longer means anything - the original's own
		// multi-column layout isn't ported (see Menu/ClassicUI.hpp's own
		// class comment on why); every item just flows top-to-bottom.
		if (!m_Name.empty())
		{
			ClassicUI::Text(m_Name);
			ClassicUI::Separator();
		}

		for (auto& item : m_Items)
		{
			if (item->CanDraw())
				item->Draw();
		}
	}
}
