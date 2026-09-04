#include "Menu/Items.hpp"
#include "Commands/ColorCommand.hpp"
#include "Commands/Commands.hpp"

namespace YimMenu
{
	ColorCommandItem::ColorCommandItem(joaat_t id, std::optional<std::string> labelOverride) :
	    m_Command(Commands::GetCommand<ColorCommand>(id)),
	    m_LabelOverride(labelOverride)
	{
	}

	// No-op - see BoolCommandItem.cpp's own comment on why.
	void ColorCommandItem::Draw()
	{
	}
}
