#include "GridItemIntStepper.hpp"

#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr DirectX::XMFLOAT4 kButtonBackground{0.16f, 0.42f, 0.83f, 0.9f};
		constexpr DirectX::XMFLOAT4 kValueBackground{0.f, 0.f, 0.f, 0.5f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};

		constexpr float kButtonSize = 22.f;
		constexpr float kValueWidth = 40.f;
		constexpr float kGap = 6.f;
	}

	GridItemIntStepper::Layout GridItemIntStepper::ComputeLayout() const
	{
		Layout layout;
		layout.buttonSize = kButtonSize;
		layout.valueWidth = kValueWidth;
		layout.plusX = m_X + m_Width - kButtonSize;
		layout.minusX = layout.plusX - kGap - kButtonSize;
		layout.valueX = layout.minusX - kGap - kValueWidth;
		return layout;
	}

	void GridItemIntStepper::Draw()
	{
		const auto layout = ComputeLayout();

		GridRenderer::DrawRect(layout.valueX, m_Y, layout.valueWidth, m_Height, kValueBackground);
		GridRenderer::DrawRect(layout.minusX, m_Y, layout.buttonSize, m_Height, kButtonBackground);
		GridRenderer::DrawRect(layout.plusX, m_Y, layout.buttonSize, m_Height, kButtonBackground);
	}

	void GridItemIntStepper::DrawText()
	{
		// Every centring offset below is clamped to 0 - see the identical
		// comment in GridItemToggle.cpp: otherwise text taller/wider than
		// its own box centres outside that box (upward, or into a
		// neighbouring button/box for the horizontal ones).
		const auto layout = ComputeLayout();

		const auto labelSize = GridRenderer::MeasureText(m_Label.c_str());
		GridRenderer::DrawText(
		    m_X,
		    m_Y + std::max(0.f, (m_Height - labelSize.y) * 0.5f),
		    m_Label.c_str(),
		    kText);

		const auto valueStr = std::to_string(m_Value);
		const auto valueSize = GridRenderer::MeasureText(valueStr.c_str());
		GridRenderer::DrawText(layout.valueX + std::max(0.f, (layout.valueWidth - valueSize.x) * 0.5f),
		    m_Y + std::max(0.f, (m_Height - valueSize.y) * 0.5f),
		    valueStr.c_str(),
		    kText);

		const auto minusSize = GridRenderer::MeasureText("-");
		GridRenderer::DrawText(layout.minusX + std::max(0.f, (layout.buttonSize - minusSize.x) * 0.5f),
		    m_Y + std::max(0.f, (m_Height - minusSize.y) * 0.5f),
		    "-",
		    kText);

		const auto plusSize = GridRenderer::MeasureText("+");
		GridRenderer::DrawText(layout.plusX + std::max(0.f, (layout.buttonSize - plusSize.x) * 0.5f),
		    m_Y + std::max(0.f, (m_Height - plusSize.y) * 0.5f),
		    "+",
		    kText);
	}

	void GridItemIntStepper::OnClick(float cursorX, float)
	{
		const auto layout = ComputeLayout();

		if (cursorX >= layout.plusX && cursorX < layout.plusX + layout.buttonSize)
			m_Value = std::min(m_Max, m_Value + 1);
		else if (cursorX >= layout.minusX && cursorX < layout.minusX + layout.buttonSize)
			m_Value = std::max(m_Min, m_Value - 1);
	}
}
