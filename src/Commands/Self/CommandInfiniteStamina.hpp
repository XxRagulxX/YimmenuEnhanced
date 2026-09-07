#pragma once
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandToggle.hpp"

#include "World/Self.hpp"

namespace Stand
{
	class CommandInfiniteStamina : public CommandToggle
	{
	public:
		explicit CommandInfiniteStamina(CommandList* parent) :
		    CommandToggle(parent, LIT("Infinite Stamina"), CMDNAMES("infstamina", "infinitestamina"))
		{
		}

		void onEnable(Click& click) override
		{
			CommandTickDispatch::AddCommand(this);
		}

		void onDisable(Click& click) override
		{
			CommandTickDispatch::RemoveCommand(this);
		}

		void onTick() override
		{
			if (auto player = Stand::Self::GetPlayer())
				PLAYER::RESTORE_PLAYER_STAMINA(player.GetId(), 1.0f);
		}

		~CommandInfiniteStamina() override
		{
			CommandTickDispatch::RemoveCommand(this);
		}
	};
}

namespace Stand::Features
{
	Stand::CommandInfiniteStamina& GetCommandInfiniteStamina();
}
