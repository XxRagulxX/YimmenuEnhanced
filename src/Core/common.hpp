#pragma once
#include <AsyncLogger/Logger.hpp>
#include <MinHook.h>
#include <windows.h>
#include <atomic>
#include <imgui.h>


#include <nlohmann/json.hpp>

using namespace al;

#undef Yield

namespace YimMenu
{
	using namespace std::chrono_literals;
	using namespace std::string_view_literals;

	extern std::atomic<bool> g_Running;
	extern HINSTANCE g_DllInstance;
	extern HANDLE g_MainThread;
	extern DWORD g_MainThreadId;
}