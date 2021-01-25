#include "Features/Features.h"

int main()
{
	SetConsoleTitle(L"TF2-xtrnl");
	g_Process.Init();
	
	while (!Offsets::dwClient)
		Offsets::dwClient = Utils::GetModuleAddress(L"client.dll");

	while (!Offsets::dwEngine)
		Offsets::dwEngine = Utils::GetModuleAddress(L"engine.dll");

	while (!GetAsyncKeyState(VK_F11))
	{
		g_EntityCache.Fill();		
		{
			g_AutoJump.Run();
			g_Glow.Run();
			g_Aimbot.Run();
		}
		g_EntityCache.Clear();
	}

	g_Process.Free();
	return 0;
}