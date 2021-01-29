#include "Client.h"

DWORD CClient::GetLocalPlayer() const {
	return Utils::Read<DWORD>(Offsets::dwClient + Offsets::dwLocalPlayer);
}

DWORD CClient::GetGlowObjectManager() const {
	return Utils::Read<DWORD>(Offsets::dwClient + Offsets::dwGlowObjectManager);
}

int CClient::GetGlowObjectManagerSize() const {
	return Utils::Read<int>((Offsets::dwClient + Offsets::dwGlowObjectManager + 0xC));
}

void CClient::SetGlowObjectColor(int nIndex, Color_t clr) const {
	Utils::Write<GlowObjectDefinition_t>((GetGlowObjectManager() + (nIndex * 32) + 4), { Color::TOVEC(clr), Color::TOFLOAT(clr.a) });
}

DWORD CClient::GetEntityList() const {
	return Utils::Read<DWORD>(Offsets::dwClient + Offsets::dwEntityList);
}

void CClient::SetJump(int nTo) {
	Utils::Write<int>(Offsets::dwClient + Offsets::dwJump, nTo);
}

void CClient::SetAttack(int nTo) {
	Utils::Write<int>(Offsets::dwClient + Offsets::dwAttack, nTo);
}

void CClient::SetAttack2(int nTo) {
	Utils::Write<int>(Offsets::dwClient + Offsets::dwAttack2, nTo);
}

int CClient::GetHighestEntityIndex() const {
	return Utils::Read<int>(Offsets::dwClient + Offsets::dwHighestEntityIndex);
}