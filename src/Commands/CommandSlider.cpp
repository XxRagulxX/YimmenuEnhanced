#include "Commands/CommandSlider.hpp"
#include "Scripting/FiberPool.hpp"

namespace StandEnhanced
{
	void CommandSlider::OnCall()
	{
	}

	void CommandSlider::SaveState(nlohmann::json& value)
	{
		value = m_State;
	}

	void CommandSlider::LoadState(nlohmann::json& value)
	{
		m_State = value;
	}

	CommandSlider::CommandSlider(std::string name, std::string label, std::string description, std::optional<int> min, std::optional<int> max, int def_val) :
	    Command(name, label, description, 0),
	    m_Min(min),
	    m_Max(max),
	    m_State(def_val)
	{
	}

	int CommandSlider::GetState()
	{
		return m_State;
	}

	void CommandSlider::SetState(int state)
	{
		FiberPool::queueJob([this] {
			OnChange();
		});
		m_State = state;
		MarkDirty();
	}

	std::optional<int> CommandSlider::GetMinimum()
	{
		if (m_DynamicRange)
			return m_DynamicRange().first;

		return m_Min;
	}

	std::optional<int> CommandSlider::GetMaximum()
	{
		if (m_DynamicRange)
			return m_DynamicRange().second;

		return m_Max;
	}

	void CommandSlider::SetDynamicRange(std::function<std::pair<int, int>()> dynamicRange)
	{
		m_DynamicRange = std::move(dynamicRange);
	}
}