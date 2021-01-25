#include "AutoJump.h"

void CAutoJump::Run()
{
	if (const auto &Local = g_EntityCache.m_Local)
	{
		if (!Local.IsAlive())
			return;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			g_Client.SetJump(Local.IsOnGround() ? 5 : 4);
	}
}