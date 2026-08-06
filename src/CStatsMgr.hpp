#pragma once
#include "sStatData.hpp"
#include "atArray.hpp"

class CStatsMgr
{
public:
	bool m_Initialized;
	rage::atArray<sStatMap> m_Stats;
	// ...

	sStatData* GetStat(std::uint32_t stat);
};