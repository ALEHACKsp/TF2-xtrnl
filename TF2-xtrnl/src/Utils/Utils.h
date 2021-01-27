#pragma once
#include "Math/Math.h"
#include "Process/Process.h"
#include "Color/Color.h"

#include <chrono>
#include <thread>

namespace Utils
{
	template <typename T> inline T Read(const DWORD &dwAddress)
	{
		T Buffer;
		ReadProcessMemory(g_Process.GetProcess(), reinterpret_cast<PVOID>(dwAddress), &Buffer, sizeof(T), nullptr);
		return Buffer;
	}

	template <typename T> inline void Write(const DWORD &dwAddress, const T &Buffer)
	{
		WriteProcessMemory(g_Process.GetProcess(), reinterpret_cast<PVOID>(dwAddress), &Buffer, sizeof(T), nullptr);
	}

	inline DWORD GetModuleAddress(const wchar_t *wszModuleName)
	{
		MODULEENTRY32 ModEntry;
		ModEntry.dwSize = sizeof(MODULEENTRY32);
		HANDLE hSnapshot = CreateToolhelp32Snapshot(0x18, g_Process.GetProcessID());
		Module32First(hSnapshot, &ModEntry);

		while (Module32Next(hSnapshot, &ModEntry))
		{
			if (!wcscmp(ModEntry.szModule, wszModuleName)) {
				CloseHandle(hSnapshot);
				return reinterpret_cast<DWORD>(ModEntry.hModule);
			}
		}

		CloseHandle(hSnapshot);
		return 0x0;
	}

	inline bool IsGameWindowFocused()
	{
		static HWND hwTF2 = 0;

		while (!hwTF2)
			hwTF2 = FindWindowW(0, L"Team Fortress 2");

		return (GetForegroundWindow() == hwTF2);
	}
}