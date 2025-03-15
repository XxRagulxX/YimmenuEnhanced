#include "Ped.hpp"

#include "Natives.hpp"
#include "core/backend/ScriptMgr.hpp"


namespace YimMenu
{
	Ped Ped::Create(uint32_t model, rage::fvector3 coords, float heading)
	{
		ENTITY_ASSERT_SCRIPT_CONTEXT();
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "Invalid model passed to Ped::Create: 0x{:X}", model);
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

		auto ped = Ped(PED::CREATE_PED(0, model, coords.x, coords.y, coords.z, heading, true, 0));

		if (!ped)
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "CREATE_PED failed when creating a ped with model {:X}", model);
#endif
			return nullptr;
		}

		ped.SetPosition(coords);
		ped.SetVelocity({});

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		return ped;
	}

	Vehicle Ped::GetVehicle()
	{
		ENTITY_ASSERT_VALID();
		return Vehicle(PED::GET_VEHICLE_PED_IS_IN(GetHandle(), true));
	}

	bool Ped::GetRagdoll()
	{
		ENTITY_ASSERT_VALID();
		return PED::CAN_PED_RAGDOLL(GetHandle());
	}

	void Ped::SetRagdoll(bool enabled)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_CAN_RAGDOLL(GetHandle(), enabled);
	}

	rage::fvector3 Ped::GetBonePosition(int bone)
	{
		ENTITY_ASSERT_VALID();
		return PED::GET_PED_BONE_COORDS(GetHandle(), bone, 0, 0, 0);
	}

	bool Ped::GetConfigFlag(PedConfigFlag flag)
	{
		ENTITY_ASSERT_VALID();
		return PED::GET_PED_CONFIG_FLAG(GetHandle(), (int)flag, false);
	}

	void Ped::SetConfigFlag(PedConfigFlag flag, bool value)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_CONFIG_FLAG(GetHandle(), (int)flag, value);
	}

	bool Ped::IsEnemy()
	{
		ENTITY_ASSERT_VALID();

		// TODO: maybe use a class member?
		auto r1  = PED::GET_RELATIONSHIP_BETWEEN_PEDS(GetHandle(), PLAYER::PLAYER_PED_ID());
		auto r2  = PED::GET_RELATIONSHIP_BETWEEN_PEDS(PLAYER::PLAYER_PED_ID(), GetHandle());
		auto r3  = PED::IS_PED_IN_COMBAT(GetHandle(), PLAYER::PLAYER_PED_ID()) ? 5 : 0;
		auto rel = std::max({r1, r2, r3});

		return rel == 3 || rel == 4 || rel == 5;
	}

	int Ped::GetAccuracy()
	{
		ENTITY_ASSERT_VALID();
		return PED::GET_PED_ACCURACY(GetHandle());
	}

	void Ped::SetAccuracy(int accuracy)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_ACCURACY(GetHandle(), accuracy);
	}

	int Ped::GetPlayer()
	{
		ENTITY_ASSERT_VALID();
#ifdef ENTITY_DEBUG
		if (!IsPlayer())
		{
			LOG(WARNING) << __FUNCTION__ << ": ped is not a player!";
		}
#endif
		return NETWORK::NETWORK_GET_PLAYER_INDEX_FROM_PED(GetHandle());
	}

	void Ped::SetInfiniteAmmo(bool infinite)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		WEAPON::SET_PED_INFINITE_AMMO(GetHandle(), infinite, NULL);
	}

	void Ped::SetInfiniteClip(bool infinite)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		WEAPON::SET_PED_INFINITE_AMMO_CLIP(GetHandle(), infinite); // is this networked?
	}
}