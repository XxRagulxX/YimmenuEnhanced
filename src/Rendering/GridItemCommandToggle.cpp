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

	GridItemCommandToggle::GridItemCommandToggle(float height, joaat_t id, std::optional<std::string> labelOverride) :
	    GridItem(height),
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

	void GridItemCommandToggle::Draw()
	{
		// Clamped to 0 - see the identical comment in GridItemToggle.cpp:
		// otherwise a negative offset draws above this item's own row.
		const float indicatorY = m_Y + std::max(0.f, (m_Height - kIndicatorSize) * 0.5f);
		const auto colour = m_Command ? (m_Command->GetState() ? Theme::kAccent : Theme::kToggleOff) : Theme::kError;
		GridRenderer::DrawRect(m_X, indicatorY, kIndicatorSize, kIndicatorSize, colour);
	}

	void GridItemCommandToggle::DrawText()
	{
		const auto& label = Label();
		const float textY = m_Y + std::max(0.f, (m_Height - GridRenderer::MeasureText(label.c_str()).y) * 0.5f);
		GridRenderer::DrawText(m_X + kIndicatorSize + kLabelGap, textY, label.c_str(), Theme::kText);
	}

	void GridItemCommandToggle::OnClick(float, float)
	{
		if (!m_Command)
			return;

		// Matches BoolCommandItem::Draw() exactly: read the live state,
		// flip it, SetState() - not a locally-tracked bool.
		m_Command->SetState(!m_Command->GetState());
	}
}
