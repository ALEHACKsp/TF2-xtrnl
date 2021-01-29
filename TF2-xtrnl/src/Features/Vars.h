#pragma once
#include <Windows.h>

#define VAR(name, value) inline auto name = value

namespace Vars
{
	namespace Aimbot
	{
		VAR(Active, true);
		VAR(AutoShoot, false);
		VAR(AimPlayers, true);
		VAR(AimBuildings, true);
		VAR(AimKey, VK_LSHIFT);
		VAR(AimMethod, 0); //0 Normal, 1 Smooth
		VAR(SortMethod, 0); //0 FOV, 1 Distance
		VAR(AimPosition, 2); //0 Body, 1 Head, 2 Auto
		VAR(AimFOV, 15.0f);
		VAR(Smoothing, 1.0f);
	}

	namespace Glow
	{
		VAR(Active, false);
	}

	namespace Misc
	{
		VAR(AutoJump, true);
		VAR(AutoBackstab, false);
	}
}

#undef VAR