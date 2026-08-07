#include "ExecCtx.hpp"

#include <soup/os.hpp>

#include "FiberPool.hpp"
#include "Script.hpp"

namespace YimMenu
{
	static thread_local ExecCtx inst;

	ExecCtx& ExecCtx::get() noexcept
	{
		return inst;
	}

	bool ExecCtx::isScript() const noexcept
	{
		return thread_context_is_script(tc);
	}

	bool ExecCtx::hasGameTls() const noexcept
	{
		return thread_context_has_game_tls(tc);
	}

	void ExecCtx::ensureScript(std::function<void()>&& f)
	{
		if (isScript())
		{
			f();
		}
		else
		{
			// If you rename FiberPool to match Stand:
			// FiberPool::queueJob(std::move(f));

			// Until then:
			FiberPool::queueJob(std::move(f));
		}
	}

	void ExecCtx::yield()
	{
		if (tc == TC_SCRIPT_YIELDABLE)
		{
			Script::current()->yield();
		}
		else if (tc == TC_OTHER)
		{
			soup::os::sleep(10);
		}
		else
		{
			SOUP_ASSERT_UNREACHABLE;
		}
	}
}