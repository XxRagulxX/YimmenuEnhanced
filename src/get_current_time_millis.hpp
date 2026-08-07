#pragma once

#include "typedecl.hpp"

namespace YimMenu
{
	[[nodiscard]]
	extern time_t get_current_time_millis() noexcept;
}

#define GET_MILLIS_SINCE(since) (::YimMenu::get_current_time_millis() - (since))
#define IS_DEADLINE_REACHED(deadline) (::YimMenu::get_current_time_millis() >= (deadline))