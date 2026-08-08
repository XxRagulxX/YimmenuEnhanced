#include "DetourHook.hpp"
#include "NodeHooks.hpp"
#include "Hooks.hpp"
#include "Nodes.hpp"

#include "datBitBuffer.hpp"

namespace YimMenu::Hooks
{
	void Spoofing::WriteNodeData(CProjectBaseSyncDataNode* node, rage::netObject* object, rage::datBitBuffer* buffer, void* logger, bool update)
	{
		auto orig_buffer = *buffer;
		bool node_dirty = false;
		Nodes::Init();

		BaseHook::Get<Spoofing::WriteNodeData, DetourHook>()->Original<decltype(&Spoofing::WriteNodeData)>()(node, object, buffer, logger, update);

		if (NodeHooks::ModifyNodeData(node, object))
			node_dirty = true;

		if (node_dirty)
		{
			*buffer = orig_buffer;
			BaseHook::Get<Spoofing::WriteNodeData, DetourHook>()->Original<decltype(&Spoofing::WriteNodeData)>()(node, object, buffer, logger, false);
		}
	}
}