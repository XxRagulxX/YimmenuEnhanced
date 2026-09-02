#include "Scripting/LuaResource.hpp"
#include "Scripting/LuaManager.hpp"

namespace YimMenu
{
	void LuaResourceType::Register()
	{
		m_Index = LuaManager::RegisterResourceType(this);
	}
}