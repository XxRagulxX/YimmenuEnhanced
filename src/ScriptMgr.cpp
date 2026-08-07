#include "ScriptMgr.hpp"
#include "AsyncLogger/Logger.hpp"

namespace YimMenu
{
	//------------------------------------------------------------
	// Script Registration
	//------------------------------------------------------------

	void ScriptMgr::addScript(HMODULE module, std::unique_ptr<Script>&& script)
	{
		m_Scripts[module].emplace_back(std::move(script));
	}

	HMODULE ScriptMgr::getScriptModule(const Script* script) const
	{
		for (const auto& [module, scripts] : m_Scripts)
		{
			for (const auto& scr : scripts)
			{
				if (scr.get() == script)
				{
					return module;
				}
			}
		}

		return nullptr;
	}

	//------------------------------------------------------------
	// Script Removal
	//------------------------------------------------------------

	void ScriptMgr::removeScripts(HMODULE module)
	{
		auto it = m_Scripts.find(module);

		if (it == m_Scripts.end())
			return;

		for (auto& script : it->second)
		{
			script->stop();
		}
	}

	void ScriptMgr::removeScript(script_func_t function)
	{
		for (auto& [module, scripts] : m_Scripts)
		{
			for (auto& script : scripts)
			{
				if (script->func == function)
				{
					script->stop();
					return;
				}
			}
		}
	}

	//------------------------------------------------------------
	// Query
	//------------------------------------------------------------

	size_t ScriptMgr::getNumScripts(HMODULE module) const
	{
		auto it = m_Scripts.find(module);

		if (it == m_Scripts.end())
			return 0;

		return it->second.size();
	}

	void ScriptMgr::tick()
	{
		if (!IsThreadAFiber())
		{
			ConvertThreadToFiber(nullptr);
		}

		Script::ret_fiber = GetCurrentFiber();

		for (auto moduleIt = m_Scripts.begin(); moduleIt != m_Scripts.end();)
		{
			auto& scripts = moduleIt->second;

			for (auto scriptIt = scripts.begin(); scriptIt != scripts.end();)
			{
				if ((*scriptIt)->tick())
				{
					++scriptIt;
				}
				else
				{
					scriptIt = scripts.erase(scriptIt);
				}
			}

			if (scripts.empty())
			{
				moduleIt = m_Scripts.erase(moduleIt);
			}
			else
			{
				++moduleIt;
			}
		}
	}

	void ScriptMgr::deinit()
	{
		m_Scripts.clear();
	}
}