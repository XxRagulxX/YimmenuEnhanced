#include "Commands/LoopedCommand.hpp"
#include "Commands/Commands.hpp"

namespace StandEnhanced
{
	LoopedCommand::LoopedCommand(std::string name, std::string label, std::string description) :
	    CommandToggle(name, label, description)
	{
		Commands::AddLoopedCommand(this);
	}

	void LoopedCommand::Tick()
	{
		OnTick();
	}
}