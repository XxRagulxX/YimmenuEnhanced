#pragma once

#include "SpinlockBase.hpp"

namespace YimMenu
{
	class Spinlock : public SpinlockBase
	{
	public:
		[[nodiscard]] bool tryLock() noexcept;
		void lock() noexcept;
		void unlock() noexcept;
	};
}