#include "core/commands/Command.hpp"
#include "game/gta/Network.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/Natives.hpp"
#include "core/logger/LogHelper.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Features
{
	class ForceQuitToStoryMode : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
			{
				try
				{
					NETWORK::SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE();
				}
				catch (const std::exception& e)
				{
					LOG(FATAL) << "Transition failed: " << e.what();
				}
			}
			else
			{
				Notifications::Show("Force Quit to Story Mode", "Already in Story Mode");
			}
		}
	};

	static ForceQuitToStoryMode _ForceQuitToStoryMode{"forcequittosp", "Force Quit to SP", "Go to single player story mode"};
}
