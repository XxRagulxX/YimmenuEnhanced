#include "GridItemCommandList.hpp"

#include "Commands.hpp"
#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kButtonSize = 22.f;
		constexpr float kGap = 6.f;
		constexpr float kLabelGap = 10.f;
		constexpr float kValuePadding = 16.f;
	}

	GridItemCommandList::GridItemCommandList(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride) :
	    GridItem(GRIDITEM_INDIFFERENT, width, height),
	    m_Command(Commands::GetCommand<ListCommand>(id)),
	    m_LabelOverride(std::move(labelOverride))
	{
	}

	const std::string& GridItemCommandList::Label() const
	{
		static const std::string unknown = "Unknown!";
		if (!m_Command)
			return unknown;

		return m_LabelOverride.has_value() ? *m_LabelOverride : m_Command->GetLabel();
	}

	const char* GridItemCommandList::CurrentItemText() const
	{
		if (!m_Command)
			return "?";

		const auto state = m_Command->GetState();
		for (auto& entry : m_Command->GetList())
		{
			if (entry.first == state)
				return entry.second;
		}

		// Matches ListCommandItem::Draw()'s own fallback (m_SelectedItem
		// defaults to "") for a state with no matching list entry.
		return "";
	}

	float GridItemCommandList::MaxItemWidth() const
	{
		if (m_MaxItemWidth.has_value())
			return *m_MaxItemWidth;

		float widest = 0.f;
		if (m_Command)
		{
			for (auto& entry : m_Command->GetList())
				widest = std::max(widest, GridRenderer::MeasureText(entry.second).x);
		}

		m_MaxItemWidth = widest + kValuePadding;
		return *m_MaxItemWidth;
	}

	GridItemCommandList::Layout GridItemCommandList::ComputeLayout() const
	{
		Layout layout;
		layout.buttonSize = kButtonSize;
		layout.valueWidth = MaxItemWidth();

		// Sequential from the label's own end, not anchored to the
		// item's right edge - see the class comment in the header for
		// why (a wide option label would otherwise run back underneath
		// the label text on the left).
		const auto labelWidth = GridRenderer::MeasureText(Label().c_str()).x;
		layout.valueX = x + 5.f + labelWidth + kLabelGap;
		layout.prevX = layout.valueX + layout.valueWidth + kGap;
		layout.nextX = layout.prevX + layout.buttonSize + kGap;
		return layout;
	}

	void GridItemCommandList::draw()
	{
		// Full-row keyboard-focus highlight, drawn first so the value box
		// and buttons below layer on top of it - see GridItem.hpp's class
		// comment and MenuFocus.hpp.
		if (isKeyboardFocused())
			GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);

		const auto layout = ComputeLayout();

		GridRenderer::DrawRect(layout.valueX, y, layout.valueWidth, height, Theme::kPanelBackground);
		GridRenderer::DrawRect(layout.prevX, y, layout.buttonSize, height, Theme::kAccent);
		GridRenderer::DrawRect(layout.nextX, y, layout.buttonSize, height, Theme::kAccent);
	}

	void GridItemCommandList::drawText()
	{
		// Every centring offset below is clamped to 0 - see the identical
		// comment in GridItemToggle.cpp: otherwise text taller/wider than
		// its own box centres outside that box (upward, or into a
		// neighbouring button/box for the horizontal ones).
		const auto layout = ComputeLayout();

		const auto& label = Label();
		const auto labelSize = GridRenderer::MeasureText(label.c_str());
		GridRenderer::DrawText(x + 5.f, y + std::max(0.f, (height - labelSize.y) * 0.5f), label.c_str(), Theme::kText);

		const auto* valueText = CurrentItemText();
		const auto valueSize = GridRenderer::MeasureText(valueText);
		GridRenderer::DrawText(layout.valueX + std::max(0.f, (layout.valueWidth - valueSize.x) * 0.5f),
		    y + std::max(0.f, (height - valueSize.y) * 0.5f),
		    valueText,
		    m_Command ? Theme::kText : Theme::kError);

		const auto prevSize = GridRenderer::MeasureText("<");
		GridRenderer::DrawText(layout.prevX + std::max(0.f, (layout.buttonSize - prevSize.x) * 0.5f),
		    y + std::max(0.f, (height - prevSize.y) * 0.5f),
		    "<",
		    Theme::kText);

		const auto nextSize = GridRenderer::MeasureText(">");
		GridRenderer::DrawText(layout.nextX + std::max(0.f, (layout.buttonSize - nextSize.x) * 0.5f),
		    y + std::max(0.f, (height - nextSize.y) * 0.5f),
		    ">",
		    Theme::kText);
	}

	void GridItemCommandList::onClick(int16_t cursorX, int16_t)
	{
		if (!m_Command)
			return;

		const auto layout = ComputeLayout();

		int direction = 0;
		if (cursorX >= layout.nextX && cursorX < layout.nextX + layout.buttonSize)
			direction = 1;
		else if (cursorX >= layout.prevX && cursorX < layout.prevX + layout.buttonSize)
			direction = -1;
		else
			return;

		Cycle(direction);
	}

	bool GridItemCommandList::onArrow(int delta)
	{
		if (!m_Command || m_Command->GetList().empty())
			return false;

		Cycle(delta > 0 ? 1 : -1);
		return true;
	}

	void GridItemCommandList::Cycle(int direction)
	{
		auto& list = m_Command->GetList();
		if (list.empty())
			return;

		const auto state = m_Command->GetState();
		auto it = std::find_if(list.begin(), list.end(), [state](auto& entry) {
			return entry.first == state;
		});

		const size_t count = list.size();
		size_t index = (it != list.end()) ? static_cast<size_t>(it - list.begin()) : 0;
		// index/count are unsigned, so "index + direction" alone would
		// underflow going backwards from 0. Casting direction (+1/-1) to
		// size_t wraps -1 to SIZE_MAX, which is -1 mod 2^64 - adding that
		// to (index + count) and reducing mod count gives exactly
		// (index - 1) mod count, the wraparound-safe decrement.
		index = (index + count + static_cast<size_t>(direction)) % count;

		m_Command->SetState(list[index].first);
	}
}
