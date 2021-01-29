#include "Glow.h"
#include "../Vars.h"

void CGlow::Run()
{
	if (!Vars::Glow::Active) {
		DisableGlows();
		return;
	}

	if (const auto &Local = g_EntityCache.m_Local)
	{
		for (const auto &Player : g_EntityCache.GetGroup(EGroupType::PLAYERS_ENEMIES))
			EnableGlow(Player);

		//custom color flickers because the glow effect is constantly updated
		//and without constantly updating it I can't consistently enable it
		//there's probably some silly workaround (like my DisableGlows meme)
		//but whatever. Damn, TF2 glow is really bad...

		//for (int n = 0; n < g_Client.GetGlowObjectManagerSize(); n++)
		//	g_Client.SetGlowObjectColor(n, { 0, 255, 0, 255 });
	}
}

void CGlow::EnableGlow(const CEntity &Entity)
{
	Entity.SetGlowEnabled(true);
	GlowedEntities[Entity.GetThis()] = 100;
}

void CGlow::DisableGlows()
{
	for (std::map<DWORD, int>::iterator it = GlowedEntities.begin(); it != GlowedEntities.end(); ++it)
	{
		if (it->second <= 0) {
			GlowedEntities.erase(it);
			continue;
		}
		
		CEntity(it->first).SetGlowEnabled(false);
		it->second--;
	}
}