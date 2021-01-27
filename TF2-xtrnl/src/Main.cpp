#include "Features/Features.h"

int main()
{
	g_Process.Init();
	
	while (!Offsets::dwClient)
		Offsets::dwClient = Utils::GetModuleAddress(L"client.dll");

	while (!Offsets::dwEngine)
		Offsets::dwEngine = Utils::GetModuleAddress(L"engine.dll");

	while (!GetAsyncKeyState(VK_F11))
	{
		g_Menu.Run();

		if (Utils::IsGameWindowFocused())
		{
			g_EntityCache.Fill();
			{
				g_Aimbot.Run();
				g_Glow.Run();
				g_AutoJump.Run();
			}
			g_EntityCache.Clear();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}

	g_Process.Free();

	return 0;
}