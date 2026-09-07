#include "Rendering/MenuCommandConsole.hpp"

#include "Commands/Command.hpp"
#include "Commands/Commands.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/InputCapture.hpp"
#include "Rendering/Theme.hpp"

#include <algorithm>
#include <windows.h>

namespace YimMenu::Rendering
{
	namespace
	{
		// x/y/width match MenuCommandBox's own (real Stand's own
		// CommandboxGrid: Grid((HUD_WIDTH / 2) - (width / 2), 100,
		// spacer_size)) - the two are never open at once (see this
		// class's own header comment), so there's no visual clash.
		constexpr float kWidth = 547.f;
		constexpr float kY = 100.f;
		constexpr float kTitleHeight = 24.f;
		constexpr float kInputHeight = 32.f;
		constexpr float kRowHeight = 22.f;
		constexpr float kPaddingX = 6.f;

		// Real Stand's own max_shown_matching_commands - caps the list
		// so a short, broad prefix (e.g. a single letter) doesn't fill
		// the whole screen with rows; a trailing "+N more" row (see
		// DrawText()) accounts for the rest, same as real Stand's own
		// "MORE"/"MANYMORE" rows.
		constexpr size_t kMaxShown = 8;
	}

	bool MenuCommandConsole::s_Open = false;
	std::string MenuCommandConsole::s_Buffer;
	std::vector<Command*> MenuCommandConsole::s_Matches;
	int MenuCommandConsole::s_SelectedIndex = -1;

	void MenuCommandConsole::Open()
	{
		s_Buffer.clear();
		s_Matches.clear();
		s_SelectedIndex = -1;
		s_Open = true;
		InputCapture::SetTextInputActive(true);
	}

	bool MenuCommandConsole::IsOpen()
	{
		return s_Open;
	}

	void MenuCommandConsole::Close()
	{
		s_Open = false;
		s_Buffer.clear();
		s_Matches.clear();
		s_SelectedIndex = -1;
		InputCapture::SetTextInputActive(false);
	}

	void MenuCommandConsole::UpdateMatches()
	{
		s_Matches.clear();
		s_SelectedIndex = -1;

		if (s_Buffer.empty())
			return;

		// Exact match short-circuits to the one result, the same as real
		// Stand's own checkCommandNameMatch NMT_HIT - e.g. typing exactly
		// "godmode" resolves to it even if some other command's own name
		// also starts with "godmode" (unusual, but real Stand's own
		// tie-break rule).
		for (auto& [hash, command] : Commands::GetCommands())
		{
			if (command->GetName() == s_Buffer)
			{
				s_Matches = {command};
				s_SelectedIndex = 0;
				return;
			}
		}

		// Otherwise every command whose own name starts with (and is
		// longer than) the typed text - real Stand's own NMT_GRAZED.
		for (auto& [hash, command] : Commands::GetCommands())
		{
			const auto& name = command->GetName();
			if (name.size() > s_Buffer.size() && name.compare(0, s_Buffer.size(), s_Buffer) == 0)
				s_Matches.push_back(command);
		}

		if (s_Matches.empty())
			return;

		std::sort(s_Matches.begin(), s_Matches.end(), [](Command* a, Command* b) {
			return a->GetName() < b->GetName();
		});
		s_SelectedIndex = 0;
	}

	MenuCommandConsole::Layout MenuCommandConsole::ComputeLayout()
	{
		Layout layout{};
		layout.width = kWidth;
		layout.x = (Theme::kHudWidth - kWidth) * 0.5f;
		layout.y = kY;

		layout.titleHeight = kTitleHeight;
		layout.titleY = layout.y;

		layout.inputHeight = kInputHeight;
		layout.inputY = layout.titleY + layout.titleHeight;

		layout.rowHeight = kRowHeight;
		layout.firstRowY = layout.inputY + layout.inputHeight;

		return layout;
	}

	void MenuCommandConsole::Draw()
	{
		if (!s_Open)
			return;

		const auto layout = ComputeLayout();

		GridRenderer::DrawRect(layout.x, layout.titleY, layout.width, layout.titleHeight, Theme::kAccent);
		GridRenderer::DrawRect(layout.x, layout.inputY, layout.width, layout.inputHeight, Theme::kPanelBackground);

		// One row per shown match (capped at kMaxShown, same as
		// DrawText() below) plus one more for the trailing "+N more"
		// row, if there are more matches than that - the currently
		// selected match's own row gets the accent fill, everything
		// else the same muted panel background as the input row.
		const auto shown = (std::min)(s_Matches.size(), kMaxShown);
		for (size_t i = 0; i != shown; ++i)
		{
			const auto rowY = layout.firstRowY + static_cast<float>(i) * layout.rowHeight;
			GridRenderer::DrawRect(layout.x, rowY, layout.width, layout.rowHeight, (static_cast<int>(i) == s_SelectedIndex) ? Theme::kAccent : Theme::kPanelBackground);
		}
	}

	void MenuCommandConsole::DrawText()
	{
		if (!s_Open)
			return;

		const auto layout = ComputeLayout();

		const char* title = "Command Console";
		const auto titleSize = GridRenderer::MeasureText(title, Theme::kSmallTextScale);
		GridRenderer::DrawText(layout.x + kPaddingX,
		    layout.titleY + std::max(0.f, (layout.titleHeight - titleSize.y) * 0.5f),
		    title,
		    Theme::kText,
		    Theme::kSmallTextScale);

		const auto displayLine = s_Buffer + "|";
		const auto lineSize = GridRenderer::MeasureText(displayLine.c_str());
		GridRenderer::DrawText(layout.x + kPaddingX, layout.inputY + std::max(0.f, (layout.inputHeight - lineSize.y) * 0.5f), displayLine.c_str(), Theme::kText);

		if (s_Buffer.empty())
			return;

		if (s_Matches.empty())
		{
			const char* unknown = "Unknown command.";
			const auto unknownSize = GridRenderer::MeasureText(unknown, Theme::kSmallTextScale);
			GridRenderer::DrawText(layout.x + kPaddingX,
			    layout.firstRowY + std::max(0.f, (layout.rowHeight - unknownSize.y) * 0.5f),
			    unknown,
			    Theme::kError,
			    Theme::kSmallTextScale);
			return;
		}

		// "<name> - <label>", exactly CommandIssuable::getCompletionHint()'s
		// own format on real Stand (confirmed against origin/stand-
		// reference) - e.g. "godmode - God Mode".
		const auto shown = (std::min)(s_Matches.size(), kMaxShown);
		for (size_t i = 0; i != shown; ++i)
		{
			auto* command = s_Matches[i];
			const auto hint = command->GetName() + " - " + command->GetLabel();
			const auto rowY = layout.firstRowY + static_cast<float>(i) * layout.rowHeight;
			const auto hintSize = GridRenderer::MeasureText(hint.c_str(), Theme::kSmallTextScale);
			GridRenderer::DrawText(layout.x + kPaddingX,
			    rowY + std::max(0.f, (layout.rowHeight - hintSize.y) * 0.5f),
			    hint.c_str(),
			    Theme::kText,
			    Theme::kSmallTextScale);
		}

		if (const auto more = s_Matches.size() - shown; more != 0)
		{
			const auto moreText = "+ " + std::to_string(more) + " more";
			const auto rowY = layout.firstRowY + static_cast<float>(shown) * layout.rowHeight;
			const auto moreSize = GridRenderer::MeasureText(moreText.c_str(), Theme::kSmallTextScale);
			GridRenderer::DrawText(layout.x + kPaddingX,
			    rowY + std::max(0.f, (layout.rowHeight - moreSize.y) * 0.5f),
			    moreText.c_str(),
			    Theme::kPlaceholderText,
			    Theme::kSmallTextScale);
		}
	}

	void MenuCommandConsole::HandleKey(unsigned int vkCode)
	{
		if (!s_Open)
			return;

		switch (vkCode)
		{
		case VK_RETURN:
			if (s_SelectedIndex >= 0 && static_cast<size_t>(s_SelectedIndex) < s_Matches.size())
			{
				// Command::Call() is the generic activation path every
				// concrete command type already shares (a toggle flips
				// its own state, a one-shot fires) - the same one a
				// normal click on its row would take, not something
				// special-cased here.
				s_Matches[s_SelectedIndex]->Call();
				Close();
			}
			break;

		case VK_ESCAPE:
			Close();
			break;

		case VK_BACK:
			if (!s_Buffer.empty())
			{
				s_Buffer.pop_back();
				UpdateMatches();
			}
			break;

		case VK_UP:
		case VK_NUMPAD8:
			if (!s_Matches.empty() && s_SelectedIndex > 0)
				--s_SelectedIndex;
			break;

		case VK_DOWN:
		case VK_NUMPAD2:
			if (!s_Matches.empty() && static_cast<size_t>(s_SelectedIndex + 1) < (std::min)(s_Matches.size(), kMaxShown))
				++s_SelectedIndex;
			break;

		default:
			break;
		}
	}

	void MenuCommandConsole::HandleChar(wchar_t c)
	{
		if (!s_Open)
			return;

		// Printable ASCII only, same restriction MenuCommandBox::HandleChar()
		// applies (see that file's own comment).
		if (c >= 0x20 && c < 0x7f && s_Buffer.size() < 64)
		{
			s_Buffer.push_back(static_cast<char>(c));
			UpdateMatches();
		}
	}
}
