#pragma once
#include "Rendering/GridItemTextInput.hpp"
#include "Util/Joaat.hpp"

#include <optional>
#include <string>

namespace YimMenu::Rendering
{
	// A GridItemTextInput wired to a real YimMenu::StringCommand, looked
	// up by joaat hash - the Grid equivalent of StringCommandItem (src/
	// StringCommandItem.cpp) for the ImGui menu.
	class GridItemCommandString : public GridItemTextInput
	{
	public:
		GridItemCommandString(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt);
	};
}
