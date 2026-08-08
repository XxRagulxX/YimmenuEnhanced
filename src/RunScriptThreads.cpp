#include "DetourHook.hpp"
#include "ScriptMgr.hpp"
#include "Hooks.hpp"
#include "Scripts.hpp"

namespace YimMenu::Hooks
{
	bool Script::RunScriptThreads(int ops_to_execute)
	{
		auto res = BaseHook::Get<Script::RunScriptThreads, DetourHook>()->Original<decltype(&RunScriptThreads)>()(ops_to_execute); // let's see what happens if we run our stuff after the game code instead of before
		if (g_Running)
		{
			auto thread = Scripts::FindScriptThread("freemode"_J);
			if (!thread)
				thread = Scripts::FindScriptThread("main_persistent"_J);
			if (!thread)
				thread = Scripts::FindScriptThread("startup"_J);
			if (thread)
			{
				Scripts::RunAsScript(thread, [] {
					//g_script_mgr.tick();;
					g_script_mgr.tick();
				});
			}
		}
		return res;
	}
}