#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/StringCommand.hpp"

namespace YimMenu
{
	StringCommandItem::StringCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<StringCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	// No-op - see BoolCommandItem.cpp's own comment on why.
	void StringCommandItem::Draw()
	{
	}
}
