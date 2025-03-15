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

namespace YimMenu
{
	namespace Functions
	{
		using PopulateNatives  = void (*)(rage::scrProgram* program);
		using HandleToPtr = void* (*)(int handle);
		using PtrToHandle = int (*)(void* pointer);
	}

	struct PointerData
	{
		IDXGISwapChain1** SwapChain;
		ID3D12CommandQueue** CommandQueue;
		HWND* Hwnd;
		WNDPROC WndProc;
		std::uint32_t* ScreenResX;
		std::uint32_t* ScreenResY;
		rage::atArray<rage::scrThread*>* ScriptThreads;
		Functions::PopulateNatives PopulateNatives;
		std::int64_t** ScriptGlobals;
		PVOID RunScriptThreads;
		Functions::HandleToPtr HandleToPtr;
		Functions::PtrToHandle PtrToHandle;
	};

	struct Pointers : PointerData
	{
		bool Init();
	};

	inline YimMenu::Pointers Pointers;
}