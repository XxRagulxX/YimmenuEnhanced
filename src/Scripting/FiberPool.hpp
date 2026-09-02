#pragma once

#include <functional>

namespace YimMenu
{
	class FiberPool
	{
	public:
		static void queueJob(std::function<void()>&& func);

		static void onTick();
	};
}