#include "AutoBackstab.h"
#include "../Vars.h"

void CAutoBackstab::Run()
{
	if (!Vars::Misc::AutoBackstab)
		return;

	if (const auto &Local = g_EntityCache.m_Local)
	{
		if (const CEntity &Weapon = g_EntityList.GetEntityFromHandle(Local.GetActiveWeapon()))
		{
			if (Weapon.IsReadyToBackstab())
				g_Client.SetAttack(6);
		}
	}
}