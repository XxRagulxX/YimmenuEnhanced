#include "Commands/CommandLegacy.hpp"
#include "Commands/LoopedCommand.hpp"
#include "Commands/Self/CommandWanted.hpp"
#include "World/Self.hpp"
#include "Scripting/Natives.hpp"

namespace Stand::Features
{
	class SetWanted : public CommandLegacy
	{
		using CommandLegacy::CommandLegacy;

		virtual void OnCall() override
		{
			Self::GetPlayer().SetWantedLevel(GetCommandWanted().value);
		}
	};

	class NeverWanted : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			Self::GetPlayer().SetWantedLevel(0);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
		}

		virtual void OnDisable() override
		{
			PLAYER::SET_MAX_WANTED_LEVEL(6);
		}
	};

	static SetWanted _SetWanted{"setwanted", "Set Wanted", "Sets your wanted level to the desired level"};
	static NeverWanted _NeverWanted{"neverwanted", "Never Wanted", "Never gain a wanted level"};
}
