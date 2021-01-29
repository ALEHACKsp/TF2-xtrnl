#pragma once
#include "../Defines.h"

class CClient
{
public:
	DWORD GetLocalPlayer() const;
	DWORD GetGlowObjectManager() const;
	int GetGlowObjectManagerSize() const;
	void SetGlowObjectColor(int nIndex, Color_t clr) const;
	DWORD GetEntityList() const;
	void SetJump(int nTo);
	void SetAttack(int nTo);
	void SetAttack2(int nTo);
	int GetHighestEntityIndex() const;
};

inline CClient g_Client;