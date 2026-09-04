#include "Menu/ClassicUI.hpp"
#include "Menu/Items.hpp"
#include "Commands/Commands.hpp"
#include "Commands/ListCommand.hpp"

#include <vector>

namespace YimMenu
{
	ListCommandItem::ListCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<ListCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void ListCommandItem::Draw()
	{
		if (!m_Command)
		{
			ClassicUI::Text("Unknown list!");
			return;
		}

		auto& list = m_Command->GetList();
		if (list.empty())
		{
			ClassicUI::Text(m_LabelOverride.value_or(m_Command->GetLabel()));
			return;
		}

		const int current_val = m_Command->GetState();
		std::vector<const char*> options;
		options.reserve(list.size());
		int currentIndex = 0;
		for (size_t i = 0; i < list.size(); i++)
		{
			options.push_back(list[i].second);
			if (list[i].first == current_val)
				currentIndex = static_cast<int>(i);
		}

		const auto newIndex = ClassicUI::Cycle(m_LabelOverride.value_or(m_Command->GetLabel()), options.data(), static_cast<int>(options.size()), currentIndex);
		if (newIndex != currentIndex)
			m_Command->SetState(list[static_cast<size_t>(newIndex)].first);
	}
}
