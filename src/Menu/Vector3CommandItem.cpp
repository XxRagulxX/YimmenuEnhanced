#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/Vector3Command.hpp"

namespace YimMenu
{
	Vector3CommandItem::Vector3CommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<Vector3Command>(id)),
	    m_LabelOverride(label_override)
	{
	}

	// No-op - see BoolCommandItem.cpp's own comment on why.
	void Vector3CommandItem::Draw()
	{
	}
}
