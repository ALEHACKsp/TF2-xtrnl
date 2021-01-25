#pragma once
#include "../../SDK/SDK.h"

class CGlow
{
private:
	struct GlowSettings_t
	{
		Vector m_vColor;
		float m_flAlpha;
		bool m_bIdk, m_bIdk2;
	};

public:
	void Run();
};

inline CGlow g_Glow;