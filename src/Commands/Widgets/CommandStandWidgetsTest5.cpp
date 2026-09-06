#include "Commands/Widgets/CommandStandWidgetsTest5.hpp"

#include "Commands/Widgets/CommandToggle.hpp"
#include "Menu/Click.hpp"
#include "World/Self.hpp"

namespace YimMenu::Features
{
	namespace
	{
		// Ported from real Stand's own CommandGod - pasted by the user
		// as the exact target shape every command should end up in once
		// migrated (constructor taking CommandList* parent + LOC()
		// name/help text/CMDNAMES() aliases, onEnable()/onDisable()
		// doing the actual work). Reuses this project's own existing
		// Self::GetPed().SetInvincible() - the same native call this
		// project's own CommandGodmode.cpp (a YimMenu::LoopedCommand,
		// kept running unmodified and independently for now) already
		// uses - rather than reimplementing the behaviour a second way.
		// No LOC() translation database exists here (see Util/Label.hpp's
		// own comment) so LOC(...) just becomes the literal text passed
		// to it, same as real Stand's own LOC() would once resolved.
		class CommandGod : public Stand::CommandToggle
		{
		public:
			explicit CommandGod(Stand::CommandList* parent) :
			    Stand::CommandToggle(parent,
			        LOC("God Mode (Stand Test)"),
			        CMDNAMES("standtest_godmode", "standtest_immortality"),
			        LOC("Makes your character unable to die."))
			{
			}

			void onEnable(Stand::Click& click) override
			{
				if (Self::GetPed())
					Self::GetPed().SetInvincible(true);
			}

			void onDisable(Stand::Click& click) override
			{
				if (Self::GetPed())
					Self::GetPed().SetInvincible(false);
			}
		};
	}

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
		static bool initialized = [] {
			root.createChild<CommandGod>();
			return true;
		}();
		(void)initialized;

		return root;
	}
}
