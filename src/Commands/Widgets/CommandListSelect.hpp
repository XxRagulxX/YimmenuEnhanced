#pragma once
#include "Commands/Widgets/CommandPhysical.hpp"
#include "Menu/Click.hpp"

#include <string>
#include <utility>
#include <vector>

namespace Stand
{
	class CommandListSelect : public CommandPhysical
	{
	public:
		std::vector<std::pair<int, Label>> options;
		int value;
		int default_value;

		explicit CommandListSelect(CommandList* parent, Label&& menu_name, std::vector<CommandName>&& command_names, Label&& help_text, std::vector<std::pair<int, Label>>&& options, int default_value, commandflags_t flags = CMDFLAGS_LIST_SELECT, CommandPerm perm = COMMANDPERM_USERONLY, const std::vector<Hotkey>& default_hotkeys = {}) :
		    CommandPhysical(COMMAND_LIST_SELECT_INLINE, parent, std::move(menu_name), std::move(command_names), std::move(help_text), flags, perm, default_hotkeys),
		    options(std::move(options)),
		    value(default_value),
		    default_value(default_value)
		{
		}

		[[nodiscard]] size_t indexOf(int val) const
		{
			for (size_t i = 0; i < options.size(); ++i)
				if (options[i].first == val)
					return i;
			return 0;
		}

		[[nodiscard]] const Label& getCurrentValueMenuName() const
		{
			return options[indexOf(value)].second;
		}

		bool onLeft(Click& click, bool holding) override
		{
			return step(click, -1);
		}

		bool onRight(Click& click, bool holding) override
		{
			return step(click, 1);
		}

		void setValue(Click& click, int newValue)
		{
			if (value == newValue)
				return;

			const int prev_value = value;
			value = newValue;
			updateState(click);
			onChange(click, prev_value);
		}

		virtual void onChange(Click& click, int prev_value)
		{
		}

		std::string getState() const override
		{
			return std::to_string(value);
		}

		std::string getDefaultState() const override
		{
			return std::to_string(default_value);
		}

		void setState(Click& click, const std::string& state) override
		{
			int updated_value = default_value;
			if (!state.empty())
			{
				try
				{
					updated_value = std::stoi(state);
				}
				catch (const std::exception&)
				{
				}
			}
			setValue(click, updated_value);
		}

		void applyDefaultState() override
		{
			if (value != default_value)
			{
				const int prev_value = value;
				value = default_value;
				Click click(CLICK_BULK, TC_APPLYDEFAULTSTATE);
				updateState(click);
				onChange(click, prev_value);
			}
		}

	private:
		bool step(Click& click, int direction)
		{
			if (options.empty())
				return false;

			const size_t index = indexOf(value);
			const size_t nextIndex = direction > 0 ? (index + 1) % options.size() : (index + options.size() - 1) % options.size();
			const int newValue = options[nextIndex].first;

			ensureScriptThread(click, [this, newValue](Click& click) mutable {
				setValue(click, newValue);
			});

			return true;
		}

		void updateState(const Click& click)
		{
			CommandStateSerializer::MarkDirty();
		}
	};
}
