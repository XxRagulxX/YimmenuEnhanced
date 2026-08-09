#include "Script.hpp"

#include "ExecCtx.hpp"
#include "ScriptMgr.hpp"
#include "get_current_time_millis.hpp"
#include "ExceptionHandler.hpp"
#include "Util.hpp"

#include <soup/base.hpp>

namespace YimMenu
{
	Script::Script(script_func_t func) :
	    func(func)
	{
		fiber = CreateFiber(0, [](void* param) {static_cast<Script*>(param)->fiberFunc();},this);
	}

	Script::~Script()
	{
		if (fiber != nullptr)
		{
			DeleteFiber(fiber);
			fiber = nullptr;
		}
	}

	Script* Script::current()
	{
		return static_cast<Script*>(GetFiberData());
	}

	HANDLE Script::getModule() const
	{
		return g_script_mgr.getScriptModule(this);
	}

	bool Script::isCurrent() const noexcept
	{
		return GetCurrentFiber() == fiber;
	}

	void Script::stop()
	{
		if (fiber != nullptr)
		{
			DeleteFiber(fiber);
			fiber = nullptr;
		}
	}

	bool Script::tick()
	{
		if (fiber == nullptr)
		{
			return false;
		}

		ExecCtx::get().tc = TC_SCRIPT_YIELDABLE;

		SwitchToFiber(fiber);

		return func != nullptr;
	}

	void Script::nestedTick()
	{
		SOUP_ASSERT(ExecCtx::get().isScript());

		SOUP_ASSERT(!isCurrent());

		const auto prev_ret_fiber = ret_fiber;

		ret_fiber = GetCurrentFiber();

		tick();

		ret_fiber = prev_ret_fiber;
	}

	void Script::yield()
	{
		SwitchToFiber(ret_fiber);
	}

	void Script::yield(time_t minSleepMs)
	{
		const auto deadline = get_current_time_millis() + minSleepMs;

		do
		{
			yield();
		} while (!IS_DEADLINE_REACHED(deadline));
	}

	void Script::fiberFunc()
	{
		__try
		{
			func();
		}
		__EXCEPTIONAL()
		{
		}

		func = nullptr;

		do
		{
			yield();
		} while (true);
	}
}