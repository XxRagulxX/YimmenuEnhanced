#pragma once
#include "Commands/Self/CommandWanted.hpp"
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandToggle.hpp"

#include "Scripting/Natives.hpp"
#include "World/Self.hpp"

namespace Stand
{
	class CommandWantedLock : public CommandToggle
	{
	public:
		explicit CommandWantedLock(CommandList* parent, CommandWanted* wantedSlider) :
		    CommandToggle(parent, LIT("Lock Wanted Level"), CMDNAMES("lockwantedlevel", "wantedlock", "freezewanted")),
		    m_WantedSlider(wantedSlider)
		{
		}

		void onEnable(Click& click) override
		{
			CommandTickDispatch::AddCommand(this);
			onTick();
		}

		void onDisable(Click& click) override
		{
			CommandTickDispatch::RemoveCommand(this);

			if (m_WantedSlider->value == 0)
				PLAYER::SET_MAX_WANTED_LEVEL(5);
		}

		void onTick() override
		{
			if (Stand::Self::GetPlayer().GetWantedLevel() != m_WantedSlider->value)
				Stand::Self::GetPlayer().SetWantedLevel(m_WantedSlider->value);

			PLAYER::SET_MAX_WANTED_LEVEL(m_WantedSlider->value == 0 ? 0 : 5);
		}

		~CommandWantedLock() override
		{
			CommandTickDispatch::RemoveCommand(this);
		}

	private:
		CommandWanted* m_WantedSlider;
	};
}

namespace Stand::Features
{
	Stand::CommandWantedLock& GetCommandWantedLock();
}
