#include "Commands/Self/CommandParalock.hpp"

namespace Stand::Features
{
	Stand::CommandParalock& GetCommandParalock()
	{
		static Stand::CommandParalock instance{nullptr};
		return instance;
	}
}
