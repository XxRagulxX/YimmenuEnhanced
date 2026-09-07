#include "Core/Hooks.hpp"

namespace StandEnhanced::Hooks
{
	bool Anticheat::PrepareMetricForSending(rage::JsonSerializer* ser, bool* failed, char* a3, uint64_t time, rage::rlMetric* metric)
	{
		return false; // don't send any telemetry
	}
}