#include "Glow.h"

void CGlow::Run()
{
	if (const auto &Local = g_EntityCache.m_Local)
	{
		for (const auto &Enemy : g_EntityCache.GetGroup(EGroupType::PLAYERS_ENEMIES))
			Utils::Write<std::pair<bool, bool>>(Enemy.GetThis() + 0xDBD, { true, false });

		DWORD dwGlowObjectManager = Utils::Read<DWORD>(Offsets::dwClient + Offsets::dwGlowObjectManager);
		int nGlowObjectCount = Utils::Read<int>((Offsets::dwClient + Offsets::dwGlowObjectManager + 0xC));
		Color_t Rainbow = Utils::Rainbow();
		Vector vColor = { Color::TOFLOAT(Rainbow.r), Color::TOFLOAT(Rainbow.g), Color::TOFLOAT(Rainbow.b) };

		for (int n = 0; n < nGlowObjectCount; n++)
			Utils::Write<GlowSettings_t>((dwGlowObjectManager + (n * 32) + 4), { vColor, 1.0f, true, false });
	}
}