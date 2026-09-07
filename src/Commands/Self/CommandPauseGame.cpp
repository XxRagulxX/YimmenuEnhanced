#include "Commands/CommandToggle.hpp"
#include "Core/Pointers.hpp"

namespace StandEnhanced::Features
{
	class PauseGame : public CommandToggle
	{
		using CommandToggle::CommandToggle;

		virtual void OnEnable() override
		{
			Pointers.AllowPausingInSessionPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.AllowPausingInSessionPatch->Restore();
		}
	};

	static PauseGame _PauseGame{"pausegame", "Pause Game", "Allows you to pause the game in online (local only)."};
}