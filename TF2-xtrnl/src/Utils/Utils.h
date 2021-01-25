#pragma once
#include "Math/Math.h"
#include "Process/Process.h"
#include "Color/Color.h"

#include <chrono>

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

	inline Color_t Rainbow()
	{
		static auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		float flElapsed = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 300.0f;

		return
		{
			static_cast<byte>(floor(sin(flElapsed + 0.0f) * 127.0f + 128.0f)),
			static_cast<byte>(floor(sin(flElapsed + 2.0f) * 127.0f + 128.0f)),
			static_cast<byte>(floor(sin(flElapsed + 4.0f) * 127.0f + 128.0f)),
			255
		};
	};
}