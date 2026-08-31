#pragma once
#include <cstdint>

namespace Stand
{
	// Verbatim port of stand-reference's src/Core/ThreadContext.hpp -
	// which execution context a Command call is happening on. Stand's
	// own Command tree is called into from several different places
	// (the game's own script thread, a background Worker, the renderer,
	// WndProc, ...) and a lot of Command/CommandPhysical's own methods
	// branch on this to decide whether it's safe to touch game memory
	// directly or whether the call needs deferring onto a script thread
	// first - see thread_context_is_script()/thread_context_has_game_tls()
	// below, both used exactly that way in real Stand.
	enum ThreadContext : uint8_t
	{
		TC_SCRIPT_NOYIELD,
		TC_SCRIPT_YIELDABLE,
		TC_RENDERER,
		TC_WORKER,
		TC_WNDPROC,
		TC_OTHER,

		TC_APPLYDEFAULTSTATE = TC_SCRIPT_NOYIELD,
	};

	[[nodiscard]] constexpr bool thread_context_is_script(ThreadContext thread_context)
	{
		return thread_context <= TC_SCRIPT_YIELDABLE;
	}

	[[nodiscard]] constexpr bool thread_context_has_game_tls(ThreadContext thread_context)
	{
		return thread_context <= TC_RENDERER;
	}
}
