#include "SpinlockBase.hpp"

namespace YimMenu
{
	bool SpinlockBase::isLocked() const noexcept
	{
		return owner != 0;
	}

	bool SpinlockBase::isLockedByThisThread() const noexcept
	{
		return owner == _Thrd_id();
	}
}