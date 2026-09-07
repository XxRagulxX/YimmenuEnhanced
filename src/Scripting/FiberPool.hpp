#pragma once

#include <functional>

namespace StandEnhanced
{
	class FiberPool
	{
	public:
		static void queueJob(std::function<void()>&& func);

		static void onTick();
	};
}