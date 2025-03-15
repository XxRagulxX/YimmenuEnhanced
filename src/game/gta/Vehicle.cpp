#include "Vehicle.hpp"
#include "Natives.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu
{
	Vehicle Vehicle::Create(std::uint32_t model, rage::fvector3 coords, float heading)
	{
		ENTITY_ASSERT_SCRIPT_CONTEXT();
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "Invalid model passed to Vehicle::Create: 0x{:X}", model);
#endif
			return nullptr;
		}

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(model); i++)
		{
			STREAMING::REQUEST_MODEL(model);
			ScriptMgr::Yield();

			if (i > 30)
			{
#ifdef ENTITY_DEBUG
				LOGF(WARNING, "Model 0x{:X} failed to load after 30 ticks, bailing out", model);
#endif
				return nullptr;
			}
		}

		auto veh = Vehicle(VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, true, false, false));

		if (!veh)
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "CREATE_VEHICLE failed when creating a vehicle with model {:X}", model);
#endif
			return nullptr;
		}

		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh.GetHandle(), 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		return veh;
	}

	void Vehicle::Fix()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(GetHandle()))
		{
			VEHICLE::SET_VEHICLE_FIXED(GetHandle());
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(GetHandle(), 0);
		}
	}
}