#include "Rendering/ScriptsGrid.hpp"

#include "Rendering/StartScriptGrid.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/ThreadsGrid.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		// Owned here rather than in MenuGrid.cpp - see SelfGrid.cpp's
		// identical note about WeaponsGrid. Each already hardcodes its
		// own origin below where this Grid's own tab strip draws - see
		// their own class comments.
		ThreadsGrid g_ThreadsContent{};
		StartScriptGrid g_StartScriptContent{};
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). This Grid's own item list is just the
	// tab strip below - everything else lives in whichever target is
	// active.
	ScriptsGrid::ScriptsGrid() :
	    GridTabbed(1438, 587, 3)
	{
	}

	void ScriptsGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		InitTabs(items_draft,
		    static_cast<int16_t>(Theme::kContentItemHeight),
		    {"Threads", "Start Script"},
		    {&g_ThreadsContent, &g_StartScriptContent});
	}
}
