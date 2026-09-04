#include "Menu/ClassicUI.hpp"
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

	void ColorCommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown color picker!");
			return;
		}

		// Non-interactive swatch, no picker popup - see Menu/ClassicUI.hpp's
		// own class comment on why. Grid's own GridItemCommandColor
		// (discrete R/G/B/A steppers) covers real colour editing.
		const auto color = m_Command->GetState();
		const auto label = m_LabelOverride.has_value() ? m_LabelOverride.value() : m_Command->GetLabel();
		ClassicUI::ColorSwatch(label, DirectX::XMFLOAT4{color.x, color.y, color.z, color.w});
	}
}
