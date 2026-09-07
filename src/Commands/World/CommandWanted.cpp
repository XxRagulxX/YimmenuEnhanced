#include "Commands/CommandLegacy.hpp"
#include "Commands/LoopedCommand.hpp"
#include "Commands/Self/CommandWanted.hpp"
#include "World/Self.hpp"
#include "Scripting/Natives.hpp"

namespace Stand::Features
{
	class ClearWanted : public CommandLegacy
	{
		using CommandLegacy::CommandLegacy;

		virtual void OnCall() override
		{
			Self::GetPlayer().SetWantedLevel(0);
		}
	};

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

	class FreezeWanted : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPlayer().GetWantedLevel() != GetCommandWanted().value)
				Self::GetPlayer().SetWantedLevel(GetCommandWanted().value);
			PLAYER::SET_MAX_WANTED_LEVEL(GetCommandWanted().value);
		}
	};

	static ClearWanted _ClearWanted{"clearwanted", "Clear Wanted", "Clears your wanted level"};
	static SetWanted _SetWanted{"setwanted", "Set Wanted", "Sets your wanted level to the desired level"};
	static NeverWanted _NeverWanted{"neverwanted", "Never Wanted", "Never gain a wanted level"};
	static FreezeWanted _FreezeWanted{"freezewanted", "Freeze Wanted", "Freeze your wanted level to the desired level"};
}
