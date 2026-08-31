#include "GridItemCommandButton.hpp"

#include "Commands.hpp"
#include "FiberPool.hpp"
#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	GridItemCommandButton::GridItemCommandButton(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride) :
	    GridItem(GRIDITEM_INDIFFERENT, width, height),
	    m_Command(Commands::GetCommand<Command>(id)),
	    m_LabelOverride(std::move(labelOverride))
	{
	}

	const std::string& GridItemCommandButton::Label() const
	{
		static const std::string unknown = "Unknown!";
		if (!m_Command)
			return unknown;

		return m_LabelOverride.has_value() ? *m_LabelOverride : m_Command->GetLabel();
	}

	void GridItemCommandButton::draw()
	{
		// See the identical comment in GridItemButton.cpp - Theme::kAccent
		// only while keyboard-focused, not permanently. An unresolved
		// command (m_Command null) stays Theme::kError regardless of
		// focus, same as it always has.
		const auto colour = !m_Command ? Theme::kError : (isKeyboardFocused() ? Theme::kAccent : Theme::kPanelBackground);
		GridRenderer::DrawRect(x, y, width, height, colour);
	}

	void GridItemCommandButton::drawText()
	{
		// Left-aligned - see the identical comment in GridItemButton.cpp:
		// centring within a uniformly-wide button reads as inconsistent
		// once label lengths vary a lot, and every other widget here is
		// already left-aligned with this same ~10px inset.
		const auto& label = Label();
		const auto size = GridRenderer::MeasureText(label.c_str());
		const float textY = y + std::max(0.f, (height - size.y) * 0.5f);
		GridRenderer::DrawText(x + 5.f, textY, label.c_str(), Theme::kText);
	}

	void GridItemCommandButton::onClick(int16_t, int16_t)
	{
		activate();
	}

	void GridItemCommandButton::activate()
	{
		if (!m_Command)
			return;

		// Matches CommandItem::Draw()'s own FiberPool::queueJob([command] {
		// command->Call(); }) exactly - captured by value (a raw pointer),
		// not 'this', in case this item is ever destroyed before the job runs.
		auto* command = m_Command;
		FiberPool::queueJob([command] {
			command->Call();
		});
	}
}
