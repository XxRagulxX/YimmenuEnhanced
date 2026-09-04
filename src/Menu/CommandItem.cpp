#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/Command.hpp"
#include "Scripting/FiberPool.hpp"

namespace YimMenu
{
	CommandItem::CommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<Command>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void CommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown!");
			return;
		}

		if (ClassicUI::Button(m_LabelOverride.has_value() ? m_LabelOverride.value() : m_Command->GetLabel()))
		{
			// Capture the command by value, not 'this'. This item may be drawn from a
			// Lua command handle's :draw()) and gets destroyed before the FiberPool task runs.
			auto command = m_Command;
			FiberPool::queueJob([command] {
				command->Call();
			});
		}

		// The original's own hover tooltip and Caps Lock hotkey-capture
		// popup aren't ported - see Menu/ClassicUI.hpp's own class
		// comment on why full interactive polish is out of scope for
		// this pass. The Grid equivalent (Settings > Hotkeys) still
		// covers real hotkey assignment.
	}
}
