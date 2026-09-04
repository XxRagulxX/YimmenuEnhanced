#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/IntCommand.hpp"

namespace YimMenu
{
	IntCommandItem::IntCommandItem(joaat_t id, std::optional<std::string> label_override, bool use_slider) :
	    m_useSlider(use_slider),
	    m_Command(Commands::GetCommand<IntCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	// No-op - see BoolCommandItem.cpp's own comment on why.
	void IntCommandItem::Draw()
	{
	}
}
