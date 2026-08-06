#pragma once
#include "CProjectBaseSyncDataNode.hpp"

class CPhysicalMigrationDataNode : CProjectBaseSyncDataNode
{
public:
	bool m_Unk;
};
static_assert(sizeof(CPhysicalMigrationDataNode) == 0xC8);