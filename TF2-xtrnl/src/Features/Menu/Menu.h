#pragma once
#include "Console/Console.h"
#include <vector>

class CMenu
{
private:
	int m_nMouseX, m_nMouseY;
	int m_nLastItemX, m_nLastItemY;

private:
	bool InputBool(const std::wstring &wszName, bool &b);
	bool InputInt(const std::wstring &wszName, int &n, int nMin = 0, int nMax = 0, int nStep = 1);
	bool InputFloat(const std::wstring &wszName, float &f, float flMin = 0, float flMax = 0, float flStep = 1.0f);
	bool InputCombo(const std::wstring &wszName, int &n, const std::vector<std::pair<std::wstring, int>> &List);
	bool Button(const std::wstring &wszName, bool bActive = false);

public:
	void Run();
};

inline CMenu g_Menu;