#pragma once
#include "../../SDK/SDK.h"

class CGlow
{
private:
	std::map<DWORD, int> GlowedEntities = {};
	void EnableGlow(const CEntity &Entity);
	void DisableGlows();

public:
	void Run();
};

inline CGlow g_Glow;