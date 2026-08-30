#pragma once
#include "GridItem.hpp"

#include <functional>
#include <string>

namespace YimMenu::Rendering
{
	// A single-line, click-to-edit text field - this project's own
	// addition (Stand routes free-text entry through its own dedicated
	// CommandboxInput system, a whole separate input mode this project
	// doesn't have - see GridItem.hpp's own isEditingText()/onChar()/
	// onEditKey() doc comments and GridRenderer::WndProcImpl for the
	// equivalent built for this instead).
	//
	// Click or Enter starts editing; typed characters append to the end,
	// Backspace removes the last one - no cursor placement within the
	// string, appending/trimming from the end only, same "simplest
	// interaction that still works" trade-off as everywhere else in this
	// system without a real popup/gradient/etc (see e.g.
	// GridItemCommandList's cycling "<"/">" in place of a real dropdown).
	// Enter commits (calls onCommit with the typed text) and stops
	// editing; Escape discards the typed buffer and stops editing
	// without calling onCommit, leaving the last-committed value shown.
	// Also auto-commits (not discards) if keyboard focus moves elsewhere
	// while still editing - a mouse click on another row, or Up/Down
	// navigating away - see draw()'s own isKeyboardFocused() check;
	// there's no separate "blur" event in this system to hook instead.
	//
	// onChange (optional) fires on every edit to the in-progress buffer -
	// each character typed, each Backspace - unlike onCommit, which only
	// fires once on Enter/auto-commit with the final value. This is what
	// a live-filtering search box needs (GridItemSelectList's search
	// field re-filters its rows on every keystroke, not just once the
	// user is done typing); a plain "type a value, press Enter" field
	// (every other GridItemTextInput use so far) just leaves this null.
	class GridItemTextInput : public GridItem
	{
	public:
		GridItemTextInput(int16_t width,
		    int16_t height,
		    std::string label,
		    std::string initialValue,
		    std::function<void(const std::string&)> onCommit,
		    std::function<void(const std::string&)> onChange = nullptr);

		void draw() override;
		void drawText() override;
		void onClick(int16_t cursorX, int16_t cursorY) override;

		bool isFocusable() const override
		{
			return true;
		}

		void activate() override;

		bool isEditingText() const override
		{
			return m_Editing;
		}

		void onChar(wchar_t c) override;
		void onEditKey(unsigned int vkCode) override;

	private:
		void BeginEditing();
		void Commit();
		void Cancel();

		std::string m_Label;
		std::string m_Value;  // committed value, shown when not editing
		std::string m_Buffer; // in-progress typed text, shown while editing
		std::function<void(const std::string&)> m_OnCommit;
		std::function<void(const std::string&)> m_OnChange;
		bool m_Editing = false;
	};
}
