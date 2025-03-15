#pragma once
#include "types/rage/RTTI.hpp"

namespace rage
{
	class rlGamerInfo;
}
class CNonPhysicalPlayerData;

namespace rage
{
#pragma pack(push, 8)
	class netPlayer
	{
	public:
		DEFINE_RAGE_RTTI(netPlayer);

		virtual void Reset();
		virtual bool IsPhysical();
		virtual const char* GetName();
		virtual std::uint64_t GetHostToken();
		virtual void UpdatePermissions(); // dev status, comm perms, etc.
		virtual bool IsHost();
		virtual rage::rlGamerInfo* GetGamerInfo();
		virtual void UpdateUnk(); // force updates a player ped data node

		char pad_0008[8];                                //0x0008
		CNonPhysicalPlayerData* m_NonPhysicalPlayer;     //0x0010
		uint32_t m_MessageId;                            //0x0018
		char pad_001C[4];                                //0x001C
		uint8_t m_ActiveId;                              //0x0020
		uint8_t m_PlayerIndex;                              //0x0021
		char pad_0022[0x7E];                             //0x0022
	}; //Size: 0x00A0
	static_assert(sizeof(netPlayer) == 0xA0);
#pragma pack(pop)
}