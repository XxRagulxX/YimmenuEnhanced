#include "GridItemCommandToggle.hpp"

#include "Commands.hpp"
#include "GridRenderer.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr DirectX::XMFLOAT4 kOnColour{0.2f, 0.75f, 0.35f, 1.f};
		constexpr DirectX::XMFLOAT4 kOffColour{0.35f, 0.35f, 0.35f, 1.f};
		constexpr DirectX::XMFLOAT4 kUnknownColour{0.6f, 0.2f, 0.2f, 1.f};
		constexpr DirectX::XMFLOAT4 kLabelColour{1.f, 1.f, 1.f, 1.f};

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
		const float indicatorY = m_Y + (m_Height - kIndicatorSize) * 0.5f;
		const auto colour = m_Command ? (m_Command->GetState() ? kOnColour : kOffColour) : kUnknownColour;
		GridRenderer::DrawRect(m_X, indicatorY, kIndicatorSize, kIndicatorSize, colour);
	}

	void GridItemCommandToggle::DrawText()
	{
		const auto& label = Label();
		const float textY = m_Y + (m_Height - GridRenderer::MeasureText(label.c_str()).y) * 0.5f;
		GridRenderer::DrawText(m_X + kIndicatorSize + kLabelGap, textY, label.c_str(), kLabelColour);
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
