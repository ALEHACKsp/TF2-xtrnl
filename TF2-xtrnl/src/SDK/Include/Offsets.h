#pragma once
#include "../../Utils/Utils.h"

#define OFFSET(name, value) inline DWORD name = value

namespace Offsets
{
	OFFSET(dwClient, 0x0);
	OFFSET(dwEngine, 0x0);

	OFFSET(dwLocalPlayer, 0xC3B570);
	OFFSET(dwEntityList, 0xC49094);
	OFFSET(dwHighestEntityIndex, 0xC590B8);
	OFFSET(dwJump, 0xC6A320);
	OFFSET(dwAttack, 0xC6A32C);
	OFFSET(dwAttack2, 0xC6A338);
	OFFSET(dwGlowObjectManager, 0xBD3BD4);
	OFFSET(dwViewAngles, 0x46848C);

	OFFSET(m_fFlags, 0x37C);
	OFFSET(m_iTeamNum, 0xB0);
	OFFSET(m_iHealth, 0xA8);
	OFFSET(m_lifeState, 0xA5);
	OFFSET(m_vecOrigin, 0x364);
	OFFSET(m_vecViewOffset, 0xFC);
	OFFSET(m_dwBoneMatrix, 0x5B0); //https://www.unknowncheats.me/forum/2755174-post265.html :shrug: thanks!
	OFFSET(m_iClass, 0x154C);
	OFFSET(m_bDormant, 0x1AA);
	OFFSET(m_iObserverMode, 0x109C);
	OFFSET(m_hActiveWeapon, 0xDB8);
}

#undef OFFSET