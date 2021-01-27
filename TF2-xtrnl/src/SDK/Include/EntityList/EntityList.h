#pragma once
#include "../Entity/Entity.h"

class CEntityList
{
public:
	DWORD GetEntity(int nIndex) const;
	DWORD GetEntityFromHandle(int nHandle) const;
};

inline CEntityList g_EntityList;