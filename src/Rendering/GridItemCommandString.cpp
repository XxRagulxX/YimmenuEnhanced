#include "Rendering/GridItemCommandString.hpp"

#include "Commands/Commands.hpp"
#include "Commands/StringCommand.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		// Looked up twice (here and again inside the commit callback
		// below) rather than cached as a member - GridItemTextInput
		// itself has no notion of a Command at all (kept generic, so it
		// doesn't need to know StringCommand exists), so there's nowhere
		// on the base class to stash a resolved pointer for reuse.
		std::string ResolveLabel(joaat_t id, const std::optional<std::string>& labelOverride)
		{
			if (labelOverride.has_value())
				return *labelOverride;

			if (auto* command = Commands::GetCommand<StringCommand>(id))
				return command->GetLabel();

			return "Unknown!";
		}

		std::string ResolveInitialValue(joaat_t id)
		{
			if (auto* command = Commands::GetCommand<StringCommand>(id))
				return command->GetString();

			return "";
		}
	}

	GridItemCommandString::GridItemCommandString(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride) :
	    GridItemTextInput(width, height, ResolveLabel(id, labelOverride), ResolveInitialValue(id), [id](const std::string& value) {
		    if (auto* command = Commands::GetCommand<StringCommand>(id))
			    command->SetStringValue(value);
	    })
	{
	}
}
