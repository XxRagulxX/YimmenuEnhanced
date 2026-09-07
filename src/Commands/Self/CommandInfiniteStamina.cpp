#include "Commands/Self/CommandInfiniteStamina.hpp"

namespace Stand::Features
{
	Stand::CommandInfiniteStamina& GetCommandInfiniteStamina()
	{
		static Stand::CommandInfiniteStamina instance{nullptr};
		return instance;
	}
}
