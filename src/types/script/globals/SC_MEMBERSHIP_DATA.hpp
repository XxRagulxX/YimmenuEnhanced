#pragma once
#include "../types.hpp"

enum class eSCMembershipFlags
{
	MEMBERSHIP_CHECKED = 1,
	CHECK_MEMBERSHIP,
	DISABLE_MEMBERSHIP_CHECK
};

struct SC_MEMBERSHIP_DATA
{
	SCR_BOOL HasMembership;               // 0
	SCR_INT StartPosix;                   // 1
	SCR_INT EndPosix;                     // 2
	SCR_BITSET<eSCMembershipFlags> Flags; // 3

	static SC_MEMBERSHIP_DATA* Get();
};
static_assert(sizeof(SC_MEMBERSHIP_DATA) == 4 * 8);