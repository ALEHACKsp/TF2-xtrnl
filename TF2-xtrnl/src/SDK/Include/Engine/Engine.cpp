#include "Engine.h"

Vector CEngine::GetViewAngles() const {
	return Utils::Read<Vector>(Offsets::dwEngine + Offsets::dwViewAngles);
}

void CEngine::SetViewAngles(Vector &vAngles, bool bClamp) {
	if (bClamp) { Math::ClampAngles(vAngles); }
	Utils::Write<Vector>(Offsets::dwEngine + Offsets::dwViewAngles, vAngles);
}