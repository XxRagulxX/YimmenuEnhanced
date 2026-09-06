#include "Rendering/GridItemCommandColor.hpp"

#include "Commands/ColorCommand.hpp"
#include "Commands/Commands.hpp"
#include "Rendering/Grid.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/MenuNavigation.hpp"
#include "Rendering/Theme.hpp"

#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <utility>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kButtonSize = 22.f;
		constexpr float kValueWidth = 40.f;
		constexpr float kGap = 6.f;
		constexpr float kArrowGap = 5.f;

		// Real Stand's own ColourUtil::isContrastSufficient() threshold
		// (a WCAG-style relative-luminance contrast ratio) - see
		// GridItemColorFolder::drawText() below for where this gates
		// falling back to the normal arrow colour instead of the
		// command's own tint while focused.
		constexpr float kMinContrastRatio = 3.f;

		enum Channel
		{
			CHANNEL_R,
			CHANNEL_G,
			CHANNEL_B,
			CHANNEL_A,
		};

		float GetChannel(const ImVec4& colour, Channel channel)
		{
			switch (channel)
			{
			case CHANNEL_R:
				return colour.x;
			case CHANNEL_G:
				return colour.y;
			case CHANNEL_B:
				return colour.z;
			case CHANNEL_A:
				return colour.w;
			}
			return 0.f;
		}

		void SetChannel(ImVec4& colour, Channel channel, float value01)
		{
			switch (channel)
			{
			case CHANNEL_R:
				colour.x = value01;
				break;
			case CHANNEL_G:
				colour.y = value01;
				break;
			case CHANNEL_B:
				colour.z = value01;
				break;
			case CHANNEL_A:
				colour.w = value01;
				break;
			}
		}

		const char* ChannelLabel(Channel channel)
		{
			switch (channel)
			{
			case CHANNEL_R:
				return "R";
			case CHANNEL_G:
				return "G";
			case CHANNEL_B:
				return "B";
			case CHANNEL_A:
				return "A";
			}
			return "?";
		}

		// One R/G/B/A row - same label + value + "-"/"+" button shape as
		// GridItemCommandInt, just stepping a 0-255 view of one channel
		// of the shared ColorCommand's ImVec4 (stored internally as
		// 0.0-1.0, same convention ImGui::ColorPicker4 itself uses)
		// rather than owning an IntCommand of its own - see the file
		// comment in GridItemCommandColor.hpp for why this is its own
		// small GridItem instead of one of the four channels being
		// folded into a single mega-widget.
		class GridItemColorChannel : public GridItem
		{
		public:
			GridItemColorChannel(int16_t width, int16_t height, Channel channel, ColorCommand* command) :
			    GridItem(GRIDITEM_INDIFFERENT, width, height),
			    m_Channel(channel),
			    m_Command(command)
			{
			}

			bool isFocusable() const override
			{
				return true;
			}

			bool onArrow(int delta) override
			{
				if (!m_Command)
					return false;

				Step(delta > 0 ? 1 : -1);
				return true;
			}

			void draw() override
			{
				if (isKeyboardFocused())
					GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);
			}

			void drawText() override
			{
				const auto layout = ComputeLayout();
				const auto* channelLabel = ChannelLabel(m_Channel);

				const auto labelSize = GridRenderer::MeasureText(channelLabel);
				GridRenderer::DrawText(x + 5.f, y + std::max(0.f, (height - labelSize.y) * 0.5f), channelLabel, Theme::kText);

				const auto valueStr = m_Command ? std::to_string(Value255()) : std::string("?");
				const auto valueSize = GridRenderer::MeasureText(valueStr.c_str());
				GridRenderer::DrawText(layout.valueX + std::max(0.f, (layout.valueWidth - valueSize.x) * 0.5f),
				    y + std::max(0.f, (height - valueSize.y) * 0.5f),
				    valueStr.c_str(),
				    m_Command ? Theme::kText : Theme::kError);

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

			void onClick(int16_t cursorX, int16_t) override
			{
				if (!m_Command)
					return;

				const auto layout = ComputeLayout();
				if (cursorX >= layout.plusX && cursorX < layout.plusX + layout.buttonSize)
					Step(1);
				else if (cursorX >= layout.minusX && cursorX < layout.minusX + layout.buttonSize)
					Step(-1);
			}

		private:
			struct Layout
			{
				float valueX;
				float valueWidth;
				float minusX;
				float plusX;
				float buttonSize;
			};

			Layout ComputeLayout() const
			{
				Layout layout;
				layout.buttonSize = kButtonSize;
				layout.valueWidth = kValueWidth;
				layout.plusX = x + width - kButtonSize;
				layout.valueX = layout.plusX - kGap - kValueWidth;
				layout.minusX = layout.valueX - kGap - kButtonSize;
				return layout;
			}

			int Value255() const
			{
				return static_cast<int>(GetChannel(m_Command->GetState(), m_Channel) * 255.f + 0.5f);
			}

			void Step(int direction)
			{
				auto colour = m_Command->GetState();
				const auto current255 = static_cast<int>(GetChannel(colour, m_Channel) * 255.f + 0.5f);
				const auto stepped255 = std::clamp(current255 + direction * 5, 0, 255);
				SetChannel(colour, m_Channel, static_cast<float>(stepped255) / 255.f);
				m_Command->SetState(colour);
			}

			Channel m_Channel;
			ColorCommand* m_Command;
		};

		// Real Stand's own ColourUtil.hpp (origin/stand-reference) - sRGB
		// relative luminance, then the standard WCAG contrast-ratio
		// formula ((L1+0.05)/(L2+0.05), lighter over darker) - ported
		// verbatim since this project has no existing colour-contrast
		// utility of its own (checked: no other file in this codebase
		// does luminance/contrast math).
		float RelativeLuminance(const DirectX::XMFLOAT4& c)
		{
			auto linearize = [](float v) {
				return v <= 0.03928f ? v / 12.92f : std::pow((v + 0.055f) / 1.055f, 2.4f);
			};
			return 0.2126f * linearize(c.x) + 0.7152f * linearize(c.y) + 0.0722f * linearize(c.z);
		}

		bool IsContrastSufficient(const DirectX::XMFLOAT4& a, const DirectX::XMFLOAT4& b)
		{
			const float la = RelativeLuminance(a) + 0.05f;
			const float lb = RelativeLuminance(b) + 0.05f;
			const float ratio = la > lb ? la / lb : lb / la;
			return ratio > kMinContrastRatio;
		}

		// The sub-page a GridItemColorFolder row below drills into - just
		// the same four R/G/B/A channel steppers AddColorCommandRows()
		// used to push inline before this change, now on their own page
		// instead (no separate swatch/label row of its own - the folder
		// row's own tinted arrow already previews the colour, same as
		// real Stand never repeating that preview on the page it drills
		// into either).
		class ColorEditGrid : public Grid
		{
		public:
			explicit ColorEditGrid(joaat_t id) :
			    Grid(1438, 587, 0),
			    m_Id(id)
			{
			}

		protected:
			void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override
			{
				auto* command = Commands::GetCommand<ColorCommand>(m_Id);
				items_draft.push_back(std::make_unique<GridItemColorChannel>(Theme::kContentWidth, Theme::kContentItemHeight, CHANNEL_R, command));
				items_draft.push_back(std::make_unique<GridItemColorChannel>(Theme::kContentWidth, Theme::kContentItemHeight, CHANNEL_G, command));
				items_draft.push_back(std::make_unique<GridItemColorChannel>(Theme::kContentWidth, Theme::kContentItemHeight, CHANNEL_B, command));
				items_draft.push_back(std::make_unique<GridItemColorChannel>(Theme::kContentWidth, Theme::kContentItemHeight, CHANNEL_A, command));
			}

		private:
			joaat_t m_Id;
		};

		// One persistent ColorEditGrid per distinct ColorCommand id,
		// created on first use and reused after - a GridItemFolder-style
		// row's own m_Target must outlive the row and stay stable across
		// MenuNavigation pushes/pops (see GridItemFolder.hpp's own class
		// comment on why m_Target is always a non-owning pointer into
		// something owned elsewhere), and AddColorCommandRows() is a
		// stateless free function with no natural owner of its own to
		// keep one on. std::unordered_map guarantees pointer/reference
		// stability across insertions (node-based, no reallocation of
		// existing elements) - safe to hand out a raw pointer into it
		// that outlives this function call.
		ColorEditGrid& GetColorEditGrid(joaat_t id)
		{
			// try_emplace constructs the ColorEditGrid in place from the
			// forwarded id (only if not already present) rather than
			// constructing a temporary and moving/copying it in - Grid
			// has no need to support either.
			static std::unordered_map<joaat_t, ColorEditGrid> grids;
			return grids.try_emplace(id, id).first->second;
		}

		// A GridItemFolder-shaped row (label + right-aligned ">",
		// clicking/Enter drills into m_Target via MenuNavigation::Push())
		// whose arrow is tinted to m_Command's own current colour instead
		// of a separate swatch box - ported from real Stand's own
		// GridItemList::update() (origin/stand-reference): "if
		// (preview_colour_in_sprite && list->type == COMMAND_LIST_COLOUR)
		// ... arrowSpriteColour = commandColour" - the row's own trailing
		// arrow SPRITE gets its tint colour swapped to the command's
		// live RGBA (read via a getter, same as this reads GetState()),
		// falling back to the normal arrow colour only while this row is
		// focused AND contrast against the focus highlight would
		// otherwise be too low (IsContrastSufficient() above, same
		// ratio/threshold Stand's own ColourUtil::isContrastSufficient()
		// uses) - unfocused, the tint always applies. Real Stand also has
		// a second, separate mechanism (preview_colour_in_list) that
		// tints the entire row's own focus-highlight background instead -
		// not ported here, since only the arrow tint was asked for.
		//
		// A distinct class from GridItemFolder rather than a subclass of
		// it - GridItemFolder's own drawText() draws the label and arrow
		// in one function with no seam to override just the arrow's
		// colour, and duplicating its small draw()/drawText()/onClick()/
		// activate() shape here (this class is used only for colour
		// commands) is simpler than adding a hook to the generic
		// GridItemFolder every other folder row would need to skip.
		class GridItemColorFolder : public GridItem
		{
		public:
			GridItemColorFolder(int16_t width, int16_t height, std::string label, Grid* target, ColorCommand* command) :
			    GridItem(GRIDITEM_INDIFFERENT, width, height),
			    m_Label(std::move(label)),
			    m_Target(target),
			    m_Command(command)
			{
			}

			bool isFocusable() const override
			{
				return true;
			}

			void draw() override
			{
				if (isKeyboardFocused())
					GridRenderer::DrawRect(x, y, width, height, Theme::kAccent);
			}

			void drawText() override
			{
				const auto labelSize = GridRenderer::MeasureText(m_Label.c_str());
				GridRenderer::DrawText(x + 5.f, y + std::max(0.f, (height - labelSize.y) * 0.5f), m_Label.c_str(), Theme::kText);

				DirectX::XMFLOAT4 arrowColour = Theme::kText;
				if (m_Command)
				{
					const auto c = m_Command->GetState();
					const DirectX::XMFLOAT4 commandColour{c.x, c.y, c.z, c.w};
					if (!isKeyboardFocused() || IsContrastSufficient(commandColour, Theme::kAccent))
						arrowColour = commandColour;
				}

				const auto arrowSize = GridRenderer::MeasureText(">");
				GridRenderer::DrawText(x + width - arrowSize.x - kArrowGap, y + std::max(0.f, (height - arrowSize.y) * 0.5f), ">", arrowColour);
			}

			void onClick(int16_t, int16_t) override
			{
				activate();
			}

			void activate() override
			{
				MenuNavigation::Push(m_Label, m_Target);
			}

		private:
			std::string m_Label;
			Grid* m_Target;
			ColorCommand* m_Command;
		};
	}

	void AddColorCommandRows(std::vector<std::unique_ptr<GridItem>>& items_draft, int16_t width, joaat_t id, std::optional<std::string> labelOverride)
	{
		auto* command = Commands::GetCommand<ColorCommand>(id);

		std::string label = "Unknown!";
		if (labelOverride.has_value())
			label = *labelOverride;
		else if (command)
			label = command->GetLabel();

		items_draft.push_back(std::make_unique<GridItemColorFolder>(width, Theme::kContentItemHeight, std::move(label), &GetColorEditGrid(id), command));
	}

	void AddConditionalColorCommandRows(Grid& grid,
	    std::vector<std::unique_ptr<GridItem>>& items_draft,
	    int16_t width,
	    joaat_t id,
	    std::function<bool()> condition,
	    std::optional<std::string> labelOverride)
	{
		if (grid.watchCondition(condition))
			AddColorCommandRows(items_draft, width, id, std::move(labelOverride));
	}
}
