#include "BaseHook.hpp"

namespace YimMenu
{
	BaseHook::BaseHook(std::string_view name) :
	    m_Name(name),
	    m_Enabled(false)
	{
	}
}