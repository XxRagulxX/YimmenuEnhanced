#include "Commands/IntCommand.hpp"
#include "Commands/stand_widgets/LambdaAction.hpp"
#include "Rendering/NotifySettings.hpp"
#include "Rendering/Notifications.hpp"

#include <algorithm>
#include <cstdint>

namespace YimMenu::Features
{
	// Ported from real Stand's own CommandNotifyReadSpeed (Commands/
	// Online/CommandListNotifySettings.cpp on origin/stand-reference) -
	// see Notifications.cpp's own EstimateReadingTimeMs() for the formula
	// this feeds.
	class CommandNotifyReadSpeed : public IntCommand
	{
	public:
		CommandNotifyReadSpeed() :
		    IntCommand("readspeed", "Reading Speed (WPM)", "How many words per minute a notification's own display duration assumes you read at.", 0, 1000, 250)
		{
		}

	protected:
		void OnChange() override
		{
			Sync();
		}

		void LoadState(nlohmann::json& value) override
		{
			IntCommand::LoadState(value);
			Sync();
		}

	private:
		void Sync()
		{
			Rendering::NotifySettings::kReadingSpeedWpm = static_cast<std::uint16_t>(std::max(0, GetState()));
		}
	};

	static CommandNotifyReadSpeed _NotifyReadSpeed{};

	class CommandNotifyReadStartDelay : public IntCommand
	{
	public:
		CommandNotifyReadStartDelay() :
		    IntCommand("readstartdelay", "Reading Start Delay (ms)", "A fixed delay added to every notification's own computed reading time, before it starts counting down.", 0, 1000, 500)
		{
		}

	protected:
		void OnChange() override
		{
			Sync();
		}

		void LoadState(nlohmann::json& value) override
		{
			IntCommand::LoadState(value);
			Sync();
		}

	private:
		void Sync()
		{
			Rendering::NotifySettings::kReadingStartDelayMs = GetState();
		}
	};

	static CommandNotifyReadStartDelay _NotifyReadStartDelay{};

	class CommandNotifyMinDuration : public IntCommand
	{
	public:
		CommandNotifyMinDuration() :
		    IntCommand("notifyminduration", "Min Duration (ms)", "A notification's own computed reading time is never shown for less than this long.", 0, 60000, 2000)
		{
		}

	protected:
		void OnChange() override
		{
			Sync();
		}

		void LoadState(nlohmann::json& value) override
		{
			IntCommand::LoadState(value);
			Sync();
		}

	private:
		void Sync()
		{
			Rendering::NotifySettings::kMinDurationMs = GetState();
		}
	};

	static CommandNotifyMinDuration _NotifyMinDuration{};

	class CommandNotifyMaxDuration : public IntCommand
	{
	public:
		CommandNotifyMaxDuration() :
		    IntCommand("notifymaxduration", "Max Duration (ms)", "A notification's own computed reading time is never shown for longer than this.", 0, 60000, 10000)
		{
		}

	protected:
		void OnChange() override
		{
			Sync();
		}

		void LoadState(nlohmann::json& value) override
		{
			IntCommand::LoadState(value);
			Sync();
		}

	private:
		void Sync()
		{
			Rendering::NotifySettings::kMaxDurationMs = GetState();
		}
	};

	static CommandNotifyMaxDuration _NotifyMaxDuration{};

	// Ported from real Stand's own "Show Sample Notification" (Small/
	// Medium/Large) - three sample messages of increasing word count, so
	// the effect of Reading Speed/Min/Max Duration above is visible
	// against the same word-count-based formula EstimateReadingTimeMs()
	// uses (Notifications.cpp).
	static StandWidgets::LambdaAction _NotifySampleSmall{"notifysamplesmall", "Small", "Shows a short sample notification.", [] {
		                                                     Notifications::Show("Sample Notification", "A short sample message.");
	                                                     }};

	static StandWidgets::LambdaAction _NotifySampleMedium{"notifysamplemedium", "Medium", "Shows a medium-length sample notification.", [] {
		                                                      Notifications::Show("Sample Notification",
		                                                          "This is a medium length sample notification message, long enough to show a couple of lines of wrapped text.");
	                                                      }};

	static StandWidgets::LambdaAction _NotifySampleLarge{"notifysamplelarge", "Large", "Shows a long sample notification.", [] {
		                                                     Notifications::Show("Sample Notification",
		                                                         "This is a much longer sample notification message, intended to demonstrate how the reading speed, "
		                                                         "minimum duration, and maximum duration settings above interact with a notification that has a "
		                                                         "large amount of text to read through before it can safely be dismissed automatically.");
	                                                     }};
}
