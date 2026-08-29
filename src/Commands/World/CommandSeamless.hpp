#pragma once

#include "Commands/Widgets/CommandToggle.hpp"

namespace Stand
{
	class CommandSeamless : public CommandToggle
	{
	public:
		inline static CommandListSelect* world_state_config;

		explicit CommandSeamless(CommandList* const parent);

		static void onPreTick();
		static void onPostTick();
		static void onPresent();

		void onEnable(Click& click) final;
		void onDisable(Click& click) final;
	};
}
