#include "Rendering/Notifications.hpp"

#include "Rendering/GridRenderer.hpp"
#include "Rendering/TextWrap.hpp"
#include "Rendering/Theme.hpp"
#include "Scripting/FiberPool.hpp"
#include "Scripting/Natives.hpp"
#include "Util/Joaat.hpp"

#include <algorithm>
#include <mutex>

namespace YimMenu
{
	namespace
	{
		constexpr float kMargin = 10.f;
		constexpr float kPadding = 8.f;
		constexpr float kProgressBarHeight = 3.5f;
		constexpr float kSeparatorHeight = 1.f;
		constexpr float kTitleScale = Rendering::Theme::kTextScale;
		constexpr float kMessageScale = Rendering::Theme::kSmallTextScale;

		// Not part of Theme.hpp's own six customizable colours (see that
		// header's own comment on why only those six are) - Success/
		// Warning have no existing slot there, same as the original's own
		// hardcoded ImVec4s for them.
		constexpr DirectX::XMFLOAT4 kSuccessColour{0.f, 1.f, 0.f, 1.f};
		constexpr DirectX::XMFLOAT4 kWarningColour{1.f, 0.5f, 0.f, 1.f};

		const DirectX::XMFLOAT4& GetTypeColour(NotificationType type)
		{
			switch (type)
			{
			case NotificationType::Success:
				return kSuccessColour;
			case NotificationType::Warning:
				return kWarningColour;
			case NotificationType::Error:
				return Rendering::Theme::kError;
			case NotificationType::Info:
			default:
				return Rendering::Theme::kText;
			}
		}

		// Every position/size Draw()'s rect pass and DrawText()'s text
		// pass both need, computed identically (and independently) by
		// each rather than shared/cached across the two - see
		// Notifications.hpp's own class comment for why each pass has to
		// stand on its own (PrimitiveBatch vs SpriteBatch), and
		// MeasureText's own doc comment for why calling it here (outside
		// either open batch) is safe.
		struct Layout
		{
			float cardX, cardY;
			float progressBarWidth;
			float separatorY;
			float titleY;
			float messageStartY;
			float lineHeight;
			std::vector<std::string> messageLines;
			float contextY;
		};

		Layout ComputeLayout(const Notification& notification, int position)
		{
			Layout layout{};
			layout.cardX = kMargin + notification.m_AnimationOffset;
			layout.cardY = kMargin + position * m_CardSizeY;

			const auto timeElapsed = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - notification.m_CreatedOn).count());
			const float depletionProgress = std::clamp(1.f - (timeElapsed / static_cast<float>(notification.m_Duration)), 0.f, 1.f);
			layout.progressBarWidth = m_CardSizeX * depletionProgress;

			const float titleHeight = Rendering::GridRenderer::MeasureText(notification.m_Title.c_str(), kTitleScale).y;
			layout.titleY = layout.cardY + kProgressBarHeight + kPadding;
			layout.separatorY = layout.titleY + titleHeight + kPadding * 0.5f;
			layout.messageStartY = layout.separatorY + kSeparatorHeight + kPadding * 0.5f;

			layout.messageLines = Rendering::WrapText(notification.m_Message, m_CardSizeX - kPadding * 2.f, kMessageScale);
			layout.lineHeight = Rendering::GridRenderer::MeasureText("Ag", kMessageScale).y;

			layout.contextY = layout.messageStartY + layout.messageLines.size() * layout.lineHeight + kPadding * 0.5f;

			return layout;
		}

		void DrawNotificationRect(const Notification& notification, int position)
		{
			using Rendering::GridRenderer;

			const auto layout = ComputeLayout(notification, position);

			GridRenderer::DrawRect(layout.cardX, layout.cardY, m_CardSizeX, m_CardSizeY, Rendering::Theme::kPanelBackground);
			GridRenderer::DrawRect(layout.cardX, layout.cardY, layout.progressBarWidth, kProgressBarHeight, Rendering::Theme::kAccent);
			GridRenderer::DrawRect(layout.cardX + kPadding, layout.separatorY, m_CardSizeX - kPadding * 2.f, kSeparatorHeight, Rendering::Theme::kToggleOff);
		}

		void DrawNotificationText(const Notification& notification, int position)
		{
			using Rendering::GridRenderer;

			const auto layout = ComputeLayout(notification, position);
			const float textX = layout.cardX + kPadding;

			GridRenderer::DrawText(textX, layout.titleY, notification.m_Title.c_str(), GetTypeColour(notification.m_Type), kTitleScale);

			float y = layout.messageStartY;
			for (auto& line : layout.messageLines)
			{
				GridRenderer::DrawText(textX, y, line.c_str(), Rendering::Theme::kText, kMessageScale);
				y += layout.lineHeight;
			}

			// No click to bind this to any more (this overlay is
			// mouseless, same as the rest of the new renderer) - see
			// this class's own header comment - so this is informational
			// only.
			if (notification.m_ContextFunc)
				GridRenderer::DrawText(textX, layout.contextY, notification.m_ContextFuncName.c_str(), Rendering::Theme::kPlaceholderText, kMessageScale);
		}
	}

	Notification Notifications::ShowImpl(std::string title, std::string message, NotificationType type, int duration, std::function<void()> context_function, std::string context_function_name)
	{
		if (title.empty() || message.empty())
			return {};

		auto message_id = Joaat(title + message);

		auto exists = std::find_if(m_Notifications.begin(), m_Notifications.end(), [&](auto& notification) {
			return notification.second.m_Identifier == message_id;
		});

		if (exists != m_Notifications.end())
		{
			exists->second.m_CreatedOn = std::chrono::system_clock::now();
			return {};
		}

		Notification notification{};
		notification.m_Title = title;
		notification.m_Message = message;
		notification.m_Type = type;
		notification.m_CreatedOn = std::chrono::system_clock::now();
		notification.m_Duration = duration;
		notification.m_Identifier = message_id;

		if (context_function)
		{
			notification.m_ContextFunc = context_function;
			notification.m_ContextFuncName = context_function_name.empty() ? "Context Function" : context_function_name;
		}

		std::lock_guard<std::mutex> lock(m_mutex);
		auto result = m_Notifications.insert(std::make_pair(title + message, notification));

		return notification;
	}

	bool Notifications::EraseImpl(Notification notification)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		for (auto& [id, n] : m_Notifications)
		{
			if (n.m_Identifier == notification.m_Identifier)
			{
				n.m_Erasing = true;
				return true;
			}
		}

		return false;
	}

	void Notifications::DrawImpl()
	{
		std::vector<std::string> keys_to_erase;
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			int position = 0;

			for (auto& [id, notification] : m_Notifications)
			{
				DrawNotificationRect(notification, position);

				if (!notification.m_Erasing)
				{
					if (notification.m_AnimationOffset < 0)
						notification.m_AnimationOffset += m_CardAnimationSpeed;

					// Need this to account for changes in card size (x dimension), custom increments might result in odd numbers
					if (notification.m_AnimationOffset > 0)
						notification.m_AnimationOffset = 0.f;
				}
				else
				{
					notification.m_AnimationOffset -= m_CardAnimationSpeed;
					if (notification.m_AnimationOffset <= -m_CardSizeX)
						keys_to_erase.push_back(id);
				}


				if ((float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - notification.m_CreatedOn).count() >= notification.m_Duration)
					keys_to_erase.push_back(id);

				position++;
			}
		}
		std::lock_guard<std::mutex> lock(m_mutex);
		for (const auto& key : keys_to_erase)
		{
			m_Notifications.erase(key);
		}
	}

	void Notifications::DrawTextImpl()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		int position = 0;

		for (auto& [id, notification] : m_Notifications)
		{
			DrawNotificationText(notification, position);
			position++;
		}
	}

	int GetNotificationColor(const std::string& color)
	{
		std::string c = color;
		std::transform(c.begin(), c.end(), c.begin(), ::tolower);

		if (c == "white")
			return 160;
		if (c == "black")
			return 140;
		if (c == "red")
			return 6;
		if (c == "orange")
			return 130;
		if (c == "yellow")
			return 180;
		if (c == "mint")
			return 200;
		if (c == "green")
			return 184;
		if (c == "light blue")
			return 40;

		return 140; // default black
	}

	void Notifications::ShowInGame(const std::string& title, const std::string& message, const std::string& icon, const std::string& color)
	{
		if (title.empty() || message.empty())
			return;

		FiberPool::queueJob([=] {
			constexpr int TIMEOUT_FRAMES = 300;
			constexpr int FEED_ICON_TYPE = 1;

			int bgColor = GetNotificationColor(color);

			std::string finalIcon = icon.empty() ? "CHAR_DEFAULT" : icon;

			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(finalIcon.c_str(), true);

			int timeout = 0;
			while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(finalIcon.c_str()))
			{
				BUILTIN::WAIT(0);

				if (++timeout > TIMEOUT_FRAMES)
				{
					// fallback icon if failed
					finalIcon = "CHAR_DEFAULT";
					GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(finalIcon.c_str(), true);
					break;
				}
			}

			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message.c_str());

			HUD::THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(bgColor);

			HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT(
			    finalIcon.c_str(),
			    finalIcon.c_str(),
			    true,
			    FEED_ICON_TYPE,
			    title.c_str(),
			    "~c~Notification");

			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, false);

			GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(finalIcon.c_str());
		});
	}
}
