#include "Entity.h"

CEntity::operator bool() const {
	return m_dwThis;
}

CEntity::CEntity(const DWORD &dwAddress) {
	m_dwThis = dwAddress;
}

DWORD CEntity::GetThis() const {
	return m_dwThis;
}

int CEntity::GetFlags() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_fFlags);
}

int CEntity::GetHealth() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_iHealth);
}

int CEntity::GetTeamNum() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_iTeamNum);
}

int CEntity::GetClassNum() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_iClass);
}

byte CEntity::GetLifeState() const {
	return Utils::Read<byte>(m_dwThis + Offsets::m_lifeState);
}

int CEntity::GetClassID() const {
	return Utils::Read<int>(Utils::Read<int>(Utils::Read<int>(Utils::Read<int>(m_dwThis + 0x8) + 0x8) + 0x1) + 0x14);
}

bool CEntity::IsAlive() const {
	return GetLifeState() == LIFE_ALIVE;
}

bool CEntity::IsInValidTeam() const {
	return [&]() -> bool {
		switch (GetTeamNum()) {
			case TEAM_RED:
			case TEAM_BLU: return true;
			default: return false;
		}
	}();
}

bool CEntity::IsOnGround() const {
	return GetFlags() & FL_ONGROUND;
}

bool CEntity::IsPlayer() const {
	return GetClassID() == CTFPlayer;
}

bool CEntity::IsBuilding() const {
	return [&]() -> bool {
		switch (GetClassID()) {
			case CObjectSentrygun:
			case CObjectDispenser:
			case CObjectTeleporter: return true;
			default: return false;
		}
	}();
}

Vector CEntity::GetOrigin() const {
	return Utils::Read<Vector>(m_dwThis + Offsets::m_vecOrigin);
}

Vector CEntity::GetViewOffset() const {
	return Utils::Read<Vector>(m_dwThis + Offsets::m_vecViewOffset);
}

Vector CEntity::GetEyePosition() const {
	return GetOrigin() + GetViewOffset();
}

DWORD CEntity::GetBoneMatrix() const {
	return Utils::Read<DWORD>(m_dwThis + Offsets::m_dwBoneMatrix);
}

Vector CEntity::GetBonePos(int nBoneIndex) const
{
	if (const auto &BoneMatrix = GetBoneMatrix())
	{
		return
		{
			Utils::Read<float>(BoneMatrix + (0x30 * nBoneIndex) + 0x0C),
			Utils::Read<float>(BoneMatrix + (0x30 * nBoneIndex) + 0x1C),
			Utils::Read<float>(BoneMatrix + (0x30 * nBoneIndex) + 0x2C)
		};
	}

	return Vector();
}

bool CEntity::IsDormant() const
{
	return Utils::Read<bool>(m_dwThis + Offsets::m_bDormant); //m_iTeamNum + 0xFA
}

bool CEntity::IsTeleporter() const
{
	return GetClassID() == CObjectTeleporter;
}