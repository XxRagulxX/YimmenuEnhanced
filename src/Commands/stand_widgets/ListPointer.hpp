#pragma once
#include "Commands/ListCommand.hpp"

#include <utility>
#include <vector>

namespace YimMenu::StandWidgets
{
	// Ported from real Stand's own CommandListSelectPointer - the
	// ListCommand equivalent of TogglePointer.hpp/SliderPointer.hpp (see
	// either's own doc comment for the shared reasoning: a one-way sync
	// onto ListCommand's own OnChange() hook, no changes to
	// ListCommand.hpp needed).
	class ListPointer : public ListCommand
	{
	public:
		ListPointer(std::string name,
		    std::string label,
		    std::string description,
		    std::vector<std::pair<int, const char*>> list,
		    int* ptr) :
		    ListCommand(std::move(name), std::move(label), std::move(description), std::move(list), ptr ? *ptr : 0),
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
