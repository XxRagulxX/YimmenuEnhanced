#pragma once
#include "lua.hpp"

namespace YimMenu
{
	class LuaScript
	{
		lua_State* m_State;
		std::string m_FileName;
		std::string m_ModuleName;
		bool m_IsMalfunctioning; // when this is set to true, the script will be unloaded next tick
		bool m_IsValid;

		// Calls the function at the top of stack. If this returns false the stack would have nothing on it
		bool CallFunction(int n_args, int n_results);

	public:
		LuaScript(std::string_view file_name);
		~LuaScript();

		bool IsMalfunctioning() const
		{
			return m_IsMalfunctioning;
		}

		bool IsValid() const
		{
			return m_IsValid;
		}

		void Invalidate()
		{
			m_IsValid = false;
		}

		void SetMalfunctioning()
		{
			m_IsMalfunctioning = true;
		}

		std::string_view GetName()
		{
			return m_ModuleName;
		}

		// we're guaranteed to have a LuaScript for each lua_State, so we can return it as a reference
		static LuaScript& GetScript(lua_State* state);
	};
}