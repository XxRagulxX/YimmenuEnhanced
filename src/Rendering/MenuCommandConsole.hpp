#pragma once
#include <string>
#include <vector>

namespace YimMenu
{
	class Command;
}

namespace YimMenu::Rendering
{
	// Stand-style blank "Command Console" - typing a prefix (e.g. "god")
	// live-lists every command whose own name starts with it (e.g.
	// "godmode - God Mode"), same live-narrowing feel as the user's own
	// reference screenshot of real Stand's own Commandbox (Commands/
	// Widgets/Commandbox.hpp + CommandboxGrid.cpp on origin/stand-
	// reference). NOT the same class as MenuCommandBox (that one always
	// opens already bound to one specific command, prefilled "<name>
	// <value>" - this one opens blank and is itself the thing that finds
	// a command by name).
	//
	// Matching logic ported from real Stand's own CommandList::
	// checkCommandNameMatch (CommandList.cpp) simplified for this
	// project's own flat legacy registry (YimMenu::Commands::GetCommands(),
	// one name per command, no tree, no OVERSHOT-driven recursion into
	// child lists - that only exists there for real Stand's own nested
	// command-name addressing, which nothing here has): an exact match
	// short-circuits to a single result the same way real Stand's own
	// HIT does; otherwise every command whose own name starts with (and
	// is longer than) the typed text is collected, real Stand's own
	// GRAZED - sorted alphabetically (real Stand's own tree walk order
	// isn't alphabetical, but this project has no equivalent ordering to
	// preserve). Each match displays as "<name> - <label>", exactly
	// CommandIssuable::getCompletionHint()'s own format (confirmed
	// against origin/stand-reference).
	//
	// Deliberately scoped to legacy YimMenu::Command only, not also
	// Stand::CommandRegistry's own ported commands - Stand::
	// CommandIssuable::onCommand() (the chat-command execution entry
	// point every ported widget would need to actually DO something on
	// Enter here) is still an empty stub in this port (see that
	// function's own doc comment in CommandIssuable.hpp) - nothing
	// overrides it yet, only the Grid-click/hotkey-dispatch paths are
	// wired. Showing a Stand match that's a dead end on Enter would be
	// worse than not showing it - a real, disclosed gap to close once a
	// later phase wires that up, not something faked here.
	//
	// A free-standing global overlay, same shape as MenuPopup/
	// MenuCommandBox: GridRenderer::DrawImpl draws it last while open,
	// WndProcImpl routes every key/char to it first while open, ahead of
	// MenuCommandBox/MenuPopup/the normal text-edit interception - opening
	// this always takes over input the same way those already do.
	class MenuCommandConsole
	{
	public:
		// Opens blank - no prefill, unlike MenuCommandBox::Open().
		static void Open();

		static bool IsOpen();
		static void Close();

		static void Draw();
		static void DrawText();

		// Enter (runs the currently-selected match's own Command::Call(),
		// the same generic activation path Call() already is regardless
		// of concrete command type - a toggle flips, a one-shot fires)/
		// Escape (closes without acting)/Up/Down (moves the selection)/
		// Backspace, same convention as MenuCommandBox::HandleKey()'s own
		// vkCode. Call for every WM_KEYDOWN while IsOpen().
		static void HandleKey(unsigned int vkCode);

		// A typed character while open - same convention as
		// MenuCommandBox::HandleChar()'s own wParam. Call for every
		// WM_CHAR while IsOpen().
		static void HandleChar(wchar_t c);

	private:
		struct Layout
		{
			float x, y, width;
			float titleY, titleHeight;
			float inputY, inputHeight;
			float firstRowY, rowHeight;
		};
		static Layout ComputeLayout();

		// Recomputes s_Matches/s_SelectedIndex from s_Buffer - called
		// after every edit (HandleChar/Backspace), not lazily from
		// Draw()/DrawText() - real Stand's own equivalent (
		// refreshCommandboxCacheOnce) runs on a background thread since
		// its own tree has thousands of commands; this project's own
		// legacy registry is small enough (low hundreds) that a plain
		// synchronous scan on every keystroke is genuinely fine, not a
		// corner cut.
		static void UpdateMatches();

		static bool s_Open;
		static std::string s_Buffer;
		static std::vector<Command*> s_Matches;
		static int s_SelectedIndex; // -1 if s_Matches is empty
	};
}
