#include "GridItemCommandToggle.hpp"

#include "Commands.hpp"
#include "GridRenderer.hpp"
#include "Theme.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kIndicatorSize = 16.f;
		constexpr float kLabelGap = 10.f;
	}

	GridItemCommandToggle::GridItemCommandToggle(int16_t width, int16_t height, joaat_t id, std::optional<std::string> labelOverride) :
	    GridItem(GRIDITEM_INDIFFERENT, width, height),
	    m_Command(Commands::GetCommand<BoolCommand>(id)),
	    m_LabelOverride(std::move(labelOverride))
	{
	}

	const std::string& GridItemCommandToggle::Label() const
	{
		static const std::string unknown = "Unknown!";
		if (!m_Command)
			return unknown;

		return m_LabelOverride.has_value() ? *m_LabelOverride : m_Command->GetLabel();
	}

	void GridItemCommandToggle::draw()
	{
		// Clamped to 0 - see the identical comment in GridItemToggle.cpp:
		// otherwise a negative offset draws above this item's own row.
		const float indicatorY = y + std::max(0.f, (height - kIndicatorSize) * 0.5f);
		const auto colour = m_Command ? (m_Command->GetState() ? Theme::kAccent : Theme::kToggleOff) : Theme::kError;
		GridRenderer::DrawRect(x, indicatorY, kIndicatorSize, kIndicatorSize, colour);
	}

	void GridItemCommandToggle::drawText()
	{
		const auto& label = Label();
		const float textY = y + std::max(0.f, (height - GridRenderer::MeasureText(label.c_str()).y) * 0.5f);
		GridRenderer::DrawText(x + kIndicatorSize + kLabelGap, textY, label.c_str(), Theme::kText);
	}

	void GridItemCommandToggle::onClick(int16_t, int16_t)
	{
		if (!m_Command)
			return;

		// Matches BoolCommandItem::Draw() exactly: read the live state,
		// flip it, SetState() - not a locally-tracked bool.
		m_Command->SetState(!m_Command->GetState());
	}
}
