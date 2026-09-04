#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/ListCommand.hpp"

namespace YimMenu
{
	ListCommandItem::ListCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<ListCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	// No-op - see BoolCommandItem.cpp's own comment on why.
	void ListCommandItem::Draw()
	{
	}
}
