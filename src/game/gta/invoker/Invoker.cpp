#include "Invoker.hpp"

#include "Crossmap.hpp"
#include "game/pointers/Pointers.hpp"

#include "types/script/scrProgram.hpp"

namespace YimMenu
{
	void NativeInvoker::DefaultHandler(rage::scrNativeCallContext* ctx)
	{
		LOG(FATAL) << "Native handler not registered";
		ctx->SetReturnValue(0);
	}

	void NativeInvoker::CacheHandlers()
	{
		if (m_AreHandlersCached)
			return;

		memcpy(m_Handlers.data(), g_Crossmap.data(), sizeof(g_Crossmap));
		auto program = reinterpret_cast<rage::scrProgram*>(calloc(1, sizeof(rage::scrProgram)));
		program->m_NativeCount = m_Handlers.size();
		program->m_NativeEntrypoints = m_Handlers.data();
		Pointers.PopulateNatives(program);
		free(program);
		m_AreHandlersCached = true;
	}
}