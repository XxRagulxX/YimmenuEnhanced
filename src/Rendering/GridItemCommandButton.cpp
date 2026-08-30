#include "GridItemCommandButton.hpp"

#include "Commands.hpp"
#include "FiberPool.hpp"
#include "GridRenderer.hpp"

#include <algorithm>

namespace YimMenu::Rendering
{
	namespace
	{
		// See the note in GridItemHeader.cpp re: Stand's real theme accent
		// not being recoverable from this snapshot.
		constexpr DirectX::XMFLOAT4 kBackground{0.16f, 0.42f, 0.83f, 0.9f};
		constexpr DirectX::XMFLOAT4 kUnknownBackground{0.5f, 0.15f, 0.15f, 0.9f};
		constexpr DirectX::XMFLOAT4 kText{1.f, 1.f, 1.f, 1.f};
	}

	GridItemCommandButton::GridItemCommandButton(float height, joaat_t id, std::optional<std::string> labelOverride) :
	    GridItem(height),
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

	void GridItemCommandButton::Draw()
	{
		GridRenderer::DrawRect(m_X, m_Y, m_Width, m_Height, m_Command ? kBackground : kUnknownBackground);
	}

	void GridItemCommandButton::DrawText()
	{
		const auto& label = Label();
		const auto size = GridRenderer::MeasureText(label.c_str());
		// Clamped to 0 - see the identical comment in GridItemButton.cpp:
		// a label wider than m_Width would otherwise centre to a negative
		// offset, starting left of the button itself.
		const float textX = m_X + std::max(0.f, (m_Width - size.x) * 0.5f);
		const float textY = m_Y + std::max(0.f, (m_Height - size.y) * 0.5f);

		if (!m_LoggedDebugInfo)
		{
			m_LoggedDebugInfo = true;
			LOGF(INFO,
			    "[GridRenderer] DEBUG '{}': m_X={} m_Y={} m_Width={} m_Height={} labelW={} labelH={} textX={} textY={}",
			    label,
			    m_X,
			    m_Y,
			    m_Width,
			    m_Height,
			    size.x,
			    size.y,
			    textX,
			    textY);
		}

		GridRenderer::DrawText(textX, textY, label.c_str(), kText);
	}

	void GridItemCommandButton::OnClick(float, float)
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
