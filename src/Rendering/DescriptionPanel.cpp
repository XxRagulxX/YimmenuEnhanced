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
		constexpr float kWidth = 350.f;
		constexpr float kPadding = 8.f;
		constexpr float kLineGap = 2.f;

		// Origin: directly to the left of the sidebar, top-aligned with
		// the content column. Content already runs from Theme::
		// kMenuOriginX (the same math GetContentOrigin() itself uses)
		// out to x=1888 of the 1920-wide H-space canvas - only 32px
		// short of the right edge - so "beside content" (real Stand's
		// own default ALIGN_TOP_RIGHT placement) has nowhere to go on
		// this project's own numbers; the content viewport's own
		// visible height similarly runs to within
		// Theme::kContentBottomMargin of the bottom edge, ruling out
		// "below content" too. Left of the sidebar is the one region
		// genuinely free regardless of content width/scroll state.
		float OriginX()
		{
			return static_cast<float>(Theme::kMenuOriginX) - Theme::kSpacer - kWidth;
		}

		float OriginY()
		{
			return static_cast<float>(Theme::kMenuOriginY) + Theme::kHeaderHeight + Theme::kSpacer;
		}

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
		std::vector<std::string> WrappedLines()
		{
			auto* item = FocusedItem();
			if (!item)
				return {};

			auto description = item->GetDescription();
			if (description.empty())
				return {};

			return WrapText(description, kWidth - kPadding * 2.f, Theme::kSmallTextScale);
		}
	}

	void DescriptionPanel::Draw()
	{
		const auto lines = WrappedLines();
		if (lines.empty())
			return;

		const auto lineHeight = GridRenderer::MeasureText("Ag", Theme::kSmallTextScale).y;
		const float height = kPadding * 2.f + static_cast<float>(lines.size()) * lineHeight + static_cast<float>(lines.size() - 1) * kLineGap;

		GridRenderer::DrawRect(OriginX(), OriginY(), kWidth, height, Theme::kPanelBackground);
	}

	void DescriptionPanel::DrawText()
	{
		const auto lines = WrappedLines();
		if (lines.empty())
			return;

		const auto lineHeight = GridRenderer::MeasureText("Ag", Theme::kSmallTextScale).y;
		float y = OriginY() + kPadding;
		for (const auto& line : lines)
		{
			GridRenderer::DrawText(OriginX() + kPadding, y, line.c_str(), Theme::kText, Theme::kSmallTextScale);
			y += lineHeight + kLineGap;
		}
	}
}
