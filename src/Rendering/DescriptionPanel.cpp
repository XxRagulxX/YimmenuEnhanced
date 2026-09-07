#include "Rendering/DescriptionPanel.hpp"

#include "Rendering/GridItem.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/MenuFocus.hpp"
#include "Rendering/MenuNavigation.hpp"
#include "Rendering/TextWrap.hpp"
#include "Rendering/Theme.hpp"

#include <string>
#include <vector>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kPadding = 8.f;
		constexpr float kLineGap = 2.f;

		GridItem* FocusedItem()
		{
			auto* current = MenuNavigation::Current();
			if (!current)
				return nullptr;

			return MenuFocus::GetFocusedItem(current);
		}

		// Recomputed fresh on every Draw()/DrawText() call rather than
		// cached - cheap (one virtual call plus a word-wrap over a
		// handful of words), and there's no shared per-frame state to
		// cache into here the way MenuGrid's own populate() has.
		std::vector<std::string> WrappedLines(int16_t width)
		{
			auto* item = FocusedItem();
			if (!item)
				return {};

			auto description = item->GetDescription();
			if (description.empty())
				return {};

			return WrapText(description, static_cast<float>(width) - kPadding * 2.f, Theme::kSmallTextScale);
		}
	}

	void DescriptionPanel::Draw(int16_t sidebarX, int16_t sidebarY, int16_t sidebarWidth, int16_t sidebarHeight)
	{
		// Real Stand's own "Below Tabs" placement uses command_width
		// (the content column's own width, not the narrower sidebar's)
		// for the box - see this class's own header comment.
		const auto width = Theme::kContentWidth;
		const auto lines = WrappedLines(width);
		if (lines.empty())
			return;

		const auto lineHeight = GridRenderer::MeasureText("Ag", Theme::kSmallTextScale).y;
		const float height = kPadding * 2.f + static_cast<float>(lines.size()) * lineHeight + static_cast<float>(lines.size() - 1) * kLineGap;

		GridRenderer::DrawRect(static_cast<float>(sidebarX), static_cast<float>(sidebarY + sidebarHeight) + Theme::kSpacer, static_cast<float>(width), height, Theme::kPanelBackground);
	}

	void DescriptionPanel::DrawText(int16_t sidebarX, int16_t sidebarY, int16_t sidebarWidth, int16_t sidebarHeight)
	{
		const auto width = Theme::kContentWidth;
		const auto lines = WrappedLines(width);
		if (lines.empty())
			return;

		const auto lineHeight = GridRenderer::MeasureText("Ag", Theme::kSmallTextScale).y;
		const float x = static_cast<float>(sidebarX) + kPadding;
		float y = static_cast<float>(sidebarY + sidebarHeight) + Theme::kSpacer + kPadding;
		for (const auto& line : lines)
		{
			GridRenderer::DrawText(x, y, line.c_str(), Theme::kText, Theme::kSmallTextScale);
			y += lineHeight + kLineGap;
		}
	}
}
