#include "Rendering/GridItemCommandColor.hpp"

#include "Commands/ColorCommand.hpp"
#include "Commands/Commands.hpp"
#include "Rendering/Grid.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/Theme.hpp"

#include <algorithm>
#include <utility>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kButtonSize = 22.f;
		constexpr float kValueWidth = 40.f;
		constexpr float kGap = 6.f;
		constexpr float kSwatchWidth = 40.f;
		constexpr float kSwatchLabelGap = 10.f;

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

		// The live colour preview + label row - not focusable/clickable,
		// just a coloured swatch rect with the command's own label text
		// next to it.
		class GridItemColorSwatch : public GridItem
		{
		public:
			GridItemColorSwatch(int16_t width, int16_t height, std::string label, ColorCommand* command) :
			    GridItem(GRIDITEM_INDIFFERENT, width, height),
			    m_Label(std::move(label)),
			    m_Command(command)
			{
			}

			void draw() override
			{
				const auto colour = m_Command ? m_Command->GetState() : ImVec4(0.f, 0.f, 0.f, 1.f);
				GridRenderer::DrawRect(x, y, kSwatchWidth, height, DirectX::XMFLOAT4{colour.x, colour.y, colour.z, colour.w});
			}

			void drawText() override
			{
				const auto labelSize = GridRenderer::MeasureText(m_Label.c_str());
				GridRenderer::DrawText(x + kSwatchWidth + kSwatchLabelGap,
				    y + std::max(0.f, (height - labelSize.y) * 0.5f),
				    m_Label.c_str(),
				    m_Command ? Theme::kText : Theme::kError);
			}

		private:
			std::string m_Label;
			ColorCommand* m_Command;
		};

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

				const auto layout = ComputeLayout();
				GridRenderer::DrawRect(layout.valueX, y, layout.valueWidth, height, Theme::kPanelBackground);
				GridRenderer::DrawRect(layout.minusX, y, layout.buttonSize, height, Theme::kAccent);
				GridRenderer::DrawRect(layout.plusX, y, layout.buttonSize, height, Theme::kAccent);
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
				layout.minusX = layout.plusX - kGap - kButtonSize;
				layout.valueX = layout.minusX - kGap - kValueWidth;
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
	}

	void AddColorCommandRows(std::vector<std::unique_ptr<GridItem>>& items_draft, int16_t width, joaat_t id, std::optional<std::string> labelOverride)
	{
		auto* command = Commands::GetCommand<ColorCommand>(id);

		std::string label = "Unknown!";
		if (labelOverride.has_value())
			label = *labelOverride;
		else if (command)
			label = command->GetLabel();

		items_draft.push_back(std::make_unique<GridItemColorSwatch>(width, Theme::kContentItemHeight, std::move(label), command));
		items_draft.push_back(std::make_unique<GridItemColorChannel>(width, Theme::kContentItemHeight, CHANNEL_R, command));
		items_draft.push_back(std::make_unique<GridItemColorChannel>(width, Theme::kContentItemHeight, CHANNEL_G, command));
		items_draft.push_back(std::make_unique<GridItemColorChannel>(width, Theme::kContentItemHeight, CHANNEL_B, command));
		items_draft.push_back(std::make_unique<GridItemColorChannel>(width, Theme::kContentItemHeight, CHANNEL_A, command));
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
