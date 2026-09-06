#pragma once
#include "Commands/CommandToggle.hpp"

namespace YimMenu
{
	class LoopedCommand : public CommandToggle
	{
	protected:
		virtual void OnTick() = 0;

	public:
		LoopedCommand(std::string name, std::string label, std::string description);
		void Tick();
	};
}