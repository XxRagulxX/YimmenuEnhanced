#pragma once
#include "Commands/IntCommand.hpp"

#include <utility>

namespace YimMenu::StandWidgets
{
	// Ported from real Stand's own CommandSliderPointer - see
	// TogglePointer.hpp's own doc comment for the shared reasoning (same
	// one-way sync, onto IntCommand::OnChange() instead of BoolCommand's
	// OnEnable()/OnDisable() - no changes to IntCommand.hpp needed
	// either).
	class SliderPointer : public IntCommand
	{
	public:
		SliderPointer(std::string name, std::string label, std::string description, int* ptr, int min, int max) :
		    IntCommand(std::move(name), std::move(label), std::move(description), min, max, ptr ? *ptr : min),
		    m_Ptr(ptr)
		{
		}

	protected:
		void OnChange() override
		{
			if (m_Ptr)
				*m_Ptr = GetState();
		}

	private:
		int* m_Ptr;
	};
}
