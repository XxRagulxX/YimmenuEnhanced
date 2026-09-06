#include "Commands/CommandSliderFloat.hpp"
#include "Scripting/FiberPool.hpp"

namespace YimMenu
{
	void CommandSliderFloat::OnCall()
	{
	}

	void CommandSliderFloat::SaveState(nlohmann::json& value)
	{
		value = m_State;
	}

	void CommandSliderFloat::LoadState(nlohmann::json& value)
	{
		m_State = value;
	}

	CommandSliderFloat::CommandSliderFloat(std::string name, std::string label, std::string description, std::optional<float> min, std::optional<float> max, float def_val) :
	    Command(name, label, description, 0),
	    m_Min(min),
	    m_Max(max),
	    m_State(def_val)
	{
	}

	float CommandSliderFloat::GetState()
	{
		return m_State;
	}

	void CommandSliderFloat::SetState(float state)
	{
		FiberPool::queueJob([this] {
			OnChange();
		});
		m_State = state;
		MarkDirty();
	}

	std::optional<float> CommandSliderFloat::GetMinimum()
	{
		return m_Min;
	}

	std::optional<float> CommandSliderFloat::GetMaximum()
	{
		return m_Max;
	}
}