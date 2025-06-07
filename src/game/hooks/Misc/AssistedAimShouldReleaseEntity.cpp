#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "types/entity/CDynamicEntity.hpp"
#include "game/gta/Ped.hpp"

namespace YimMenu::Hooks
{
	bool Misc::AssistedAimShouldReleaseEntity(__int64 a1)
	{
		auto entity = *(CDynamicEntity**)(a1 + 0x38);

		if (entity && entity->IsPed() && Ped(entity).IsDead())
		{
			return true;
		}

		return BaseHook::Get<Misc::AssistedAimShouldReleaseEntity, DetourHook<decltype(&Misc::AssistedAimShouldReleaseEntity)>>()->Original()(a1);
	}
}