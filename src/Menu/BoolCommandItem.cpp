#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Commands/BoolCommand.hpp"
#include "Commands/Commands.hpp"

namespace YimMenu
{
	BoolCommandItem::BoolCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<BoolCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void BoolCommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown!");
			return;
		}

		const auto label = m_LabelOverride.has_value() ? m_LabelOverride.value() : m_Command->GetLabel();
		const bool enabled = ClassicUI::Toggle(label, m_Command->GetState());
		if (enabled != m_Command->GetState())
			m_Command->SetState(enabled);

		// The original's own hotkey-capture popup (hover + Caps Lock to
		// bind a key) isn't ported - see Menu/ClassicUI.hpp's own class
		// comment on why full interactive polish is out of scope for
		// this pass. The Grid equivalent (Settings > Hotkeys) still
		// covers real hotkey assignment.
	}
}
