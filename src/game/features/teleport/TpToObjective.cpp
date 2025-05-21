#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class TpToObjective final : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			// Blip sprite types that could represent objectives
			static constexpr std::array<int, 23> kObjectiveSprites = {1, 0, 2, 38, 143, 144, 145, 146, 535, 536, 537, 538, 539, 540, 541, 542, 556, 568, 615, 760, 780, 817, 842};

			Vector3 objectiveLocation;

			for (int sprite : kObjectiveSprites)
			{
				Blip blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite);
				if (blip != 0)
				{
					objectiveLocation = HUD::GET_BLIP_COORDS(blip);
					Self::GetPed().TeleportTo(objectiveLocation);

					Notifications::Show("Teleporting to Objective", "Teleported to the objective.", NotificationType::Success, 5000);
					return;
				}
			}

			Notifications::Show("Teleporting to Objective", "No objective found.", NotificationType::Error, 5000);
		}
	};

	static TpToObjective _TpToObjective{"tptoobjective", "Teleport to Objective", "Teleports you to the Objective"};
}
