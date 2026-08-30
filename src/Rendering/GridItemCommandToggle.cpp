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
		constexpr float kBorderWidth = 2.f;
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
		// Full-row keyboard-focus highlight - see the identical comment
		// in GridItemToggle.cpp.
		if (isKeyboardFocused())
			GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);

		// Clamped to 0 - see the identical comment in GridItemToggle.cpp:
		// otherwise a negative offset draws above this item's own row.
		const float indicatorY = y + std::max(0.f, (height - kIndicatorSize) * 0.5f);

		// A real checkbox (border + inset fill) - see the identical
		// comment in GridItemToggle.cpp. An unresolved command (m_Command
		// null) shows fully in Theme::kError, border included, same as
		// this drew a single flat kError square before.
		const auto borderColour = m_Command ? Theme::kText : Theme::kError;
		const auto fillColour = !m_Command ? Theme::kError : (m_Command->GetState() ? Theme::kAccent : Theme::kPanelBackground);
		GridRenderer::DrawRect(x, indicatorY, kIndicatorSize, kIndicatorSize, borderColour);
		GridRenderer::DrawRect(x + kBorderWidth,
		    indicatorY + kBorderWidth,
		    kIndicatorSize - kBorderWidth * 2.f,
		    kIndicatorSize - kBorderWidth * 2.f,
		    fillColour);
	}

	void GridItemCommandToggle::drawText()
	{
		const auto& label = Label();
		const float textY = y + std::max(0.f, (height - GridRenderer::MeasureText(label.c_str()).y) * 0.5f);
		GridRenderer::DrawText(x + kIndicatorSize + kLabelGap, textY, label.c_str(), Theme::kText);
	}

	void GridItemCommandToggle::onClick(int16_t, int16_t)
	{
		activate();
	}

	void GridItemCommandToggle::activate()
	{
		if (!m_Command)
			return;

		// Matches BoolCommandItem::Draw() exactly: read the live state,
		// flip it, SetState() - not a locally-tracked bool.
		m_Command->SetState(!m_Command->GetState());
	}
}
