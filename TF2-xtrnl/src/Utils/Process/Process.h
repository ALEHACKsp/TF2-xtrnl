#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class CProcess
{
private:
	HANDLE m_hProcess;
	DWORD m_dwProcessID;

public:
	void Init();
	void Free();
	HANDLE GetProcess() const;
	DWORD GetProcessID() const;
};

inline CProcess g_Process;