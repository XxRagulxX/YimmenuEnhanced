#pragma once
#include "GridItem.hpp"

#include <functional>
#include <string>

namespace YimMenu::Rendering
{
	// A button-styled rectangle with a centred label. Runs an optional
	// action callback on click (in addition to the log line, which stays
	// so a click is always independently verifiable in the log even for
	// a silent/purely-visual action, or when no callback is given at all).
	class GridItemButton : public GridItem
	{
	public:
		GridItemButton(float height, std::string label, std::function<void()> action = nullptr) :
		    GridItem(height),
		    m_Label(std::move(label)),
		    m_Action(std::move(action))
		{
		}

		void Draw() override;
		void DrawText() override;
		void OnClick(float cursorX, float cursorY) override;

	private:
		std::string m_Label;
		std::function<void()> m_Action;
	};
}
