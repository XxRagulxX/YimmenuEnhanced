#include "Commands/CommandToggle.hpp"
#include "Scripting/FiberPool.hpp"
#include "Commands/Commands.hpp"

namespace StandEnhanced
{
	CommandToggle::CommandToggle(std::string name, std::string label, std::string description, bool def_value) :
	    Command(name, label, description, 0),
	    m_State(def_value)
	{
		Commands::AddBoolCommand(this);
	}

	void CommandToggle::OnCall()
	{
		SetState(!m_State);
	}

	void CommandToggle::SaveState(nlohmann::json& value)
	{
		value = m_State;
	}

	void CommandToggle::LoadState(nlohmann::json& value)
	{
		m_State = value;
	}

	bool CommandToggle::GetState()
	{
		return m_State;
	}

	void CommandToggle::SetState(bool state)
	{
		if (state && !m_State)
		{
			FiberPool::queueJob([this] {
				OnEnable();
				m_Ready = true;
			});
		}
		else if (!state && m_State)
		{
			FiberPool::queueJob([this] {
				OnDisable();
				m_Ready = true;
			});
		}

		m_Ready = false;
		m_State = state;
		MarkDirty();
	}

	void CommandToggle::Initialize()
	{
		OnEnable();
		m_Ready = true;
	}

	void CommandToggle::Shutdown()
	{
		m_Ready = false;
		OnDisable();
	}
}