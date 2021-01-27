#include "Glow.h"
#include "../Vars.h"

void CGlow::Run()
{
	if (!Vars::Glow::Active)
		return;

	if (const auto &Local = g_EntityCache.m_Local)
	{
		if (Vars::Glow::GlowPlayers)
		{
			for (const auto &Player : g_EntityCache.GetGroup(EGroupType::PLAYERS_ENEMIES))
				Utils::Write<std::pair<bool, bool>>(Player.GetThis() + 0xDBD, { true, false });
		}

		if (Vars::Glow::GlowBuildings)
		{
			for (const auto &Building : g_EntityCache.GetGroup(EGroupType::BUILDINGS_ENEMIES))
				Utils::Write<std::pair<bool, bool>>(Building.GetThis() + 0xDBD, { true, false });
		}
	}
}