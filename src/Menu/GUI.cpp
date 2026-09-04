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

			Script::current()->yield();
		}
	}
}
