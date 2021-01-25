#pragma once
#include "../Entity/Entity.h"

class CEntityList
{
public:
	DWORD GetEntity(int nIndex) const;
};

inline CEntityList g_EntityList;