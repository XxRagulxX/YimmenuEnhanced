#pragma once

#include "Game/typedecl.hpp"

namespace StandEnhanced
{
	[[nodiscard]]
	extern time_t get_current_time_millis() noexcept;
}

#define GET_MILLIS_SINCE(since) (::StandEnhanced::get_current_time_millis() - (since))
#define IS_DEADLINE_REACHED(deadline) (::StandEnhanced::get_current_time_millis() >= (deadline))