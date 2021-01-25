#pragma once
#include "../Defines.h"

class CEngine
{
public:
	Vector GetViewAngles() const;
	void SetViewAngles(Vector &vAngles, bool bClamp = true);
};

inline CEngine g_Engine;