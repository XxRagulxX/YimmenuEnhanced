#pragma once

#include "Core/SpinlockBase.hpp"

namespace StandEnhanced
{
	class Spinlock : public SpinlockBase
	{
	public:
		[[nodiscard]] bool tryLock() noexcept;
		void lock() noexcept;
		void unlock() noexcept;
	};
}