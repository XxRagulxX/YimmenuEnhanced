#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Commands/PlayerCommand.hpp"
#include "Commands/Commands.hpp"
#include "Scripting/FiberPool.hpp"
#include "Network/Players.hpp"

namespace YimMenu
{
	PlayerCommandItem::PlayerCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<PlayerCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void PlayerCommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown!");
			return;
		}

		if (ClassicUI::Button(m_LabelOverride.has_value() ? m_LabelOverride.value() : m_Command->GetLabel()))
		{
			FiberPool::queueJob([this] {
				if (Players::GetSelected().IsValid())
					m_Command->Call(Players::GetSelected());
			});
		}

		// The original's own hover tooltip isn't ported - see
		// Menu/ClassicUI.hpp's own class comment.
	}
}
