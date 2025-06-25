#include "LuaManager.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu
{
	void LuaManager::RegisterLibraryImpl(LuaLibrary* library)
	{
		m_Libraries.push_back(library);
	}

	void LuaManager::LoadLibrariesImpl(lua_State* state)
	{
		for (auto library : m_Libraries)
			library->Register(state);
	}

	void LuaManager::LoadScriptImpl(std::string path)
	{
		std::lock_guard lock(m_LoadMutex);
		m_ScriptsToLoad.push(path);
	}

	void LuaManager::RunScriptImpl()
	{
		m_MainThreadId = GetCurrentThreadId();

		auto scripts_dir = FileMgr::GetProjectFolder("./scripts");
		for (const auto& entry : std::filesystem::directory_iterator(scripts_dir.Path()))
		{
			if (entry.path().extension() != ".lua")
				continue;

			m_ScriptsToLoad.push(entry.path().string());
		}

		while (g_Running)
		{
			{
				// 1) process new load requests
				std::lock_guard lock(m_LoadMutex);
				while (!m_ScriptsToLoad.empty())
				{
					m_LoadedScripts.push_back(std::make_shared<LuaScript>(m_ScriptsToLoad.front()));
					m_ScriptsToLoad.pop();
				}

				// 2) remove malfunctioning scripts
				std::erase_if(m_LoadedScripts, [](auto& script) {
					auto is_malfunctioning = script->IsMalfunctioning();
					if (is_malfunctioning)
					{
						script->Invalidate();
						Notifications::Show("Lua Scripting", std::format("Script {} has been unloaded due to a malfunction", script->GetName()), NotificationType::Warning);
						return true;
					}

					return false;
				});
			}

			// 3) run tick coroutines
			{
				// TODO!
			}
			ScriptMgr::Yield();
		}
	}

	bool LuaManager::IsRunningInMainThreadImpl()
	{
		return GetCurrentThreadId() == m_MainThreadId;
	}
}