#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <Windows.h>

#include "Script.hpp"

namespace YimMenu
{
	class ScriptMgr
	{
	public:
		ScriptMgr() = default;
		~ScriptMgr() = default;

		ScriptMgr(const ScriptMgr&) = delete;
		ScriptMgr& operator=(const ScriptMgr&) = delete;
		ScriptMgr(ScriptMgr&&) = delete;
		ScriptMgr& operator=(ScriptMgr&&) = delete;

		//============================================================
		// Stand Runtime
		//============================================================

		void addScript(HMODULE module, std::unique_ptr<Script>&& script);

		[[nodiscard]]
		HMODULE getScriptModule(const Script* script) const;

		void removeScripts(HMODULE module);

		void removeScript(script_func_t function);

		[[nodiscard]]
		size_t getNumScripts(HMODULE module) const;

		void tick();

		void deinit();

	private:
		std::unordered_map<
		    HMODULE,
		    std::vector<std::unique_ptr<Script>>>
		    m_Scripts;
	};

	inline ScriptMgr g_script_mgr;
}