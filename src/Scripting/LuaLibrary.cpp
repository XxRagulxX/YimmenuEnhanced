#include "Scripting/LuaLibrary.hpp"
#include "Scripting/LuaManager.hpp"

namespace StandEnhanced
{
	LuaLibrary::LuaLibrary()
	{
		LuaManager::RegisterLibrary(this);
	}
}