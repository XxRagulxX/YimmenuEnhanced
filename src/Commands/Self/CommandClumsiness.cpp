#include "Commands/Self/CommandClumsiness.hpp"

namespace Stand::Features
{
	Stand::CommandClumsiness& GetCommandClumsiness()
	{
		static Stand::CommandClumsiness instance{nullptr, &GetCommandGrace()};
		return instance;
	}
}
