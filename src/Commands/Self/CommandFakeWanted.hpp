#pragma once
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandSlider.hpp"

#include "Scripting/Natives.hpp"

namespace Stand
{
	class CommandFakeWanted : public CommandSlider
	{
	public:
		explicit CommandFakeWanted(CommandList* parent) :
		    CommandSlider(parent, LIT("Fake Wanted"), CMDNAMES("fakewantedlevel", "fakewanted"), LIT("Shows wanted stars on the HUD without actually being wanted"), 0, 6, 0)
		{
		}

		void onChange(Click& click, int prev_value) override
		{
			CommandSlider::onChange(click, prev_value);

			click.ensureScriptThread([this] {
				MISC::SET_FAKE_WANTED_LEVEL(value);

				if (value > 0)
					CommandTickDispatch::AddCommand(this);
				else
					CommandTickDispatch::RemoveCommand(this);
			});
		}

		void onTick() override
		{
			MISC::SET_FAKE_WANTED_LEVEL(value);
		}

		~CommandFakeWanted() override
		{
			CommandTickDispatch::RemoveCommand(this);
		}
	};
}

namespace Stand::Features
{
	Stand::CommandFakeWanted& GetCommandFakeWanted();
}
