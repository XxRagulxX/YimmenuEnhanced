#pragma once
#include "BoolCommand.hpp"
#include "GridItem.hpp"
#include "Joaat.hpp"

#include <optional>
#include <string>

namespace YimMenu::Rendering
{
	// A GridItemToggle wired to a real YimMenu::BoolCommand, looked up by
	// joaat hash - the Grid/GridItem equivalent of BoolCommandItem (src/
	// BoolCommandItem.cpp) for the ImGui menu. Reads the command's live
	// state every frame (rather than tracking its own), and calls
	// SetState() on click, mirroring BoolCommandItem::Draw() exactly.
	class GridItemCommandToggle : public GridItem
	{
	public:
		GridItemCommandToggle(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt);

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

	private:
		const std::string& Label() const;

		BoolCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
	};
}
