#include "DetourHook.hpp"
#include "NativeHooks.hpp"
#include "ScriptPatches.hpp"
#include "Hooks.hpp"

#include "scrProgram.hpp"

namespace YimMenu::Hooks
{
	void Script::InitNativeTables(rage::scrProgram* program)
	{
		BaseHook::Get<Script::InitNativeTables, DetourHook>()->Original<decltype(&Script::InitNativeTables)>()(program);
		if (g_Running)
		{
			if (program->m_CodeBlocks && program->m_CodeSize)
			{
				NativeHooks::RegisterProgram(program);
				ScriptPatches::RegisterProgram(program);
			}
			else
			{
				// printing name causes crash
				// LOGF(VERBOSE, "InitNativeTables: skipping SHV script {}", program->m_Name);
			}
		}
	}
}