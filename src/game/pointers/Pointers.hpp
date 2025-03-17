#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <windows.h>
#include "types/script/scrNativeHandler.hpp"

namespace rage
{
	template<typename T>
	class atArray;
	class scrThread;
	class scrProgram;
}
class CPedFactory;
class CNetGamePlayer;
class CEntity;

namespace YimMenu
{
	namespace Functions
	{
		using HandleToPtr = void* (*)(int handle);
		using PtrToHandle = int (*)(void* pointer);
		using GetNetPlayerFromPid = CNetGamePlayer* (*)(int id);
		using TriggerWeaponDamageEvent = void (*)(CEntity* source, CEntity* target, rage::fvector3* position, int hit_component, bool override_default_damage, int weapon_type, float override_damage, int tire_index, int suspension_index, int flags, uint32_t action_result_hash, int16_t action_result_id, int action_unk, bool hit_weapon, bool hit_weapon_ammo_attachment, bool silenced, bool unk, rage::fvector3* impact_direction);
	}

	struct PointerData
	{
		IDXGISwapChain1** SwapChain;
		ID3D12CommandQueue** CommandQueue;
		HWND* Hwnd;
		PVOID WndProc;
		std::uint32_t* ScreenResX;
		std::uint32_t* ScreenResY;
		rage::atArray<rage::scrThread*>* ScriptThreads;
		PVOID InitNativeTables;
		std::int64_t** ScriptGlobals;
		PVOID RunScriptThreads;
		Functions::HandleToPtr HandleToPtr;
		Functions::PtrToHandle PtrToHandle;
		CPedFactory** PedFactory;
		Functions::GetNetPlayerFromPid GetNetPlayerFromPid;
		bool* IsSessionStarted;
		PVOID AssignPhysicalIndex;
		Functions::TriggerWeaponDamageEvent TriggerWeaponDamageEvent;
		rage::scrProgram** ScriptPrograms;
	};

	struct Pointers : PointerData
	{
		bool Init();
	};

	inline YimMenu::Pointers Pointers;
}