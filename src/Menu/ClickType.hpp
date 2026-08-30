#pragma once
#include <cstdint>

namespace YimMenu
{
	// Verbatim port of stand-reference's src/Menu/ClickType.hpp - what
	// kind of input produced a Click (Menu/Click.hpp). Kept complete
	// (including the chat/web-command variants) rather than trimmed to
	// only what this project currently produces: it's a plain value
	// enum with no behaviour of its own, so keeping every real Stand
	// value costs nothing and means anything that reads a ClickType by
	// value (a saved hotkey, a log line, ...) never has to renumber if
	// a chat-command or web-command bridge is ever added later. Nothing
	// in this project constructs CLICK_CHAT_*/CLICK_WEB_* today - there's
	// no chat-command or web-command system here (see Click.hpp's own
	// class comment for what else that means).
	enum ClickType : uint8_t
	{
		CLICK_MENU = 0b00000,    // in-game interface click; stop_input is allowed
		CLICK_COMMAND = 0b00001, // via command box
		CLICK_HOTKEY = 0b00010,

		CLICK_FLAG_AUTO = 0b00100, // auto: be non-interactive
		CLICK_BULK = 0b00100,      // state is adjusted for consistency; don't call g_gui.on_command_state_change()
		CLICK_AUTO = 0b00101,      // state is adjusted programatically by Stand
		CLICK_SCRIPTED = 0b00111,  // state is adjusted programatically by a script

		CLICK_FLAG_CHAT = 0b01000,
		CLICK_CHAT_ALL = 0b01000,
		CLICK_CHAT_TEAM = 0b01001,

		CLICK_FLAG_WEB = 0b10000,
		CLICK_WEB = 0b10000,
		CLICK_WEB_COMMAND = 0b10001,
	};
}
