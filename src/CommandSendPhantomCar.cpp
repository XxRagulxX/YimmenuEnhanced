#include "PlayerCommand.hpp"
#include "ScriptMgr.hpp"
#include "Scripts.hpp"
#include "ScriptEvent.hpp"
#include "GSBD_RandomEvents.hpp"

namespace YimMenu::Features
{
	class SendPhantomCar : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			Scripts::ForceScriptHost(Scripts::FindScriptThread("freemode"_J));

			if (auto GSBDRandomEvents = GSBD_RandomEvents::Get())
			{
				SCRIPT_EVENT_REQUEST_RANDOM_EVENT data;
				data.FMMCType = 269;
				data.PlayersToSend = 1;
				data.Send();

				ScriptMgr::Yield();

				GSBDRandomEvents->TargetData.PhantomCarTarget = player.GetId();
			}
		}
	};

	static SendPhantomCar _SendPhantomCar{"sendphantomcar", "Send Phantom Car", "Sends the Phantom Car to the specified player."};
}