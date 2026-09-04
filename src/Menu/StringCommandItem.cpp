#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/StringCommand.hpp"

#include <cstdint>
#include <format>

namespace YimMenu
{
	StringCommandItem::StringCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<StringCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void StringCommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown string command!");
			return;
		}

		const auto id = std::format("strcmd{}", reinterpret_cast<std::uintptr_t>(m_Command));
		const auto label = m_LabelOverride.value_or(m_Command->GetLabel());
		const auto newValue = ClassicUI::TextField(id, label, m_Command->GetString());
		if (newValue != m_Command->GetString())
			m_Command->SetStringValue(newValue);
	}
}
