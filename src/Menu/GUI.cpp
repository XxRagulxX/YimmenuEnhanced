#include "Menu/UIManager.hpp"
#include "Menu/GUI.hpp"
#include "Menu/Menu.hpp"
#include "Rendering/ESP.hpp"
#include "Rendering/Overlay.hpp"
#include "Rendering/AutoDriveHUD.hpp"
#include "Scripting/ScriptMgr.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/ChatDisplay.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Scripting/Natives.hpp"
#include "Game/ControllerInputs.hpp"
#include "Config/Themes.hpp"

namespace YimMenu
{
	GUI::GUI() :
	    m_IsOpen(false)
	{
		Menu::SetupFonts();
		SetupStyle();
		Menu::Init();

		Renderer::AddWindowProcedureCallback([this](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			GUI::WndProc(hwnd, msg, wparam, lparam);
		});

		Renderer::AddRendererCallBack(
		    [&] {
			    ESP::Draw();
		    },
		    -3);
		Renderer::AddRendererCallBack(
		    [&] {
			    ChatDisplay::Draw();
		    },
		    -5);
		Renderer::AddRendererCallBack(
		    [&] {
			    AutoDriveHUD::Draw();
		    },
		    -7);
		Renderer::AddRendererCallBack(
		    [&] {
			    Overlay::Draw();
		    },
		    -6);

		Renderer::SetSafeToRender();
	}

	GUI::~GUI()
	{
	}

	void GUI::ToggleMouse()
	{
		// Real Stand feel: its menu is keyboard-only, no mouse cursor
		// ever shown for it (see GridRenderer::WndProcImpl's own
		// Up/Down/Ctrl/Shift handling) - only the classic ImGui menu
		// (still ImGui-driven, needs a real cursor) and onboarding
		// should ever turn the cursor on.
		const bool want_mouse = (GUI::IsOpen() && !Rendering::GridRenderer::IsActive()) || GUI::IsOnboarding();

		auto& io = ImGui::GetIO();
		io.MouseDrawCursor = want_mouse;
		want_mouse ? io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse : io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
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
	
	void GUI::SetOnboardingImpl(bool state)
	{
		m_Onboarding = state;
		ToggleMouse();
	}

	void GUI::RunScriptImpl()
	{
		while (g_Running)
		{
			if (GUI::IsOpen())
			{
				if (Rendering::GridRenderer::IsActive())
				{
					// Real Stand feel: the menu doesn't take over the game's
					// input at all while it's open (driving, aiming, ... all
					// keep working) - it only needs to stop the one control
					// that would otherwise fire alongside its own key
					// reads: Up Arrow (INPUT_PHONE) is what was popping the
					// cell phone open every time Up/Down was used to
					// navigate. Nothing else gets touched here.
					PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(ControllerInputs::INPUT_PHONE), true);
				}
				else if (UIManager::ShowingContentWindow())
				{
					if (GUI::IsUsingKeyboard() && PAD::IS_USING_KEYBOARD_AND_MOUSE(0))
					{
						PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
					}
					else
					{
						static constexpr ControllerInputs controls[] = {ControllerInputs::INPUT_LOOK_LR, ControllerInputs::INPUT_LOOK_UD, ControllerInputs::INPUT_ATTACK, ControllerInputs::INPUT_AIM, ControllerInputs::INPUT_DUCK, ControllerInputs::INPUT_SELECT_WEAPON, ControllerInputs::INPUT_VEH_AIM, ControllerInputs::INPUT_VEH_ATTACK, ControllerInputs::INPUT_VEH_ATTACK2, ControllerInputs::INPUT_VEH_NEXT_RADIO, ControllerInputs::INPUT_VEH_PASSENGER_AIM, ControllerInputs::INPUT_VEH_PASSENGER_ATTACK, ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON, ControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON, ControllerInputs::INPUT_VEH_MOUSE_CONTROL_OVERRIDE, ControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE, ControllerInputs::INPUT_FRONTEND_Y, ControllerInputs::INPUT_ATTACK2, ControllerInputs::INPUT_PREV_WEAPON, ControllerInputs::INPUT_NEXT_WEAPON, ControllerInputs::INPUT_VEH_DRIVE_LOOK, ControllerInputs::INPUT_VEH_DRIVE_LOOK2};

						for (const auto& control : controls)
							PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);
					}
				}
			}

			Script::current()->yield();
		}
	}
}