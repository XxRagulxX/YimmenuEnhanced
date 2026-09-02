#include "Commands/BoolCommand.hpp"
#include "Commands/IntCommand.hpp"
#include "Commands/PlayerCommand.hpp"
#include "Network/ScriptEvent.hpp"
#include "Network/GSBD_FM_Events.hpp"

namespace YimMenu::Features
{
	static IntCommand _BountyAmount{"bountyamount", "Bounty Amount", "The bounty amount to set", 1, 10000, 9000};
	static BoolCommand _AnonymousBounty{"anonymousbounty", "Anonymous Bounty", "Sets the bounty as anonymous"};

	class SetBounty : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			SCRIPT_EVENT_BOUNTY bounty;
			bounty.Target = player.GetId();
			bounty.FromPed = _AnonymousBounty.GetState();
			bounty.Amount = _BountyAmount.GetState();
			bounty.BountyFlags = 1;
			bounty.AntiReplayValue1 = GSBD_FM_Events::Get()->AntiReplayValue1;
			bounty.AntiReplayValue2 = GSBD_FM_Events::Get()->AntiReplayValue2;
			bounty.SetAllPlayers();
			bounty.Send();
		}
	};

	static SetBounty _SetBounty{"setbounty", "Set Bounty", "Sets the specified bounty to the player"};
}