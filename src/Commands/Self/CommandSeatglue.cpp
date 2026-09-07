#include "Commands/Self/CommandSeatglue.hpp"

namespace Stand::Features
{
	Stand::CommandSeatglue& GetCommandSeatglue()
	{
		static Stand::CommandSeatglue instance{nullptr};
		return instance;
	}
}
