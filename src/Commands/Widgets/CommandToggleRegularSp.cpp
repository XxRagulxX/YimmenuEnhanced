#include "Commands/Widgets/CommandToggleRegularSp.hpp"

#include "Network/is_session.hpp"

namespace Stand
{
	bool CommandToggleRegularSp::checkPermissions(Click& click) noexcept
	{
		return m_on == default_on || click.isRegularEditionOrSp();
	}

	bool CommandToggleRegularSp::checkPermissions() noexcept
	{
		return !is_session_or_transition_active();
	}
}
