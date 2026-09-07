#pragma once
#include "Commands/Widgets/CommandSlider.hpp"

#include "World/Self.hpp"

namespace Stand
{
	class CommandWanted : public CommandSlider
	{
	public:
		explicit CommandWanted(CommandList* parent) :
		    CommandSlider(parent, LIT("Set Wanted Level"), CMDNAMES("wanted", "wantedlevel", "wantedslider"), NOLABEL, 0, 5, 0)
		{
		}

		void onChange(Click& click, int prev_value) override
		{
			CommandSlider::onChange(click, prev_value);

			click.ensureScriptThread([this] {
				if (auto player = Stand::Self::GetPlayer())
					player.SetWantedLevel(value);
			});
		}
	};
}

namespace Stand::Features
{
	Stand::CommandWanted& GetCommandWanted();
}
