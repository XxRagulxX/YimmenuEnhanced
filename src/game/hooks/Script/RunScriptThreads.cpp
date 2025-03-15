#include "core/hooking/DetourHook.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/gta/Scripts.hpp"

namespace YimMenu::Hooks
{
	bool Script::RunScriptThreads(int ops_to_execute)
	{
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
					ScriptMgr::Tick();
				});
			}
		}
		return BaseHook::Get<Script::RunScriptThreads, DetourHook<decltype(&RunScriptThreads)>>()->Original()(ops_to_execute);
	}
}