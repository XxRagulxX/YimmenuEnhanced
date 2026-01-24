#include "Overlay.hpp"
#include "Menu.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/invoker/Invoker.hpp"

namespace YimMenu::Features
{
	void DrawBusinessOverlay();
	BoolCommand _OverlayEnabled("overlay", "Overlay Enabled", "Show an info overlay at the top left corner of the screen");
	BoolCommand _OverlayShowFPS("overlayfps", "Overlay Show FPS", "Show frame rate in the info overlay");
	BoolCommand _OverlayLock("overlaylock", "Lock Overlay Position", "Lock the overlay so it cannot be moved in free mode");

	static std::vector<std::pair<int, const char*>> g_OverlayPositionConfig = {
	    {0, "topleft"},
	    {1, "topright"},
	    {2, "bottomleft"},
	    {3, "bottomright"},
	    {4, "free"}};

	static ListCommand _OverlayPositionCmd("overlaypos", "Overlay Position", "Change overlay position", g_OverlayPositionConfig, 0);
}

namespace YimMenu
{
	static ImVec2 g_FreeOverlayPos = ImVec2(50.f, 50.f);

	void Overlay::Draw()
	{
		if (!Features::_OverlayEnabled.GetState() || !NativeInvoker::AreHandlersCached())
			return;

		auto posMode = (OverlayPosition)Features::_OverlayPositionCmd.GetState();

		ImVec2 screen(*Pointers.ScreenResX, *Pointers.ScreenResY);
		ImVec2 padding(10.f, 10.f);

		ImVec2 pos = padding;

		switch (posMode)
		{
		case OverlayPosition::TopLeft:
			pos = padding;
			break;

		case OverlayPosition::TopRight:
			pos = ImVec2(screen.x - padding.x, padding.y);
			break;

		case OverlayPosition::BottomLeft:
			pos = ImVec2(padding.x, screen.y - padding.y);
			break;

		case OverlayPosition::BottomRight:
			pos = ImVec2(screen.x - padding.x, screen.y - padding.y);
			break;

		case OverlayPosition::Free:
			pos = g_FreeOverlayPos;
			break;
		}

		ImGuiCond cond = (posMode == OverlayPosition::Free) ? ImGuiCond_Once : ImGuiCond_Always;

		ImGui::SetNextWindowPos(pos, cond);

		ImGuiWindowFlags flags =
		    ImGuiWindowFlags_NoTitleBar |
		    ImGuiWindowFlags_NoCollapse |
		    ImGuiWindowFlags_NoSavedSettings |
		    ImGuiWindowFlags_NoScrollbar |
		    ImGuiWindowFlags_NoScrollWithMouse |
		    ImGuiWindowFlags_NoBackground |
		    ImGuiWindowFlags_AlwaysAutoResize;

		if (posMode != OverlayPosition::Free || Features::_OverlayLock.GetState())
			flags |= ImGuiWindowFlags_NoMove;

		ImGui::PushFont(Menu::Font::g_OverlayFont);

		ImGui::PushStyleColor(ImGuiCol_Text, YimMenu::g_OverlayTextColor);

		ImGui::Begin("##overlay", nullptr, flags);
		ImGui::SetWindowFontScale(YimMenu::g_OverlayTextScale);

		if (posMode == OverlayPosition::Free && !Features::_OverlayLock.GetState())
		{
			g_FreeOverlayPos = ImGui::GetWindowPos();
		}

		if (Features::_OverlayShowFPS.GetState())
			ImGui::Text("FPS: %d", (int)(ImGui::GetIO().Framerate));
		
		Features::DrawBusinessOverlay();

		ImGui::End();

		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
}