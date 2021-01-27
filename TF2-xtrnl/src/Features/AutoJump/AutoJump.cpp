#include "AutoJump.h"
#include "../Vars.h"

void CAutoJump::Run()
{
	if (!Vars::Misc::AutoJump)
		return;

	if (const auto &Local = g_EntityCache.m_Local)
	{
		if (!Local.IsAlive())
			return;

		if (GetAsyncKeyState(VK_SPACE))
			g_Client.SetJump(Local.IsOnGround() ? 5 : 4);
	}
}