#pragma once
#include "../EntityList/EntityList.h"

enum struct EGroupType
{
	PLAYERS_ALL, PLAYERS_ENEMIES, PLAYERS_TEAMMATES
};

class CEntityCache
{
private:
	std::map<EGroupType, std::vector<CEntity>> m_Groups;

public:
	CEntity m_Local = 0x0;

public:
	void Fill();
	void Clear();
	const std::vector<CEntity> &GetGroup(EGroupType Group);
};

inline CEntityCache g_EntityCache;