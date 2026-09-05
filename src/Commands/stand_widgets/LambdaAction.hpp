#pragma once
#include "Commands/Command.hpp"

#include <functional>
#include <utility>

namespace YimMenu::StandWidgets
{
	// Ported from real Stand's own CommandLambdaAction - a one-shot
	// action (button) whose behaviour is supplied inline, the Command
	// equivalent of LambdaToggle.hpp's own doc comment (see there for
	// why this whole file exists). Every existing plain-Command feature
	// in this codebase (CommandHeal.cpp, CommandSuicide.cpp, ...) still
	// needs its own subclass file for a single OnCall() override - this
	// lets a one-off action be dropped in with no subclass at all.
	class LambdaAction : public Command
	{
	public:
		LambdaAction(std::string name, std::string label, std::string description, std::function<void()> onCall) :
		    Command(std::move(name), std::move(label), std::move(description), 0),
		    m_OnCall(std::move(onCall))
		{
		}

	protected:
		void OnCall() override
		{
			if (m_OnCall)
				m_OnCall();
		}

	private:
		std::function<void()> m_OnCall;
	};
}
