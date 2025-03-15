#pragma once
#include "core/util/Joaat.hpp"

namespace rage
{
	class scrThread;
	class scrProgram;
}

namespace YimMenu::Scripts
{
	extern rage::scrThread* FindScriptThread(joaat_t hash);
	// extern rage::scrProgram* FindScriptProgram(joaat_t hash);
	extern void RunAsScript(rage::scrThread* thread, std::function<void()> callback);
}