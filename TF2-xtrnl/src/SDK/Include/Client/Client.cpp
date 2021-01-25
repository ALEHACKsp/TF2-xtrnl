#include "Client.h"

DWORD CClient::GetLocalPlayer() const {
	return Utils::Read<DWORD>(Offsets::dwClient + Offsets::dwLocalPlayer);
}

DWORD CClient::GetGlowObjectManager() const {
	return Utils::Read<DWORD>(Offsets::dwClient + Offsets::dwGlowObjectManager);
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