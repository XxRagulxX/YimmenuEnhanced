#include "Menu/ClassicUI.hpp"

#include "Core/Pointers.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/InputCapture.hpp"

#include <algorithm>
#include <vector>
#include <windows.h>

namespace YimMenu::ClassicUI
{
	namespace
	{
		using Rendering::GridRenderer;

		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
		constexpr DirectX::XMFLOAT4 kTextDisabled{0.6f, 0.6f, 0.6f, 1.f};
		constexpr DirectX::XMFLOAT4 kRowBg{1.f, 1.f, 1.f, 0.05f};
		constexpr DirectX::XMFLOAT4 kRowBgHovered{1.f, 1.f, 1.f, 0.12f};
		constexpr DirectX::XMFLOAT4 kAccent{0.36f, 0.85f, 0.56f, 1.f};
		constexpr DirectX::XMFLOAT4 kToggleOff{0.35f, 0.35f, 0.35f, 1.f};
		constexpr DirectX::XMFLOAT4 kSeparator{1.f, 1.f, 1.f, 0.15f};

		float s_PanelX = 0.f;
		float s_PanelWidth = 0.f;
		float s_CursorY = 0.f;
		float s_Scale = 1.f;
		float s_RowHeight = 24.f;

		POINT s_MousePos{};
		bool s_MouseDown = false;
		bool s_MouseClicked = false; // left button released this frame, was down last frame

		// Which TextField (by id) is currently being edited, if any - only
		// one at a time, same single-active-field model GridItemTextInput
		// uses per-item (there's no per-item focus tracking here, just a
		// single shared "this one, if any" the way a real ID stack would
		// give for free).
		std::string s_EditingId;
		std::string s_EditBuffer;
		bool s_Editing = false;

		// Queued text draws for this frame - see ClassicUI.hpp's own class
		// comment on the two-pass contract. Cleared by BeginFrame(),
		// appended to by every widget call in the rect pass, flushed and
		// cleared by DrawQueuedText() in the text pass.
		struct QueuedText
		{
			float x, y;
			std::string text;
			DirectX::XMFLOAT4 colour;
			float scale;
		};
		std::vector<QueuedText> s_QueuedText;

		void QueueText(float x, float y, const std::string& text, const DirectX::XMFLOAT4& colour, float scale)
		{
			s_QueuedText.push_back({x, y, text, colour, scale});
		}

		float ResolutionScale()
		{
			const auto w = static_cast<float>(*Pointers.ScreenResX);
			const auto h = static_cast<float>(*Pointers.ScreenResY);
			return std::clamp(std::min(w / 1920.f, h / 1080.f), 0.5f, 2.f);
		}

		bool MouseOverRow(float rowY, float rowHeight)
		{
			return s_MousePos.x >= s_PanelX && s_MousePos.x <= s_PanelX + s_PanelWidth && s_MousePos.y >= rowY && s_MousePos.y <= rowY + rowHeight;
		}

		void CommitEditing()
		{
			s_Editing = false;
			s_EditingId.clear();
			Rendering::InputCapture::SetTextInputActive(false);
		}

		// Row background + hover highlight + the standard row-height
		// advance every widget below shares - returns this row's own top Y
		// (before advancing) so callers can hit-test/draw against it.
		float BeginRow(bool interactive)
		{
			const auto rowY = s_CursorY;
			const bool hovered = interactive && MouseOverRow(rowY, s_RowHeight);
			GridRenderer::DrawRectFilledScreen(s_PanelX, rowY, s_PanelX + s_PanelWidth, rowY + s_RowHeight, hovered ? kRowBgHovered : kRowBg);
			s_CursorY += s_RowHeight + 2.f * s_Scale;
			return rowY;
		}
	}

	void BeginFrame(float x, float y, float width)
	{
		s_PanelX = x;
		s_PanelWidth = width;
		s_CursorY = y;
		s_Scale = ResolutionScale();
		s_RowHeight = 24.f * s_Scale;
		s_QueuedText.clear();

		POINT pt{};
		GetCursorPos(&pt);
		if (const auto hwnd = *Pointers.Hwnd)
			ScreenToClient(hwnd, &pt);
		s_MousePos = pt;

		const bool down = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
		s_MouseClicked = s_MouseDown && !down;
		s_MouseDown = down;
	}

	void Text(const std::string& text)
	{
		QueueText(s_PanelX + 4.f * s_Scale, s_CursorY, text, kText, s_Scale);
		s_CursorY += s_RowHeight;
	}

	void TextDisabled(const std::string& text)
	{
		QueueText(s_PanelX + 4.f * s_Scale, s_CursorY, text, kTextDisabled, s_Scale);
		s_CursorY += s_RowHeight;
	}

	bool Button(const std::string& label)
	{
		const auto rowY = BeginRow(true);
		QueueText(s_PanelX + 6.f * s_Scale, rowY + 2.f * s_Scale, label, kText, s_Scale);
		return s_MouseClicked && MouseOverRow(rowY, s_RowHeight);
	}

	bool Toggle(const std::string& label, bool value)
	{
		const auto rowY = BeginRow(true);
		QueueText(s_PanelX + 6.f * s_Scale, rowY + 2.f * s_Scale, label, kText, s_Scale);

		const auto swatchSize = s_RowHeight - 6.f * s_Scale;
		const auto swatchX = s_PanelX + s_PanelWidth - swatchSize - 6.f * s_Scale;
		const auto swatchY = rowY + 3.f * s_Scale;
		GridRenderer::DrawRectFilledScreen(swatchX, swatchY, swatchX + swatchSize, swatchY + swatchSize, value ? kAccent : kToggleOff);

		if (s_MouseClicked && MouseOverRow(rowY, s_RowHeight))
			return !value;
		return value;
	}

	int IntStepper(const std::string& label, int value, int step)
	{
		const auto rowY = BeginRow(true);
		QueueText(s_PanelX + 6.f * s_Scale, rowY + 2.f * s_Scale, label, kText, s_Scale);

		const auto valueText = std::to_string(value);
		const auto textWidth = GridRenderer::MeasureText(valueText.c_str(), s_Scale).x;
		const auto minusX = s_PanelX + s_PanelWidth - 60.f * s_Scale;
		const auto plusX = s_PanelX + s_PanelWidth - 20.f * s_Scale;
		QueueText(minusX, rowY + 2.f * s_Scale, "-", kText, s_Scale);
		QueueText(minusX + 30.f * s_Scale - textWidth * 0.5f, rowY + 2.f * s_Scale, valueText, kText, s_Scale);
		QueueText(plusX, rowY + 2.f * s_Scale, "+", kText, s_Scale);

		if (s_MouseClicked)
		{
			if (MouseOverRow(rowY, s_RowHeight) && s_MousePos.x < minusX + 20.f * s_Scale)
				return value - step;
			if (MouseOverRow(rowY, s_RowHeight) && s_MousePos.x >= plusX - 10.f * s_Scale)
				return value + step;
		}
		return value;
	}

	float FloatStepper(const std::string& label, float value, float step)
	{
		const auto rowY = BeginRow(true);
		QueueText(s_PanelX + 6.f * s_Scale, rowY + 2.f * s_Scale, label, kText, s_Scale);

		char buf[32];
		std::snprintf(buf, sizeof(buf), "%.2f", value);
		const auto textWidth = GridRenderer::MeasureText(buf, s_Scale).x;
		const auto minusX = s_PanelX + s_PanelWidth - 60.f * s_Scale;
		const auto plusX = s_PanelX + s_PanelWidth - 20.f * s_Scale;
		QueueText(minusX, rowY + 2.f * s_Scale, "-", kText, s_Scale);
		QueueText(minusX + 30.f * s_Scale - textWidth * 0.5f, rowY + 2.f * s_Scale, buf, kText, s_Scale);
		QueueText(plusX, rowY + 2.f * s_Scale, "+", kText, s_Scale);

		if (s_MouseClicked)
		{
			if (MouseOverRow(rowY, s_RowHeight) && s_MousePos.x < minusX + 20.f * s_Scale)
				return value - step;
			if (MouseOverRow(rowY, s_RowHeight) && s_MousePos.x >= plusX - 10.f * s_Scale)
				return value + step;
		}
		return value;
	}

	int Cycle(const std::string& label, const char* const* options, int count, int current)
	{
		const auto rowY = BeginRow(true);
		QueueText(s_PanelX + 6.f * s_Scale, rowY + 2.f * s_Scale, label, kText, s_Scale);

		const char* currentLabel = (count > 0 && current >= 0 && current < count) ? options[current] : "";
		const auto textWidth = GridRenderer::MeasureText(currentLabel, s_Scale).x;
		const auto leftX = s_PanelX + s_PanelWidth - 140.f * s_Scale;
		const auto rightX = s_PanelX + s_PanelWidth - 20.f * s_Scale;
		QueueText(leftX, rowY + 2.f * s_Scale, "<", kText, s_Scale);
		QueueText(leftX + (rightX - leftX) * 0.5f - textWidth * 0.5f, rowY + 2.f * s_Scale, currentLabel, kText, s_Scale);
		QueueText(rightX, rowY + 2.f * s_Scale, ">", kText, s_Scale);

		if (s_MouseClicked && count > 0 && MouseOverRow(rowY, s_RowHeight))
		{
			if (s_MousePos.x < leftX + 20.f * s_Scale)
				return (current - 1 + count) % count;
			if (s_MousePos.x >= rightX - 10.f * s_Scale)
				return (current + 1) % count;
		}
		return current;
	}

	void ColorSwatch(const std::string& label, const DirectX::XMFLOAT4& colour)
	{
		const auto rowY = BeginRow(false);
		QueueText(s_PanelX + 6.f * s_Scale, rowY + 2.f * s_Scale, label, kText, s_Scale);

		const auto swatchSize = s_RowHeight - 6.f * s_Scale;
		const auto swatchX = s_PanelX + s_PanelWidth - swatchSize - 6.f * s_Scale;
		const auto swatchY = rowY + 3.f * s_Scale;
		GridRenderer::DrawRectFilledScreen(swatchX, swatchY, swatchX + swatchSize, swatchY + swatchSize, colour);
	}

	std::string TextField(const std::string& id, const std::string& label, std::string value)
	{
		const auto rowY = BeginRow(true);
		const auto editingThis = s_Editing && s_EditingId == id;

		if (!label.empty())
			QueueText(s_PanelX + 6.f * s_Scale, rowY + 2.f * s_Scale, label, kText, s_Scale);

		const auto labelWidth = label.empty() ? 0.f : GridRenderer::MeasureText(label.c_str(), s_Scale).x + 10.f * s_Scale;
		const auto boxX = s_PanelX + 6.f * s_Scale + labelWidth;
		const auto boxWidth = std::max(0.f, s_PanelWidth - (boxX - s_PanelX) - 6.f * s_Scale);
		GridRenderer::DrawRectFilledScreen(boxX, rowY + 2.f * s_Scale, boxX + boxWidth, rowY + s_RowHeight - 2.f * s_Scale, kRowBgHovered);

		const auto displayValue = editingThis ? (s_EditBuffer + "_") : value;
		QueueText(boxX + 4.f * s_Scale, rowY + 2.f * s_Scale, displayValue, kText, s_Scale);

		if (s_MouseClicked && MouseOverRow(rowY, s_RowHeight))
		{
			if (s_Editing && s_EditingId != id)
				CommitEditing();

			s_EditingId = id;
			s_EditBuffer = value;
			s_Editing = true;
			Rendering::InputCapture::SetTextInputActive(true);
		}

		if (editingThis)
			return s_EditBuffer;
		return value;
	}

	void Separator()
	{
		GridRenderer::DrawLineScreen(s_PanelX, s_CursorY + 4.f * s_Scale, s_PanelX + s_PanelWidth, s_CursorY + 4.f * s_Scale, kSeparator, 1.f);
		s_CursorY += 10.f * s_Scale;
	}

	void Spacing()
	{
		s_CursorY += 6.f * s_Scale;
	}

	float GetCursorY()
	{
		return s_CursorY;
	}

	void SetCursorY(float y)
	{
		s_CursorY = y;
	}

	void DrawQueuedText()
	{
		for (auto& queued : s_QueuedText)
			GridRenderer::DrawTextScreen(queued.x, queued.y, queued.text.c_str(), queued.colour, queued.scale);

		s_QueuedText.clear();
	}

	void OnChar(wchar_t c)
	{
		if (!s_Editing)
			return;

		if (c >= 0x20 && c < 0x7f && s_EditBuffer.size() < 255)
			s_EditBuffer.push_back(static_cast<char>(c));
	}

	void OnKeyDown(unsigned int vkCode)
	{
		if (!s_Editing)
			return;

		switch (vkCode)
		{
		case VK_BACK:
			if (!s_EditBuffer.empty())
				s_EditBuffer.pop_back();
			break;

		case VK_RETURN:
			CommitEditing();
			break;

		case VK_ESCAPE:
			s_Editing = false;
			s_EditingId.clear();
			Rendering::InputCapture::SetTextInputActive(false);
			break;

		default:
			break;
		}
	}
}
