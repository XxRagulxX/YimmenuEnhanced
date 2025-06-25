#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"

namespace YimMenu::Lua
{
	class Logging : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int Verbose(lua_State* state)
		{
			const char* message = luaL_checkstring(state, 1);
			LOGF(VERBOSE, "{}: {}", LuaScript::GetScript(state).GetName(), message);
			return 0;
		}

		static int Info(lua_State* state)
		{
			const char* message = luaL_checkstring(state, 1);
			LOGF(INFO, "{}: {}", LuaScript::GetScript(state).GetName(), message);
			return 0;
		}

		static int Warn(lua_State* state)
		{
			const char* message = luaL_checkstring(state, 1);
			LOGF(WARNING, "{}: {}", LuaScript::GetScript(state).GetName(), message);
			return 0;
		}

		static int Error(lua_State* state)
		{
			const char* message = luaL_checkstring(state, 1);
			LOGF(FATAL, "{}: {}", LuaScript::GetScript(state).GetName(), message);
			return 0;
		}

		static int Trace(lua_State* state)
		{
			const char* message = luaL_checkstring(state, 1);
			luaL_traceback(state, state, message, 1);
			LOGF(VERBOSE, "{}: {}", LuaScript::GetScript(state).GetName(), lua_tostring(state, -1));
			lua_pop(state, 1); // pop the traceback
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
		
			lua_pushcfunction(state, Verbose);
			lua_setfield(state, -2, "verbose");

			lua_pushcfunction(state, Info);
			lua_setfield(state, -2, "info");

			lua_pushcfunction(state, Warn);
			lua_setfield(state, -2, "warn");

			lua_pushcfunction(state, Error);
			lua_setfield(state, -2, "error");

			lua_pushcfunction(state, Trace);
			lua_setfield(state, -2, "trace");

		    lua_setglobal(state, "log");
		}
	};

	Logging _Logging;
}