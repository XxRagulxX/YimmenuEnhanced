#pragma once
#include "Command.hpp"
#include "GridItem.hpp"
#include "Joaat.hpp"

#include <optional>
#include <string>

namespace YimMenu::Rendering
{
	// A GridItemButton wired to a real YimMenu::Command, looked up by
	// joaat hash - the Grid/GridItem equivalent of CommandItem (src/
	// CommandItem.cpp) for the ImGui menu. Click behaviour mirrors
	// CommandItem::Draw() exactly: FiberPool::queueJob calling
	// Command::Call().
	class GridItemCommandButton : public GridItem
	{
	public:
		GridItemCommandButton(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt);

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

	private:
		const std::string& Label() const;

		Command* m_Command;
		std::optional<std::string> m_LabelOverride;
	};
}
