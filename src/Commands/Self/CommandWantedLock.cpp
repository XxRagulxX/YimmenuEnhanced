#include "Commands/Self/CommandWantedLock.hpp"

namespace Stand::Features
{
	Stand::CommandWantedLock& GetCommandWantedLock()
	{
		static Stand::CommandWantedLock instance{nullptr, &GetCommandWanted()};
		return instance;
	}
}
