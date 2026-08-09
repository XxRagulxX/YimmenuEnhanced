#include "Command.hpp"

namespace YimMenu::Features
{
	class UnloadMenu : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			g_Running = false;
		}
	};

	static UnloadMenu _UnloadMenu{"unloadmenu", "Unload", "Unload YimMenuV2."};
}