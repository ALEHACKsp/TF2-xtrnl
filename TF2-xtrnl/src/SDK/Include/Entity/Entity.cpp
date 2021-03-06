#include "Entity.h"

CEntity::operator bool() const {
	return m_dwThis != 0x0;
}

bool CEntity::operator==(const CEntity &other) {
	return m_dwThis == other.GetThis();
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
	VMatrix BoneMatrix = Utils::Read<VMatrix>(Utils::Read<DWORD>(m_dwThis + Offsets::m_dwBoneMatrix) + nBoneIndex * 0x30);
	
	if (const auto &BM = BoneMatrix.As3x4())
		return Vector(BM[0][3], BM[1][3], BM[2][3]);

	return Vector();
}

bool CEntity::IsDormant() const {
	return Utils::Read<bool>(m_dwThis + Offsets::m_bDormant); //m_iTeamNum + 0xFA
}

bool CEntity::IsTeleporter() const {
	return GetClassID() == CObjectTeleporter;
}

int CEntity::GetObserverMode() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_iObserverMode);
}

int CEntity::GetActiveWeapon() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_hActiveWeapon);
}

bool CEntity::IsGlowEnabled() const {
	return Utils::Read<bool>(m_dwThis + Offsets::m_bGlowEnabled);
}

void CEntity::SetGlowEnabled(bool bEnabled) const {
	Utils::Write<std::pair<bool, bool>>(GetThis() + Offsets::m_bGlowEnabled, { bEnabled, !bEnabled });
}

bool CEntity::IsReadyToBackstab() const {
	return Utils::Read<bool>(m_dwThis + Offsets::m_bReadyToBackstab);
}

int CEntity::GetItemDefinitionIndex() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_AttributeManager + Offsets::m_Item + Offsets::m_iItemDefinitionIndex);
}

int CEntity::GetCond() const {
	return Utils::Read<int>(m_dwThis + Offsets::m_nPlayerCond);
}

bool CEntity::IsScoped() const {
	return GetCond() & TFCond_Zoomed;
}