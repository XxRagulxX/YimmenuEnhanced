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
	extern void RunAsScript(rage::scrThread* thread, std::function<void()> callback);
	extern void RunWithSpoofedThreadName(std::uint32_t name, std::function<void()> callback); // consider using RunAsScript if possible
}