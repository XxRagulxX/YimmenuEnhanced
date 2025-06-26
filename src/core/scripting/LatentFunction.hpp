#pragma once
#include "LuaScript.hpp"

namespace YimMenu::Lua
{
	int LatentFunctionInternal(lua_State* state, lua_CFunction func);

	template<lua_CFunction function>
	int LatentFunction(lua_State* state)
	{
		return LatentFunctionInternal(state, function);
	}
}