#include "Aimbot.h"
#include "../Vars.h"

bool CAimbot::GetTargets(const CEntity &Local)
{
	m_vecTargets.clear();

	Vector vViewAngles = g_Engine.GetViewAngles();
	Vector vLocalEyePos = Local.GetEyePosition();
	Vector vLocalOrigin = Local.GetOrigin();

	if (Vars::Aimbot::AimPlayers)
	{
		for (const auto &Player : g_EntityCache.GetGroup(EGroupType::PLAYERS_ENEMIES))
		{
			Vector vPos = GetAimPosition(Player, true);
			Vector vAngleTo = Math::CalcAngle(vLocalEyePos, vPos);
			float flFOVTo = Vars::Aimbot::SortMethod == 0 ? Math::CalcFov(vViewAngles, vAngleTo) : 0.0f;
			float flDistTo = Vars::Aimbot::SortMethod == 1 ? vLocalOrigin.DistTo(vPos) : 0.0f;

			if (Vars::Aimbot::SortMethod == 0 && flFOVTo > Vars::Aimbot::AimFOV)
				continue;

			m_vecTargets.push_back({ Player.GetThis(), vPos, vAngleTo, flFOVTo, flDistTo });
		}
	}

	if (Vars::Aimbot::AimBuildings)
	{
		for (const auto &Building : g_EntityCache.GetGroup(EGroupType::BUILDINGS_ENEMIES))
		{
			Vector vPos = GetAimPosition(Building, false);
			Vector vAngleTo = Math::CalcAngle(vLocalEyePos, vPos);
			float flFOVTo = Vars::Aimbot::SortMethod == 0 ? Math::CalcFov(vViewAngles, vAngleTo) : 0.0f;
			float flDistTo = Vars::Aimbot::SortMethod == 1 ? vLocalOrigin.DistTo(vPos) : 0.0f;

			if (Vars::Aimbot::SortMethod == 0 && flFOVTo > Vars::Aimbot::AimFOV)
				continue;

			m_vecTargets.push_back({ Building.GetThis(), vPos, vAngleTo, flFOVTo, flDistTo });
		}
	}

	return !m_vecTargets.empty();
}

bool CAimbot::GetTarget(const CEntity &Local, Target_t &TargetOut)
{
	if (!GetTargets(Local))
		return false;

	std::sort(m_vecTargets.begin(), m_vecTargets.end(), [&](const Target_t &a, const Target_t &b) -> bool
	{
		switch (Vars::Aimbot::SortMethod) {
			case 0: return a.m_flFOVTo < b.m_flFOVTo;
			case 1: return a.m_flDistTo < b.m_flDistTo;
			default: return a.m_flDistTo < b.m_flDistTo;
		}
	});

	TargetOut = m_vecTargets[0];

	return true;
}

Vector CAimbot::GetAimPosition(const CEntity &Entity, bool bIsPlayer)
{
	if (bIsPlayer)
	{
		if (Vars::Aimbot::AimPosition == 1)
		{
			Vector vPos = {};
			float flZOffset = 0.0f;

			switch (Entity.GetClassNum()) //yup... we gaming
			{
				case CLASS_SCOUT: {
					vPos = Entity.GetBonePos(6);
					flZOffset = 5.0f;
					break;
				}

				case CLASS_SOLDIER: {
					vPos = Entity.GetBonePos(6);
					flZOffset = 5.0f;
					break;
				}

				case CLASS_PYRO: {
					vPos = Entity.GetBonePos(6);
					flZOffset = 5.0f;
					break;
				}

				case CLASS_DEMOMAN: {
					vPos = Entity.GetBonePos(16);
					flZOffset = 4.0f;
					break;
				}

				case CLASS_HEAVY: {
					vPos = Entity.GetBonePos(6);
					flZOffset = 4.0f;
					break;
				}

				case CLASS_ENGINEER: {
					vPos = Entity.GetBonePos(8);
					flZOffset = 4.0f;
					break;
				}

				case CLASS_MEDIC: {
					vPos = Entity.GetBonePos(6);
					flZOffset = 4.0f;
					break;
				}

				case CLASS_SNIPER: {
					vPos = Entity.GetBonePos(6);
					flZOffset = 4.0f;
					break;
				}

				case CLASS_SPY: {
					vPos = Entity.GetBonePos(6);
					flZOffset = 4.0f;
					break;
				}

				default: return Vector();
			}

			return vPos + Vector(0.0f, 0.0f, flZOffset);
		}
		
		return Entity.GetBonePos(0);
	}

	return Entity.GetOrigin() + Vector(0.0f, 0.0f, Entity.IsTeleporter() ? 0.0f : 25.0f);
}

void CAimbot::Aim(Vector &vAngles)
{
	switch (Vars::Aimbot::AimMethod)
	{
		case 0: {
			g_Engine.SetViewAngles(vAngles);
			break;
		}

		case 1: {
			Vector vViewAngles = g_Engine.GetViewAngles();
			Vector vDelta = vAngles - vViewAngles;
			Math::ClampAngles(vDelta);
			vViewAngles += vDelta / (Vars::Aimbot::Smoothing * 20.0f);
			g_Engine.SetViewAngles(vViewAngles);
			break;
		}

		default: break;
	}
}

void CAimbot::Run()
{
	if (!Vars::Aimbot::Active)
		return;

	if (const auto &Local = g_EntityCache.m_Local)
	{
		if (!Local.IsAlive())
			return;

		Target_t Target = {};

		auto IsKeyDown = [&]() -> bool {
			return !Vars::Aimbot::AimKey ? true : GetAsyncKeyState(Vars::Aimbot::AimKey);
		};

		if (GetTarget(Local, Target) && IsKeyDown())
		{
			Aim(Target.m_vAngleTo);
			
			if (Vars::Aimbot::AutoShoot)
				g_Client.SetAttack(6);
		}
	}
}