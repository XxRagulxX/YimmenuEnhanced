#pragma once
#include "Commands/ListCommand.hpp"

#include <functional>
#include <utility>
#include <vector>

namespace YimMenu::StandWidgets
{
	// Ported from real Stand's own CommandLambdaListSelect - see
	// LambdaToggle.hpp's own doc comment for why this whole file exists.
	class LambdaListSelect : public ListCommand
	{
	public:
		LambdaListSelect(std::string name,
		    std::string label,
		    std::string description,
		    std::vector<std::pair<int, const char*>> list,
		    int def_val,
		    std::function<void(int)> onChange) :
		    ListCommand(std::move(name), std::move(label), std::move(description), std::move(list), def_val),
		    m_OnChange(std::move(onChange))
		{
		}

	protected:
		void OnChange() override
		{
			if (m_OnChange)
				m_OnChange(GetState());
		}

	private:
		std::function<void(int)> m_OnChange;
	};
}
