#include "Core/Pointers.hpp"
#include "Menu/ClassicUI.hpp"
#include "Menu/UIManager.hpp"

namespace YimMenu
{
	// Real ImGui window/child panels are gone (see Menu/ClassicUI.hpp's
	// own class comment) - a single fixed on-screen panel instead,
	// proportioned the same way the original ImGui window was
	// (*Pointers.ScreenResX/2.5 wide, centred, starting a fifth of the
	// way down). No background rect of its own is drawn for the panel as
	// a whole (ClassicUI's own per-row backgrounds already read fine
	// against the game underneath, same "no backing window" look several
	// of this project's other always-on overlays share).
	void RenderClassicTheme()
	{
		const float screenW = static_cast<float>(*Pointers.ScreenResX);
		const float screenH = static_cast<float>(*Pointers.ScreenResY);

		const float panelWidth = screenW / 2.5f;
		const float panelX = (screenW - panelWidth) / 2.0f;
		const float panelY = screenH / 5.0f;

		ClassicUI::BeginFrame(panelX, panelY, panelWidth);

		ClassicUI::Text("YimMenuV2");
		ClassicUI::Separator();

		const auto& submenus = UIManager::GetSubmenus();
		auto activeSubmenu = UIManager::GetActiveSubmenu();

		for (auto& submenu : submenus)
		{
			if (!submenu)
				continue;

			if (submenu == activeSubmenu)
				ClassicUI::Text("> " + submenu->m_Name);
			else if (ClassicUI::Button(submenu->m_Name))
			{
				UIManager::SetActiveSubmenu(submenu);
				UIManager::SetShowContentWindow(true);
			}
		}

		ClassicUI::Separator();

		if (activeSubmenu)
		{
			activeSubmenu->DrawCategorySelectors();
			ClassicUI::Spacing();
			activeSubmenu->Draw();
		}
	}

	// Text pass - flushes whatever RenderClassicTheme() above queued this
	// same frame. Must run after it, same two-pass contract as everywhere
	// else in this system (see Menu/ClassicUI.hpp's own class comment).
	void RenderClassicThemeText()
	{
		ClassicUI::DrawQueuedText();
	}
}
