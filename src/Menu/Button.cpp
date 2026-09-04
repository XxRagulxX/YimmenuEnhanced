#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Scripting/FiberPool.hpp"

namespace YimMenu
{
	Button::Button(const std::string_view& name, std::function<void()> onClick, const ImVec2 size, const std::string_view& information) :
	    m_Name(name),
	    m_Information(information),
	    m_OnClick(onClick),
	    m_Size(size)
	{
	}

	void Button::Draw()
	{
		// m_Size no longer means anything - see Menu/ClassicUI.hpp's own
		// class comment on why every row in this tree is full-width now.
		if (ClassicUI::Button(std::string(m_Name)))
		{
			if (m_OnClick != nullptr)
			{
				FiberPool::queueJob([&] {
					m_OnClick();
				});
			}
		}
	}
}
