#include "Core/yeet_flow.hpp"

#include "lib/soup/ObfusString.hpp"

#include "Core/ConsoleLogger.hpp"
#include "Network/HttpRequestBuilder.hpp"
#include "Network/NetInterface.hpp"
#include "Scripting/Script.hpp"
#include "Util/Util.hpp"

namespace Stand
{

	void yeet_flow(ThreadContext thread_context)
	{
		yeet_now();
	}

	void yeet_now() // OBFUS!
	{
		g_console.deinit();

		// Exiting means dtoring everything, and if this is called from an HTTP callback, that includes the thread that is running this code.
		// However, dtoring the thread would mean awaiting its completion. A thread waiting for itself... yeah, so: just invalidate it.
		g_net_interface.thrd.handle = INVALID_HANDLE_VALUE;

		Exceptional::disableExceptionHandling();
		SOUP_IF_UNLIKELY (g_yeeting_with_abort)
		{
			abort();
		}
		TerminateProcess(GetCurrentProcess(), 0);
	}
}
