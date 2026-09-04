#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"

namespace YimMenu
{
	InputTextWithHint::InputTextWithHint(std::string label, std::string hint, std::string* buf, std::function<void()> cb) :
	    m_Id(std::move(label)),
	    m_Hint(std::move(hint)),
	    m_Buf(buf),
	    m_Callback(std::move(cb))
	{
	}

	void InputTextWithHint::Draw()
	{
		if (!m_Buf)
			return;

		// m_Hint (the placeholder shown while empty) isn't drawn - see
		// Menu/ClassicUI.hpp's own class comment on why full interactive
		// polish is out of scope for this pass. ClassicUI::TextField
		// already shows an empty box either way.
		const auto newValue = ClassicUI::TextField(m_Id, m_Id, *m_Buf);
		if (newValue != *m_Buf)
		{
			*m_Buf = newValue;
			if (m_Callback)
				m_Callback();
		}
	}
}
