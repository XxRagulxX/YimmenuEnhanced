#include "Commands/Self/CommandFakeWanted.hpp"

namespace Stand::Features
{
	Stand::CommandFakeWanted& GetCommandFakeWanted()
	{
		static Stand::CommandFakeWanted instance{nullptr};
		return instance;
	}
}
