#include "Commands/Self/CommandWanted.hpp"

namespace Stand::Features
{
	Stand::CommandWanted& GetCommandWanted()
	{
		static Stand::CommandWanted instance{nullptr};
		return instance;
	}
}
