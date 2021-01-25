#include "Aimbot.h"

bool CAimbot::GetTargets(const CEntity &Local)
{
	m_vecTargets.clear();

	for (const auto &Enemy : g_EntityCache.GetGroup(EGroupType::PLAYERS_ENEMIES))
	{
		if (!Enemy.IsAlive())
			continue;

		Vector vPos = Enemy.GetOrigin() + Vector(0.0f, 0.0f, 50.0f);
		Vector vAngleTo = Math::CalcAngle(Local.GetEyePosition(), vPos);
		float flFOVTo = Math::CalcFov(g_Engine.GetViewAngles(), vAngleTo);

		if (flFOVTo > 180.0f)
			continue;

		m_vecTargets.push_back({ Enemy.GetThis(), vPos, vAngleTo, flFOVTo });
	}

	return !m_vecTargets.empty();
}

bool CAimbot::GetTarget(const CEntity &Local, Target_t &TargetOut)
{
	if (!GetTargets(Local))
		return false;

	std::sort(m_vecTargets.begin(), m_vecTargets.end(), [&](const Target_t &a, const Target_t &b) -> bool {
		return a.m_flFOVTo < b.m_flFOVTo;
	});

	TargetOut = m_vecTargets[0];

	return true;
}

void CAimbot::Run()
{
	if (const auto &Local = g_EntityCache.m_Local)
	{
		if (!Local.IsAlive())
			return;

		Target_t Target = {};

		if (GetTarget(Local, Target) && GetAsyncKeyState(VK_SHIFT)) {
			g_Engine.SetViewAngles(Target.m_vAngleTo);
			g_Client.SetAttack(6);
		}
	}
}