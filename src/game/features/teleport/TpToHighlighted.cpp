#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static bool GetHighlightedLocation(Vector3& out)
	{
		for (Blip blip = HUD::GET_FIRST_BLIP_INFO_ID(0);
		    HUD::DOES_BLIP_EXIST(blip);
		    blip = HUD::GET_NEXT_BLIP_INFO_ID(0))
		{
			if (!HUD::IS_BLIP_ON_MINIMAP(blip))
				continue;

			if (!HUD::IS_BLIP_FLASHING(blip))
				continue;

			if (HUD::GET_BLIP_ALPHA(blip) != 255)
				continue;

			out = HUD::GET_BLIP_COORDS(blip);
			out.z += 1.0f;
			return true;
		}

		return false;
	}

	class TpToHighlighted : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Vector3 location;
			if (!GetHighlightedLocation(location))
				return;

			Self::GetPed().TeleportTo(location);
		}
	};

	static TpToHighlighted _TpToHighlighted{"tptohighlighted", "Teleport to Highlighted Blip", "Teleports you to the selected map blip"};
}
