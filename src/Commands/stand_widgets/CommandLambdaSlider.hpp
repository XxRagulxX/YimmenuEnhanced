#pragma once
#include "Commands/IntCommand.hpp"

#include <functional>
#include <optional>
#include <utility>

namespace YimMenu::StandWidgets
{
	// Ported from real Stand's own CommandLambdaSlider (a template over
	// which slider base it wraps there - this project only has one
	// integer slider base, IntCommand, so no template needed here) - see
	// LambdaToggle.hpp's own doc comment for why this whole file exists.
	// Callback receives the new value directly (IntCommand::OnChange()
	// already runs after m_State is updated - see IntCommand::SetState())
	// rather than needing a separate GetState() call.
	class LambdaSlider : public IntCommand
	{
	public:
		LambdaSlider(std::string name,
		    std::string label,
		    std::string description,
		    std::optional<int> min,
		    std::optional<int> max,
		    int def_val,
		    std::function<void(int)> onChange) :
		    IntCommand(std::move(name), std::move(label), std::move(description), min, max, def_val),
		    m_OnChange(std::move(onChange))
		{
		}

	protected:
		void OnChange() override
		{
			if (m_OnChange)
				m_OnChange(GetState());
		}

	private:
		std::function<void(int)> m_OnChange;
	};
}
