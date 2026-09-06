#include "Menu/GUI.hpp"
#include "Menu/Menu.hpp"
#include "Scripting/ScriptMgr.hpp"
#include "Rendering/Renderer.hpp"
#include "Scripting/Natives.hpp"
#include "Game/ControllerInputs.hpp"

namespace YimMenu
{
	GUI::GUI() :
	    m_IsOpen(false)
	{
		Menu::Init();

		Renderer::AddWindowProcedureCallback([this](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			GUI::WndProc(hwnd, msg, wparam, lparam);
		});

		Renderer::SetSafeToRender();
	}

	GUI::~GUI()
	{
	}

	void GUI::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_KEYUP
		    && (wparam == VK_INSERT || (wparam == VK_OEM_5 && (GetKeyState(VK_CONTROL) & 0x8000) != 0)))
		{
			// Persist and restore the cursor position between menu instances
			static POINT CursorCoords{};
			if (m_IsOpen)
			{
				GetCursorPos(&CursorCoords);
			}
			else if (CursorCoords.x + CursorCoords.y)
			{
				SetCursorPos(CursorCoords.x, CursorCoords.y);
			}
			if (!GUI::IsOnboarding())
				Toggle();
			ToggleMouse();
		}
	}

	void GUI::ToggleMouse()
	{
		// ShowCursor() maintains an internal display counter rather than
		// a plain on/off flag, so this only calls it on an actual change
		// to avoid that counter drifting if ToggleMouse() is ever called
		// more than once for the same state.
		static bool cursorShown = false;
		const bool want_mouse = GUI::IsOpen();
		if (want_mouse != cursorShown)
		{
			ShowCursor(want_mouse);
			cursorShown = want_mouse;
		}
	}

	void GUI::SetOnboardingImpl(bool state)
	{
		m_Onboarding = state;
	}

	void GUI::RunScriptImpl()
	{
		while (g_Running)
		{
			if (GUI::IsOpen())
			{
				// Real Stand feel: the menu doesn't take over the game's
				// input at all while it's open (driving, aiming, ... all
				// keep working) - it only needs to stop the one control
				// that would otherwise fire alongside its own key reads:
				// Up Arrow (INPUT_PHONE) is what was popping the cell
				// phone open every time Up/Down was used to navigate.
				PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(ControllerInputs::INPUT_PHONE), true);
			}

			// Reported bug, fixed the same way real Stand does: typing a
			// value into MenuCommandBox (or any GridItemTextInput) was
			// reaching the game's own control reads too - digits opened
			// the weapon wheel and switched weapons, 'P' opened the pause
			// menu - since nothing here ever stopped a keystroke meant
			// for a text field from also being read as a normal game
			// control. Checked how real Stand actually solves this rather
			// than guessing: origin/stand-reference's own src/Rendering/
			// Gui.cpp calls PAD::DISABLE_ALL_CONTROL_ACTIONS(0) every
			// tick for exactly as long as its own
			// Commandbox::shouldBlockGameInputs() (its command box
			// actively capturing keystrokes) is true - this project's own
			// equivalent state is InputCapture::IsTextInputActive() (see
			// GridItemTextInput/MenuCommandBox, both of which already set
			// it while editing). Same call, same gating, every tick that
			// state is true - independent of GUI::IsOpen() above, since
			// Stand's own call isn't nested under a "menu open" check
			// either, just its own narrower text-capture one.
			if (Rendering::InputCapture::IsTextInputActive())
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);

			Script::current()->yield();
		}
	}
}
