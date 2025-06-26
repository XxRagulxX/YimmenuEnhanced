#include "LuaScript.hpp"
#include "LuaManager.hpp"

namespace YimMenu
{
	// https://github.com/brimworks/lua-ev/blob/2d11066b6f96a7501805e8c28d92f70dd2c0ab13/lua_ev.c#L144
	// TODO: may need to check if debug is a real table if ChatGPT is to be trusted
	static int ErrorHandler(lua_State* state)
	{
		auto error_msg = lua_tostring(state, 1);
		if (!error_msg)
			return 1; // return error_msg

		// ok this is the fun part
		// our stack right now: retaddr error_message <
		lua_getglobal(state, "debug");
		lua_getfield(state, -1, "traceback");
		
		lua_pushstring(state, error_msg);
		lua_pushinteger(state, 2);

		lua_call(state, 2, 1); // now the top of stack should have the stacktrace

		return 1;
	}

	bool LuaScript::CallFunction(int n_args, int n_results, lua_State* override_state)
	{
		auto state = override_state;
		if (!state)
			state = m_State;

		if (!LuaManager::IsRunningInMainThread())
		{
			LOGF(FATAL, "LuaScript::CallFunction: {} attempted to call a Lua function outside the main thread. This is not allowed", m_ModuleName);
			lua_pop(state, 1); // pop the function from the stack since we aren't going to call it
			SetMalfunctioning();
			return false;
		}

		lua_pushcfunction(state, &ErrorHandler);
		int handler_index = lua_gettop(state) - n_args - 1;
		lua_insert(state, handler_index); // move it before all the args

		auto result = lua_pcall(state, n_args, n_results, handler_index);

		if (result == LUA_OK)
		{
			// the lua runtime doesn't pop the handler if there's no error
			lua_remove(state, handler_index); // TODO: does this actually work? What happens if your function returns stuff?
			return true;
		}
		else
		{
			auto trace = lua_tostring(state, -1);
			LOGF(FATAL, "{}: {}", m_ModuleName, trace);
			lua_pop(state, 1); // pop the stack trace
			SetMalfunctioning();
			return false;
		}
	}

	int LuaScript::ResumeCoroutine(int n_args, int n_results, lua_State* coro_state)
	{
		if (!LuaManager::IsRunningInMainThread())
		{
			LOGF(FATAL, "LuaScript::ResumeCoroutine: {} attempted to resume a Lua coroutine outside the main thread. This is not allowed", m_ModuleName);
			SetMalfunctioning();
			return LUA_ERRRUN;
		}

		auto result = lua_resume(coro_state, n_args);
		if (result == LUA_OK || result == LUA_YIELD)
		{
			// move returns to the main stack

			auto num_rets = lua_gettop(coro_state);
			if (num_rets != n_results && result == LUA_YIELD)
			{
				LOGF(FATAL, "LuaScript::ResumeCoroutine: {} yielded {} values when code expected {} values to be yielded", m_ModuleName, num_rets, n_results);
				SetMalfunctioning();
				return LUA_ERRRUN;
			}

			if (num_rets)
				lua_xmove(coro_state, m_State, num_rets);
		}
		else
		{
			// there would be an error object on the top of stack
			std::string error_msg = lua_tostring(coro_state, -1);
			lua_pop(coro_state, 1);

			// traceback
			luaL_traceback(coro_state, coro_state, error_msg.c_str(), 1);
			LOGF(FATAL, "{}: {}", m_ModuleName, lua_tostring(coro_state, -1));
			lua_pop(coro_state, 1);
	
			SetMalfunctioning();
		}

		return result;
	}

	void LuaScript::RemoveScriptCallback(ScriptCallback& callback)
	{
		luaL_unref(m_State, LUA_REGISTRYINDEX, callback.m_Coroutine);
		if (callback.m_Fiber)
			DeleteFiber(callback.m_Fiber);
	}

	LuaScript::LuaScript(std::string_view file_name) :
	    m_FileName(file_name),
	    m_ModuleName(std::filesystem::path(file_name).filename().string())
	{
		m_State = luaL_newstate();
		
		lua_pushlightuserdata(m_State, (void*)this);  
		lua_setfield(m_State, LUA_REGISTRYINDEX, "context");

		LuaManager::LoadLibraries(m_State);

		if (luaL_loadfilex(m_State, file_name.data(), "t") != LUA_OK) // don't load binary chunks
		{
			auto error = lua_tostring(m_State, -1);
			LOGF(FATAL, "{}: {}", m_ModuleName, error);
			SetMalfunctioning();
			return;
		}

		// we should have a function in the top of stack
		CallFunction(0, 0);
		m_LoadState = LoadState::RUNNING;
	}

	LuaScript::~LuaScript()
	{
		if (m_State)
		{
			lua_close(m_State);
			m_State = nullptr;
		}
	}

	bool LuaScript::SafeToUnload()
	{
		for (auto& callback : m_ScriptCallbacks)
			if (callback.m_LastYieldFromCode)
				return false; // don't unload if we're calling a latent function

		return true;
	}

	LuaScript& LuaScript::GetScript(lua_State* state)
	{
		lua_getfield(state, LUA_REGISTRYINDEX, "context");
		auto script = static_cast<LuaScript*>(lua_touserdata(state, -1));
		lua_pop(state, 1);
		return *script;
	}

	void LuaScript::AddScriptCallback(int coro_handle)
	{
		ScriptCallback callback;
		callback.m_Coroutine = coro_handle;
		callback.m_LastYieldFromCode = false;
		callback.m_TimeToResume = std::nullopt;
		callback.m_Fiber = nullptr;
		callback.m_ParentFiber = nullptr;
		callback.m_LatentTarget = nullptr;

		// we don't want to push any additional callbacks to the main array when we're in the middle of running, and potentially deleting, them
		if (m_RunningScriptCallbacks)
			m_QueuedScriptCallbacks.push_back(callback);
		else
			m_ScriptCallbacks.push_back(callback);
	}

	void LuaScript::Yield(lua_State* state, int millis, bool from_code)
	{
		lua_pushinteger(state, millis);
		lua_pushboolean(state, from_code);
		lua_yield(state, 2);
	}

	void LuaScript::Tick()
	{
		m_RunningScriptCallbacks = true;
		std::erase_if(m_ScriptCallbacks, [this](ScriptCallback& callback) {
			if (callback.m_TimeToResume && *callback.m_TimeToResume > std::chrono::high_resolution_clock::now())
				return false;

			lua_rawgeti(m_State, LUA_REGISTRYINDEX, callback.m_Coroutine);
			lua_State* coro_state = lua_tothread(m_State, -1);
			lua_pop(m_State, 1);

			auto state = ResumeCoroutine(0, 2, coro_state);

			if (state != LUA_YIELD)
			{
				RemoveScriptCallback(callback);
				return true;
			}

			auto time = lua_tointeger(m_State, -2);
			auto from_code = lua_toboolean(m_State, -1);
			lua_pop(m_State, 2);

			if (time == 0)
			{
				callback.m_TimeToResume = std::nullopt;
			}
			else
			{
				callback.m_TimeToResume = std::chrono::high_resolution_clock::now() + std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::milliseconds(static_cast<std::uint64_t>(time)));
			}
			callback.m_LastYieldFromCode = from_code;

			return false;
		});
		m_RunningScriptCallbacks = false;
		
		std::ranges::move(m_QueuedScriptCallbacks, std::back_inserter(m_ScriptCallbacks));
		m_QueuedScriptCallbacks.clear();
	}
}