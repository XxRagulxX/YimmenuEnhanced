#include "Rendering/GridItemStandCommand.hpp"

#include "Commands/Stand/CommandToggleNoCorrelation.hpp"
#include "Commands/Widgets/CommandList.hpp"
#include "Commands/Widgets/CommandSlider.hpp"
#include "Menu/Click.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/GridStandCommandList.hpp"
#include "Rendering/MenuNavigation.hpp"
#include "Rendering/Theme.hpp"
#include "Scripting/FiberPool.hpp"

#include <algorithm>
#include <string>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kIndicatorSize = 16.f;
		constexpr float kIndicatorBorderWidth = 2.f;
		constexpr float kArrowGap = 5.f;
		constexpr float kButtonSize = 22.f;
		constexpr float kValueWidth = 40.f;
		constexpr float kGap = 6.f;

		std::string Label(Stand::Command* command)
		{
			if (auto* physical = command->getPhysical())
				return physical->getMenuName().getLocalisedUtf8();

			return "Unknown!";
		}
	}

	GridItemStandCommand::GridItemStandCommand(int16_t width, int16_t height, Stand::Command* command) :
	    GridItem(GRIDITEM_INDIFFERENT, width, height),
	    m_Command(command)
	{
	}

	void GridItemStandCommand::draw()
	{
		if (isKeyboardFocused())
			GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);

		if (!m_Command || !m_Command->isToggle())
			return;

		// Same checkbox visual as this project's own GridItemCommandToggle.cpp -
		// deliberately kept identical so a Stand-backed row and a
		// YimMenu-backed one look indistinguishable while both exist side
		// by side during the migration.
		auto* toggle = m_Command->as<Stand::CommandToggleNoCorrelation>();
		const float indicatorX = x + width - kIndicatorSize;
		const float indicatorY = y + std::max(0.f, (height - kIndicatorSize) * 0.5f);
		GridRenderer::DrawRect(indicatorX, indicatorY, kIndicatorSize, kIndicatorSize, Theme::kText);
		GridRenderer::DrawRect(indicatorX + kIndicatorBorderWidth,
		    indicatorY + kIndicatorBorderWidth,
		    kIndicatorSize - kIndicatorBorderWidth * 2.f,
		    kIndicatorSize - kIndicatorBorderWidth * 2.f,
		    toggle->m_on ? Theme::kAccent : Theme::kPanelBackground);
	}

	void GridItemStandCommand::drawText()
	{
		using Rendering::GridRenderer;

		if (!m_Command)
		{
			GridRenderer::DrawText(x + 5.f, y, "Unknown!", Theme::kError);
			return;
		}

		const auto label = Label(m_Command);
		const auto labelSize = GridRenderer::MeasureText(label.c_str());
		GridRenderer::DrawText(x + 5.f, y + std::max(0.f, (height - labelSize.y) * 0.5f), label.c_str(), Theme::kText);

		if (m_Command->isList())
		{
			const auto arrowSize = GridRenderer::MeasureText(">");
			GridRenderer::DrawText(x + width - arrowSize.x - kArrowGap, y + std::max(0.f, (height - arrowSize.y) * 0.5f), ">", Theme::kText);
			return;
		}

		if (m_Command->isSlider())
		{
			auto* slider = m_Command->as<Stand::CommandSlider>();
			const auto layout = ComputeSliderLayout();

			const auto valueStr = std::to_string(slider->value);
			const auto valueSize = GridRenderer::MeasureText(valueStr.c_str());
			GridRenderer::DrawText(layout.valueX + std::max(0.f, (layout.valueWidth - valueSize.x) * 0.5f),
			    y + std::max(0.f, (height - valueSize.y) * 0.5f),
			    valueStr.c_str(),
			    Theme::kText);

			const auto minusSize = GridRenderer::MeasureText("<");
			GridRenderer::DrawText(layout.minusX + std::max(0.f, (layout.buttonSize - minusSize.x) * 0.5f),
			    y + std::max(0.f, (height - minusSize.y) * 0.5f),
			    "<",
			    Theme::kText);

			const auto plusSize = GridRenderer::MeasureText(">");
			GridRenderer::DrawText(layout.plusX + std::max(0.f, (layout.buttonSize - plusSize.x) * 0.5f),
			    y + std::max(0.f, (height - plusSize.y) * 0.5f),
			    ">",
			    Theme::kText);
		}
	}

	void GridItemStandCommand::onClick(int16_t cursorX, int16_t)
	{
		if (!m_Command)
			return;

		if (m_Command->isSlider())
		{
			const auto layout = ComputeSliderLayout();
			if (cursorX >= layout.plusX && cursorX < layout.plusX + layout.buttonSize)
				SliderStep(1);
			else if (cursorX >= layout.minusX && cursorX < layout.minusX + layout.buttonSize)
				SliderStep(-1);
			return;
		}

		activate();
	}

	void GridItemStandCommand::activate()
	{
		if (!m_Command)
			return;

		if (m_Command->isToggle())
			ToggleClicked();
		else if (m_Command->isList())
			OpenSubList();
	}

	bool GridItemStandCommand::onArrow(int delta)
	{
		if (!m_Command || !m_Command->isSlider())
			return false;

		SliderStep(delta > 0 ? 1 : -1);
		return true;
	}

	void GridItemStandCommand::ToggleClicked()
	{
		auto* toggle = m_Command->as<Stand::CommandToggleNoCorrelation>();

		// A menu click, dispatched on a script thread since a toggle's
		// own onEnable()/onDisable() touches game state/natives, which
		// must never run directly on the render/input thread - same
		// "queue it, don't call it inline" convention
		// GridItemCommandButton.cpp's own onClick() already uses for
		// this project's own Command::Call().
		FiberPool::queueJob([toggle] {
			Stand::Click click(Stand::CLICK_MENU, Stand::TC_SCRIPT_YIELDABLE);
			toggle->onClick(click);
		});
	}

	void GridItemStandCommand::SliderStep(int direction)
	{
		auto* slider = m_Command->as<Stand::CommandSlider>();

		FiberPool::queueJob([slider, direction] {
			Stand::Click click(Stand::CLICK_MENU, Stand::TC_SCRIPT_YIELDABLE);
			if (direction > 0)
				slider->onRight(click, false);
			else
				slider->onLeft(click, false);
		});
	}

	void GridItemStandCommand::OpenSubList()
	{
		auto* list = m_Command->as<Stand::CommandList>();
		MenuNavigation::Push(Label(m_Command), &GridStandCommandList::GetOrCreate(list));
	}

	GridItemStandCommand::SliderLayout GridItemStandCommand::ComputeSliderLayout() const
	{
		SliderLayout layout;
		layout.buttonSize = kButtonSize;
		layout.valueWidth = kValueWidth;
		layout.plusX = x + width - kButtonSize;
		layout.valueX = layout.plusX - kGap - kValueWidth;
		layout.minusX = layout.valueX - kGap - kButtonSize;
		return layout;
	}
}
