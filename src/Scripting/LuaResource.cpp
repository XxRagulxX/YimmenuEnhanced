#include "Scripting/LuaResource.hpp"
#include "Scripting/LuaManager.hpp"

namespace StandEnhanced
{
	void LuaResourceType::Register()
	{
		m_Index = LuaManager::RegisterResourceType(this);
	}
}