#include "Process.h"

void CProcess::Init()
{
    static const wchar_t *wszWindowName = L"Team Fortress 2";

    auto GetProcID = [&]() -> DWORD {
        DWORD dwOut = 0x0;
        GetWindowThreadProcessId(FindWindow(0, wszWindowName), &dwOut);
        return dwOut;
    };

    while (!m_hProcess)
        m_hProcess = OpenProcess(0x38, 0, m_dwProcessID = GetProcID());
}

void CProcess::Free()
{
    CloseHandle(m_hProcess);
}

HANDLE CProcess::GetProcess() const
{
    return m_hProcess;
}

DWORD CProcess::GetProcessID() const
{
    return m_dwProcessID;
}