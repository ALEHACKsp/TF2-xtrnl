#pragma once
#include "../../SDK/SDK.h"

class CAimbot
{
private:
	struct Target_t {
		DWORD m_dwEntity;
		Vector m_vPosition;
		Vector m_vAngleTo;
		float m_flFOVTo;
	};

	std::vector<Target_t> m_vecTargets;

	bool GetTargets(const CEntity &Local);
	bool GetTarget(const CEntity &Local, Target_t &TargetOut);

public:
	void Run();
};

inline CAimbot g_Aimbot;