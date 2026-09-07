#include "Commands/Self/CommandRespawnRecall.hpp"

namespace Stand::Features
{
	Stand::CommandRespawnRecall& GetCommandRespawnRecall()
	{
		static Stand::CommandRespawnRecall instance{nullptr};
		return instance;
	}
}
