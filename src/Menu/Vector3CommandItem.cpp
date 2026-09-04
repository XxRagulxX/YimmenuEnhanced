#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/Vector3Command.hpp"
#include "World/Self.hpp"

namespace YimMenu
{
	Vector3CommandItem::Vector3CommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<Vector3Command>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void Vector3CommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown!");
			return;
		}

		// The original's own "Saved..." popup (browse Teleport > Saved's
		// own locations from here) isn't ported - see Menu/ClassicUI.hpp's
		// own class comment on why full interactive polish is out of
		// scope for this pass. X/Y/Z steppers + a "Current" button cover
		// the same functionality this item's own callers actually need
		// (setting a coordinate).
		auto value = m_Command->GetState();
		const auto& label = m_LabelOverride.has_value() ? m_LabelOverride.value() : m_Command->GetLabel();
		if (!label.empty())
			ClassicUI::Text(label);

		value.x = ClassicUI::FloatStepper("X", value.x, 1.0f);
		value.y = ClassicUI::FloatStepper("Y", value.y, 1.0f);
		value.z = ClassicUI::FloatStepper("Z", value.z, 1.0f);
		if (value.x != m_Command->GetState().x || value.y != m_Command->GetState().y || value.z != m_Command->GetState().z)
			m_Command->SetState(value);

		if (Self::GetPed() && ClassicUI::Button("Current"))
			m_Command->SetState(Self::GetPed().GetPosition());
	}
}
