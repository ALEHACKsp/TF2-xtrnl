#include "EntityList.h"

DWORD CEntityList::GetEntity(int nIndex) const {
	return Utils::Read<DWORD>(Offsets::dwClient + Offsets::dwEntityList + (nIndex * 0x10));
}