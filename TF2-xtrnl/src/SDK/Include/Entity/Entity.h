#pragma once
#include "../Defines.h"

class CEntity
{
private:
	DWORD m_dwThis;

public:
	explicit operator bool() const;
	bool operator== (const CEntity &other);
	CEntity(const DWORD &dwAddress);
	DWORD GetThis() const;
	int GetFlags() const;
	int GetHealth() const;
	int GetTeamNum() const;
	int GetClassNum() const;
	byte GetLifeState() const;
	int GetClassID() const;
	bool IsAlive() const;
	bool IsInValidTeam() const;
	bool IsOnGround() const;
	bool IsPlayer() const;
	bool IsBuilding() const;
	Vector GetOrigin() const;
	Vector GetViewOffset() const;
	Vector GetEyePosition() const;
	DWORD GetBoneMatrix() const;
	Vector GetBonePos(int nBoneIndex) const;
	bool IsDormant() const;
	bool IsTeleporter() const;
	int GetObserverMode() const;
	int GetActiveWeapon() const;
	bool IsGlowEnabled() const;
	void SetGlowEnabled(bool bEnabled) const;
	bool IsReadyToBackstab() const;
	int GetItemDefinitionIndex() const;
	int GetCond() const;
	bool IsScoped() const;
};