#include "common.hpp"
#include "ScriptMgr.hpp"
#include "FiberPool.hpp"
#include "Commands.hpp"
#include "HotkeySystem.hpp"
#include "Settings.hpp"
#include "FileMgr.hpp"
#include "Notifications.hpp"
#include "Hooking.hpp"
#include "CallHook.hpp"
#include "ModuleMgr.hpp"
#include "Renderer.hpp"
#include "Wine.hpp"
#include "LuaManager.hpp"
#include "AnticheatBypass.hpp"
#include "Players.hpp"
#include "CommandSavedLocations.hpp"
#include "CommandSavedPlayers.hpp"
#include "Self.hpp"
#include "NativeHooks.hpp"
#include "Tunables.hpp"
#include "ScriptPointers.hpp"
#include "GUI.hpp"
#include "Pointers.hpp"
#include "CommandSavePersonalVehicle.hpp"
#include "CommandOpenGunLocker.hpp"
#include "CommandDailyActivities.hpp"
#include "LogHelper.hpp"

namespace YimMenu
{
	DWORD Main(void*)
	{
		const auto documents = std::filesystem::path(std::getenv("appdata")) / "YimMenuV2";
		FileMgr::Init(documents);

		HMODULE module = GetModuleHandle(nullptr);

		LogHelper::Init("YimMenuV2", FileMgr::GetProjectFile("./cout.log"));

		LOGF(INFO, "Welcome to YimMenuV2! Build date: {} at {}", __DATE__, __TIME__);

		g_HotkeySystem.RegisterCommands();
		SavedLocations::FetchSavedLocations();
		Settings::Initialize(FileMgr::GetProjectFile("./settings.json"));

		if (!ModuleMgr.LoadModules())
			goto EARLY_UNLOAD;

		if (ModuleMgr.IsManualMapped())
			LOGF(WARNING, "Manual mapping detected, switch to normal injection if you're having issues");

		if (!Pointers.Init())
			goto EARLY_UNLOAD;

		AnticheatBypass::RunOnStartup();

		if (!Renderer::Init())
			goto EARLY_UNLOAD;

		Players::Init();

		Hooking::Init();

		//ScriptMgr::Init();
		//g_script_mgr.Init();
		LOG(INFO) << "ScriptMgr initialized";

		ScriptPointers::Init();

		GUI::Init();

		g_script_mgr.addScript(module, std::make_unique<Script>(&NativeHooks::RunScript)); // runs once
		g_script_mgr.addScript(module, std::make_unique<Script>(&Tunables::RunScript));    // runs once
		g_script_mgr.addScript(module, std::make_unique<Script>(&AnticheatBypass::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&Self::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&GUI::RunScript));

		g_script_mgr.addScript(module, std::make_unique<Script>(&LuaManager::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&HotkeySystem::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&Commands::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&Features::SavePersonalVehicle::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&Features::OpenGunLocker::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&Features::OpenStreetDealerMenu::RunScript));
		g_script_mgr.addScript(module, std::make_unique<Script>(&SavedPlayers::RunScript));

		if (!Pointers.LateInit())
			LOG(WARNING) << "Socialclub patterns failed to load";

		Notifications::Show("YimMenuV2", "Loaded succesfully", NotificationType::Success);

		if (InWine().value_or(false))
		    LOG(INFO) << "Running in Wine!";

		while (g_Running)
		{
			Settings::Tick();
			std::this_thread::yield();
		}

		LOG(INFO) << "Unloading";
		//ScriptMgr::Destroy();
		g_script_mgr.deinit();
		NativeHooks::Destroy();
		Hooking::Destroy();
		CallSiteHook::Destroy();

	EARLY_UNLOAD:
		g_Running = false;
		Renderer::Destroy();
		LogHelper::Destroy();

		CloseHandle(g_MainThread);
		FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);

		return EXIT_SUCCESS;
	}
}

BOOL WINAPI DllMain(HINSTANCE dllInstance, DWORD reason, void*)
{
	using namespace YimMenu;

	if (dllInstance)
		DisableThreadLibraryCalls(dllInstance);

	if (reason == DLL_PROCESS_ATTACH)
	{
		g_DllInstance = dllInstance;

		g_MainThread = CreateThread(nullptr, 0, Main, nullptr, 0, &g_MainThreadId);
	}
	return true;
}