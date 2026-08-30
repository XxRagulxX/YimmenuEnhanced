#pragma once
#include "GridItem.hpp"
#include "Joaat.hpp"
#include "ListCommand.hpp"

#include <optional>
#include <string>

namespace YimMenu::Rendering
{
	// A label + current selected item + "<"/">" buttons cycling through
	// a real YimMenu::ListCommand's own option list - the Grid
	// equivalent of ListCommandItem (src/ListCommandItem.cpp) for the
	// ImGui menu, minus the dropdown/combo box: there's no popup system
	// here yet, so cycling one entry at a time with the arrow buttons is
	// the whole interaction - the same trade-off GridItemIntStepper
	// already makes in place of ImGui::InputInt's text entry.
	class GridItemCommandList : public GridItem
	{
	public:
		GridItemCommandList(float height, joaat_t id, std::optional<std::string> labelOverride = std::nullopt);

		void Draw() override;
		void DrawText() override;
		void OnClick(float cursorX, float cursorY) override;

	private:
		struct Layout
		{
			float valueX;
			float valueWidth;
			float prevX;
			float nextX;
			float buttonSize;
		};
		Layout ComputeLayout() const;

		const std::string& Label() const;
		const char* CurrentItemText() const;
		float MaxItemWidth() const; // cached on first call - the list itself doesn't change at runtime

		ListCommand* m_Command;
		std::optional<std::string> m_LabelOverride;
		mutable std::optional<float> m_MaxItemWidth;
	};
}
