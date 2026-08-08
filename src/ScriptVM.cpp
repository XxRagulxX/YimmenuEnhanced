#include "DetourHook.hpp"
#include "Hooks.hpp"
#include "ScriptPatches.hpp"

namespace YimMenu::Hooks
{
	int Script::ScriptVM(uint64_t* stack, uint64_t** scr_globals, rage::scrProgram* program, void* ctx)
	{
		if (g_Running)
		{
			ScriptPatches::OnScriptVMEnter(program);
			auto res = BaseHook::Get<Script::ScriptVM, DetourHook>()->Original<decltype(&Script::ScriptVM)>()(stack, scr_globals, program, ctx);
			ScriptPatches::OnScriptVMLeave(program);
			return res;
		}
		return BaseHook::Get<Script::ScriptVM, DetourHook>()->Original<decltype(&Script::ScriptVM)>()(stack, scr_globals, program, ctx);
	}
}