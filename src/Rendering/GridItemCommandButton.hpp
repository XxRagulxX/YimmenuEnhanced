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
		GridItemCommandButton(float height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt);

		void Draw() override;
		void DrawText() override;
		void OnClick(float cursorX, float cursorY) override;

	private:
		const std::string& Label() const;

		Command* m_Command;
		std::optional<std::string> m_LabelOverride;

		// Temporary: logs computed position/size once per item the first
		// time it draws, to diagnose a text-centring overflow report.
		// Remove once that's resolved.
		bool m_LoggedDebugInfo = false;
	};
}
