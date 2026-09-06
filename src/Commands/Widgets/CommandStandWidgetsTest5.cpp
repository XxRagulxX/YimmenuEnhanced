#include "Commands/Widgets/CommandStandWidgetsTest5.hpp"

#include "Commands/Widgets/CommandToggle.hpp"
#include "Menu/Click.hpp"
#include "World/Self.hpp"

// CommandGod lives directly in namespace Stand (not YimMenu::Features) -
// matching where the user's own pasted reference example was written.
// CommandName/Label/CommandList/CommandToggle/Click/LOC()/CMDNAMES() all
// resolve unqualified only from inside namespace Stand itself (or a
// namespace nested under it) - writing this class inside
// YimMenu::Features instead (the original mistake here) left every one
// of those unqualified names unable to find Stand::CommandName et al.,
// since YimMenu::Features and Stand are unrelated sibling namespace
// trees, not parent/child.
namespace Stand
{
	namespace
	{
		// Ported from real Stand's own CommandGod - pasted by the user
		// as the exact target shape every command should end up in once
		// migrated (constructor taking CommandList* parent + LOC()
		// name/help text/CMDNAMES() aliases, onEnable()/onDisable()
		// doing the actual work). Reuses this project's own existing
		// YimMenu::Self::GetPed().SetInvincible() - the same native call
		// this project's own CommandGodmode.cpp (a YimMenu::LoopedCommand,
		// kept running unmodified and independently for now) already
		// uses - rather than reimplementing the behaviour a second way.
		// No LOC() translation database exists here (see Util/Label.hpp's
		// own comment) so LOC(...) just becomes the literal text passed
		// to it, same as real Stand's own LOC() would once resolved.
		class CommandGod : public CommandToggle
		{
		public:
			explicit CommandGod(CommandList* parent) :
			    CommandToggle(parent,
			        LOC("God Mode (Stand Test)"),
			        CMDNAMES("standtest_godmode", "standtest_immortality"),
			        LOC("Makes your character unable to die."))
			{
			}

			void onEnable(Click& click) override
			{
				if (YimMenu::Self::GetPed())
					YimMenu::Self::GetPed().SetInvincible(true);
			}

			void onDisable(Click& click) override
			{
				if (YimMenu::Self::GetPed())
					YimMenu::Self::GetPed().SetInvincible(false);
			}
		};
	}
}

namespace YimMenu::Features
{
	Stand::CommandList& GetStandTreeTestRoot()
	{
		static Stand::CommandList root{nullptr, LOC("Stand Tree Test")};
		// Built lazily, once, the first time this is reached - a plain
		// file-scope static Stand::CommandList would try to construct
		// its own child at static-init time via createChild<CommandGod>(),
		// before FiberPool/other statics this eventually touches are
		// necessarily ready; deferring the child's own construction to
		// first real use (same "lazy static" idiom this project's own
		// Commands::GetInstance()/Notifications::GetInstance() already
		// use) avoids that ordering risk.
		//
		// Stand::CommandGod, not just CommandGod - it's declared inside
		// an anonymous namespace nested under namespace Stand above, not
		// under YimMenu::Features, so it needs that qualifier from here.
		static bool initialized = [] {
			root.createChild<Stand::CommandGod>();
			return true;
		}();
		(void)initialized;

		return root;
	}
}
