#include "Util/get_root_list.hpp"

#include "lib/soup/ObfusString.hpp"

#include "Commands/Widgets/CommandAction.hpp"
#include "Commands/Widgets/CommandLambdaAction.hpp"
#include "Commands/Widgets/CommandReadonlyLink.hpp"
#include "Core/Exceptional.hpp"
#include "Rendering/Gui.hpp"
#include "Network/is_session.hpp"
#include "Rendering/Renderer.hpp"
#include "Core/RootNameMgr.hpp"
#include "Util/Util.hpp"

#include "Core/FileLogger.hpp"

#include "Commands/Self/CommandTabSelf.hpp"
#include "Commands/Vehicle/CommandTabVehicle.hpp"
#include "Commands/Stand/CommandTabOnline.hpp"
#include "Commands/Player/CommandTabPlayers.hpp"
#include "Commands/World/CommandTabWorld.hpp"
#include "Commands/Stand/CommandTabGame.hpp"
#include "Commands/Stand/CommandTabStand.hpp"

#include "Commands/Widgets/CommandDummy.hpp"
#include "Commands/Stand/CommandHotkeyAdd.hpp"
#include "Commands/Stand/CommandHotkeyRemove.hpp"
#include "Commands/Widgets/CommandWait.hpp"

namespace Stand
{

	template <typename T>
	static T* createTabExceptional(CommandList* const root)
	{
		T* const tab = root->createChild<T>();
		__try
		{
			tab->populate();
		}
		__EXCEPTIONAL()
		{
		}
		return tab;
	}

CommandList* get_root_list() // OBFUS!
{
    // Keep the normal root-state calculation.
    if (g_gui.minimal)
    {
        g_gui.root_state = GUI_MINIMAL;
    }
    else
    {
        // Do not bypass the license/root-state logic here.
        //
        // Restore/use the project's normal root-state determination
        // rather than forcing GUI_FREE or GUI_ULTIMATE.
        g_gui.root_state = GUI_FREEONLINE;

        if (!g_gui.killswitched
            && g_gui.root_state == GUI_FREEONLINE
            && !is_session_or_transition_active())
        {
            g_gui.root_state = GUI_FREE;
        }
    }

    g_logger.log(fmt::format(
        "get_root_list(): root_state={}",
        static_cast<int>(g_gui.root_state)
    ));

    auto* root = new CommandList(
        nullptr,
        LIT(RootNameMgr::getCurrentRootNameForState())
    );

    g_logger.log("ROOT: created CommandList");

    if (g_gui.isRootStateFull())
    {
        g_logger.log("ROOT: Self BEGIN");
        createTabExceptional<CommandTabSelf>(root);
        g_logger.log("ROOT: Self END");

        g_logger.log("ROOT: Vehicle BEGIN");
        createTabExceptional<CommandTabVehicle>(root);
        g_logger.log("ROOT: Vehicle END");
    }

    g_logger.log("ROOT: Online BEGIN");
    createTabExceptional<CommandTabOnline>(root);
    g_logger.log("ROOT: Online END");

    if (g_gui.doesRootStateAllowPlayerList())
    {
        g_logger.log("ROOT: Players BEGIN");
        g_gui.player_list =
            createTabExceptional<CommandTabPlayers>(root);
        g_logger.log("ROOT: Players END");
    }

    if (g_gui.isRootStateFull())
    {
        g_logger.log("ROOT: World BEGIN");
        createTabExceptional<CommandTabWorld>(root);
        g_logger.log("ROOT: World END");
    }

    g_logger.log("ROOT: Game BEGIN");
    createTabExceptional<CommandTabGame>(root);
    g_logger.log("ROOT: Game END");

    if (g_gui.root_state != GUI_MINIMAL)
    {
        g_logger.log("ROOT: Stand BEGIN");
        createTabExceptional<CommandTabStand>(root);
        g_logger.log("ROOT: Stand END");

        g_gui.pseudo_commands->createChild<CommandDummy>();
        g_gui.pseudo_commands->createChild<CommandHotkeyAdd>();
        g_gui.pseudo_commands->createChild<CommandHotkeyRemove>();
        g_gui.pseudo_commands->createChild<CommandWait>();
    }

    g_logger.log("ROOT: get_root_list() COMPLETE");

    return root;
}
}
