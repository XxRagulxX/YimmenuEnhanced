#include "Scripting/LuaLibrary.hpp"
#include "Scripting/LuaManager.hpp"

namespace YimMenu
{
	LuaLibrary::LuaLibrary()
	{
		LuaManager::RegisterLibrary(this);
	}
}