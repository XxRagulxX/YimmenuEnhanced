#include "MenuDebug.hpp"
#include "Misc.hpp"
#include "Globals.hpp"
#include "Locals.hpp"
#include "MenuScripts.hpp"

namespace YimMenu::Submenus
{
	Debug::Debug() :
		#define ICON_FA_ARROW_RIGHT "\xef\x84\xa0"
	    Submenu::Submenu("Debug", ICON_FA_ARROW_RIGHT)
	{
		AddCategory(BuildMiscMenu());
		AddCategory(BuildGlobalsMenu());
		AddCategory(BuildLocalsMenu());
		AddCategory(BuildScriptsMenu());
	}
}