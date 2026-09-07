#include "Util/Timer.hpp"
#include "Core/Pointers.hpp"

void TIMER::Initialize(bool localTimer)
{
	if (!IsInitialized)
	{
		Time = (*StandEnhanced::Pointers.IsSessionStarted && !localTimer) ? *StandEnhanced::Pointers.NetworkTime : *StandEnhanced::Pointers.GameTimer;
		IsInitialized = true;
	}
}

void TIMER::Reset(bool localTimer)
{
	Time = (*StandEnhanced::Pointers.IsSessionStarted && !localTimer) ? *StandEnhanced::Pointers.NetworkTime : *StandEnhanced::Pointers.GameTimer;
	IsInitialized = true;
}

void TIMER::Destroy()
{
	IsInitialized = false;
}

bool TIMER::_IsInitialized()
{
	return IsInitialized;
}

bool TIMER::HasTimePassed(int ms, bool localTimer)
{
	if (ms < 0)
		return true;

	Initialize(localTimer);

	int timePassed = (*StandEnhanced::Pointers.IsSessionStarted && !localTimer) ? (*StandEnhanced::Pointers.NetworkTime - Time) : (*StandEnhanced::Pointers.GameTimer - Time);
	if (timePassed >= ms)
		return true;

	return false;
}

int TIMER::GetRemainingTime(int ms, bool localTimer)
{
	int timePassed = (*StandEnhanced::Pointers.IsSessionStarted && !localTimer) ? (*StandEnhanced::Pointers.NetworkTime - Time) : (*StandEnhanced::Pointers.GameTimer - Time);
	return (ms - timePassed);
}

std::string TIMER::GetRemainingTimeStr(int ms, bool localTimer)
{
	int timePassed = (*StandEnhanced::Pointers.IsSessionStarted && !localTimer) ? (*StandEnhanced::Pointers.NetworkTime - Time) : (*StandEnhanced::Pointers.GameTimer - Time);
	int difference = (ms - timePassed);
	int totalSeconds = difference / 1000;
	int hours = totalSeconds / 3600;
	int minutes = (totalSeconds % 3600) / 60;
	int seconds = totalSeconds % 60;

	if (hours < 1)
		return std::format("{:02}:{:02}", minutes, seconds);
	else
		return std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
}