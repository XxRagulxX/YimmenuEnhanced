#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/FloatCommand.hpp"

#include <algorithm>

namespace YimMenu
{
	FloatCommandItem::FloatCommandItem(joaat_t id, std::optional<std::string> label_override, bool use_slider) :
	    m_useSlider(use_slider),
	    m_Command(Commands::GetCommand<FloatCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void FloatCommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown!");
			return;
		}

		// m_useSlider only chose between two real ImGui widget shapes
		// (SliderFloat vs InputFloat) - both are the same "- value +"
		// stepper row here (see Menu/ClassicUI.hpp's own class comment on
		// why full interactive polish, drag sliders included, is out of
		// scope for this pass), so it no longer changes anything.
		const auto label = m_LabelOverride.has_value() ? m_LabelOverride.value() : m_Command->GetLabel();
		const auto value = ClassicUI::FloatStepper(label, m_Command->GetState());
		if (value != m_Command->GetState())
		{
			const auto clamped = std::clamp(value, m_Command->GetMinimum().value_or(value), m_Command->GetMaximum().value_or(value));
			m_Command->SetState(clamped);
		}
	}
}
