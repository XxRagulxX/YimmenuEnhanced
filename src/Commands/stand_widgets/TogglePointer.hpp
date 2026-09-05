#pragma once
#include "Commands/BoolCommand.hpp"

#include <utility>

namespace YimMenu::StandWidgets
{
	// Ported from real Stand's own CommandTogglePointer - a toggle backed
	// by an existing bool* (typically a static field on some manager
	// class, e.g. real Stand's own AllEntitiesEveryTick::aimbot_los_check)
	// rather than owning its own storage. Real Stand's own version reads
	// *ptr once at construction (as the initial state) and writes back to
	// it on every change - a one-way sync onto an already-virtual
	// OnEnable()/OnDisable() hook, not something needing GetState()/
	// SetState() themselves to be virtual, so this needed no changes to
	// BoolCommand.hpp at all.
	//
	// Why this matters for porting: a lot of Stand's own remaining
	// categories (Weapons > Aimbot, for one) are built entirely out of
	// CommandTogglePointer/CommandSliderPointer (see SliderPointer.hpp)
	// rows bound directly to a shared settings struct's own fields,
	// rather than each row owning independent state - this is the one
	// widget missing to port those directly instead of redesigning them
	// around independent BoolCommands.
	class TogglePointer : public BoolCommand
	{
	public:
		TogglePointer(std::string name, std::string label, std::string description, bool* ptr) :
		    BoolCommand(std::move(name), std::move(label), std::move(description), ptr && *ptr),
		    m_Ptr(ptr)
		{
		}

	protected:
		void OnEnable() override
		{
			if (m_Ptr)
				*m_Ptr = true;
		}

		void OnDisable() override
		{
			if (m_Ptr)
				*m_Ptr = false;
		}

	private:
		bool* m_Ptr;
	};
}
