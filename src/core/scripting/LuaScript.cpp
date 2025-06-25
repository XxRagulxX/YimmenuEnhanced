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

	bool LuaScript::CallFunction(int n_args, int n_results)
	{
		if (!LuaManager::IsRunningInMainThread())
		{
			LOGF(FATAL, "LuaScript::CallFunction: {} attempted to call a Lua function outside the main thread. This is not allowed", m_ModuleName);
			lua_pop(m_State, 1); // pop the function from the stack since we aren't going to call it
			SetMalfunctioning();
			return false;
		}

		lua_pushcfunction(m_State, &ErrorHandler);
		int handler_index = lua_gettop(m_State) - n_args - 1;
		lua_insert(m_State, handler_index); // move it before all the args

		auto result = lua_pcall(m_State, n_args, n_results, handler_index);

		if (result == LUA_OK)
		{
			// the lua runtime doesn't pop the handler if there's no error
			lua_remove(m_State, handler_index); // TODO: does this actually work? What happens if your function returns stuff?
			return true;
		}
		else
		{
			auto trace = lua_tostring(m_State, -1);
			LOGF(FATAL, "{}: {}", m_ModuleName, trace);
			lua_pop(m_State, 1); // pop the stack trace
			SetMalfunctioning();
			return false;
		}
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
		m_IsValid = true;
	}

	LuaScript::~LuaScript()
	{
		if (m_State)
		{
			lua_close(m_State);
			m_State = nullptr;
		}
	}

	LuaScript& LuaScript::GetScript(lua_State* state)
	{
		lua_getfield(state, LUA_REGISTRYINDEX, "context");
		auto script = static_cast<LuaScript*>(lua_touserdata(state, -1));
		lua_pop(state, 1);
		return *script;
	}
}