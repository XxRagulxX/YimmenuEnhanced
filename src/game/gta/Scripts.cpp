#include "Scripts.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/rage/atArray.hpp"
#include "types/rage/tlsContext.hpp"
#include "types/script/GtaThread.hpp"
#include "types/script/CGameScriptHandler.hpp"
#include "types/script/CGameScriptId.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Scripts
{
	rage::scrThread* FindScriptThread(joaat_t hash)
	{
		for (auto& thread : *Pointers.ScriptThreads)
		{
			if (thread && thread->m_Context.m_ThreadId && thread->m_ScriptHash == hash)
			{
				return thread;
			}
		}

		return nullptr;
	}


	void RunAsScript(rage::scrThread* thread, std::function<void()> callback)
	{
		auto og_thread = rage::tlsContext::Get()->m_CurrentScriptThread;
		auto og_running_in_scrthread = rage::tlsContext::Get()->m_ScriptThreadActive;
		rage::tlsContext::Get()->m_CurrentScriptThread = thread;
		rage::tlsContext::Get()->m_ScriptThreadActive = true;
		callback();
		rage::tlsContext::Get()->m_ScriptThreadActive = og_running_in_scrthread;
		rage::tlsContext::Get()->m_CurrentScriptThread = og_thread;
	}

	void RunWithSpoofedThreadName(std::uint32_t name, std::function<void()> callback)
	{
		if (auto thread = reinterpret_cast<GtaThread*>(rage::tlsContext::Get()->m_CurrentScriptThread))
		{
			auto hash_1 = thread->m_Context.m_ScriptHash;
			auto hash_2 = thread->m_ScriptHash;
			auto hash_3 = thread->m_ScriptHash2;
			std::optional<std::uint32_t> hash_4;
			if (auto handler = thread->m_ScriptHandler)
				hash_4 = handler->GetId()->m_Hash;

			thread->m_Context.m_ScriptHash = name;
			thread->m_ScriptHash = name;
			thread->m_ScriptHash2 = name;
			if (hash_4)
				thread->m_ScriptHandler->GetId()->m_Hash = name;

			callback();

			thread->m_Context.m_ScriptHash = hash_1;
			thread->m_ScriptHash = hash_2;
			thread->m_ScriptHash2 = hash_3;
			if (hash_4)
				thread->m_ScriptHandler->GetId()->m_Hash = *hash_4;
		}
	}

	bool SafeToModifyFreemodeBroadcastGlobals()
	{
		if (!*Pointers.IsSessionStarted)
			return false;

		if (!FindScriptThread("freemode"_J))
			return false;

		if (auto gpbd = GlobalPlayerBD::Get())
		{
			return gpbd->Entries[Self::GetPlayer().GetId()].FreemodeState == eFreemodeState::RUNNING;
		}

		return false;
	}
}