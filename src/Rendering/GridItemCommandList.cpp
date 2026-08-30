#include "GridItemCommandList.hpp"

#include "Commands.hpp"
#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr DirectX::XMFLOAT4 kButtonBackground{0.16f, 0.42f, 0.83f, 0.9f};
		constexpr DirectX::XMFLOAT4 kValueBackground{0.f, 0.f, 0.f, 0.5f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
		constexpr DirectX::XMFLOAT4 kUnknownColour{0.6f, 0.2f, 0.2f, 1.f};

		constexpr float kButtonSize = 22.f;
		constexpr float kGap = 6.f;
		constexpr float kValuePadding = 16.f; // left+right padding inside the value box
	}

	GridItemCommandList::GridItemCommandList(float height, joaat_t id, std::optional<std::string> labelOverride) :
	    GridItem(height),
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
		layout.nextX = m_X + m_Width - kButtonSize;
		layout.prevX = layout.nextX - kGap - kButtonSize;
		layout.valueX = layout.prevX - kGap - layout.valueWidth;
		return layout;
	}

	void GridItemCommandList::Draw()
	{
		const auto layout = ComputeLayout();

		GridRenderer::DrawRect(layout.valueX, m_Y, layout.valueWidth, m_Height, kValueBackground);
		GridRenderer::DrawRect(layout.prevX, m_Y, layout.buttonSize, m_Height, kButtonBackground);
		GridRenderer::DrawRect(layout.nextX, m_Y, layout.buttonSize, m_Height, kButtonBackground);
	}

	void GridItemCommandList::DrawText()
	{
		// Every centring offset below is clamped to 0 - see the identical
		// comment in GridItemToggle.cpp: otherwise text taller/wider than
		// its own box centres outside that box (upward, or into a
		// neighbouring button/box for the horizontal ones).
		const auto layout = ComputeLayout();

		const auto& label = Label();
		const auto labelSize = GridRenderer::MeasureText(label.c_str());
		GridRenderer::DrawText(m_X, m_Y + std::max(0.f, (m_Height - labelSize.y) * 0.5f), label.c_str(), kText);

		const auto* valueText = CurrentItemText();
		const auto valueSize = GridRenderer::MeasureText(valueText);
		GridRenderer::DrawText(layout.valueX + std::max(0.f, (layout.valueWidth - valueSize.x) * 0.5f),
		    m_Y + std::max(0.f, (m_Height - valueSize.y) * 0.5f),
		    valueText,
		    m_Command ? kText : kUnknownColour);

		const auto prevSize = GridRenderer::MeasureText("<");
		GridRenderer::DrawText(layout.prevX + std::max(0.f, (layout.buttonSize - prevSize.x) * 0.5f),
		    m_Y + std::max(0.f, (m_Height - prevSize.y) * 0.5f),
		    "<",
		    kText);

		const auto nextSize = GridRenderer::MeasureText(">");
		GridRenderer::DrawText(layout.nextX + std::max(0.f, (layout.buttonSize - nextSize.x) * 0.5f),
		    m_Y + std::max(0.f, (m_Height - nextSize.y) * 0.5f),
		    ">",
		    kText);
	}

	void GridItemCommandList::OnClick(float cursorX, float)
	{
		if (!m_Command)
			return;

		auto& list = m_Command->GetList();
		if (list.empty())
			return;

		const auto layout = ComputeLayout();

		int direction = 0;
		if (cursorX >= layout.nextX && cursorX < layout.nextX + layout.buttonSize)
			direction = 1;
		else if (cursorX >= layout.prevX && cursorX < layout.prevX + layout.buttonSize)
			direction = -1;
		else
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
