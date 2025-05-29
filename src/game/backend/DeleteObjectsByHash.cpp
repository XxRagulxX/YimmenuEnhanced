#include "game/gta/Natives.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu
{
	void DeleteObjectsByHash(Hash hash)
	{
		for (auto object : YimMenu::Pools::GetObjects())
		{
			if (!object)
				continue;

			int handle = object.GetHandle();

			if (ENTITY::DOES_ENTITY_EXIST(handle) && ENTITY::GET_ENTITY_MODEL(handle) == hash)
			{
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(handle, true, true);
				OBJECT::DELETE_OBJECT(&handle);
			}
		}
	}
}
