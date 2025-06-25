#pragma once
#include "LuaScript.hpp"
#include "LuaLibrary.hpp"

namespace YimMenu
{
	// note to future self: Lua is a horrible language and should never be used
	class LuaManager
	{
	public:
		enum class ScriptPermission
		{
		};

	private:
		std::vector<std::shared_ptr<LuaScript>> m_LoadedScripts;
		std::vector<LuaLibrary*> m_Libraries;
		std::queue<std::string> m_ScriptsToLoad;
		std::mutex m_LoadMutex;
		std::uint32_t m_MainThreadId;

		void RegisterLibraryImpl(LuaLibrary* library);
		void LoadLibrariesImpl(lua_State* state);
		void LoadScriptImpl(std::string path);
		void RunScriptImpl();
		bool IsRunningInMainThreadImpl();

		static LuaManager& GetInstance()
		{
			static LuaManager instance;
			return instance;
		}

	public:
		static void RegisterLibrary(LuaLibrary* library)
		{
			GetInstance().RegisterLibraryImpl(library);
		}

		static void LoadLibraries(lua_State* state)
		{
			GetInstance().LoadLibrariesImpl(state);
		}

		static void LoadScript(std::string file_name)
		{
			GetInstance().LoadScriptImpl(file_name);
		}

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool IsRunningInMainThread()
		{
			return GetInstance().IsRunningInMainThreadImpl();
		}
	};
}