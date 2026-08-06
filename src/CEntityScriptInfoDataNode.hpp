#pragma once
#include "CProjectBaseSyncDataNode.hpp"
#include "CGameScriptObjInfo.hpp"

struct CEntityScriptInfoDataNode : CSyncDataNodeInfrequent
{
public:
	bool m_HasScriptInfo;
	CGameScriptObjInfo m_ScriptInfo;
};
static_assert(sizeof(CEntityScriptInfoDataNode) == 0x118);