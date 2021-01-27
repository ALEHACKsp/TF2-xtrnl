#include "Menu.h"
#include "Input/Input.h"
#include "../Vars.h"

#pragma warning (disable : 4018)

bool CMenu::InputBool(const std::wstring &wszName, bool &b)
{
	bool callback = false;
	int x = m_nLastItemX;
	int y = m_nLastItemY;
	std::wstring name = std::wstring(wszName + L": " + (b ? L"On" : L"Off"));

	short color = FG_WHITE;

	if (m_nMouseX >= x && m_nMouseX <= x + name.length() - 1 && m_nMouseY == y)
	{
		if (g_Input.IsPressed(VK_LBUTTON)) {
			b = !b;
			callback = true;
		}

		color = FG_GREEN;
	}

	g_Console.DrawString(x, y, name, color);

	m_nLastItemX = x;
	m_nLastItemY = y + 1;
	return callback;
}

bool CMenu::InputInt(const std::wstring &wszName, int &n, int nMin, int nMax, int nStep)
{
	bool callback = false;
	int x = m_nLastItemX;
	int y = m_nLastItemY;
	std::wstring name = std::wstring(wszName + L": " + std::to_wstring(n).c_str());

	short color = FG_WHITE;

	if (m_nMouseX >= x && m_nMouseX <= x + name.length() - 1 && m_nMouseY == y)
	{
		if (g_Input.IsPressedAndHeld(VK_LBUTTON))
		{
			n -= nStep;

			if (nMin != 0 && nMax != 0)
				n = std::clamp(n, nMin, nMax);

			callback = true;
		}

		if (g_Input.IsPressedAndHeld(VK_RBUTTON))
		{
			n += nStep;

			if (nMin != 0 && nMax != 0)
				n = std::clamp(n, nMin, nMax);

			callback = true;
		}

		color = FG_GREEN;
	}

	g_Console.DrawString(x, y, name, color);

	m_nLastItemX = x;
	m_nLastItemY = y + 1;
	return callback;
}

bool CMenu::InputFloat(const std::wstring &wszName, float &f, float flMin, float flMax, float flStep)
{
	bool callback = false;
	int x = m_nLastItemX;
	int y = m_nLastItemY;
	std::wstring name = std::wstring(wszName + L": " + std::to_wstring(f).c_str());

	short color = FG_WHITE;

	if (m_nMouseX >= x && m_nMouseX <= x + name.length() - 1 && m_nMouseY == y)
	{
		if (g_Input.IsPressedAndHeld(VK_LBUTTON))
		{
			f -= flStep;

			if (flMin != 0.0f && flMax != 0.0f)
				f = std::clamp(f, flMin, flMax);

			callback = true;
		}

		if (g_Input.IsPressedAndHeld(VK_RBUTTON))
		{
			f += flStep;

			if (flMin != 0.0f && flMax != 0.0f)
				f = std::clamp(f, flMin, flMax);

			callback = true;
		}
		
		color = FG_GREEN;
	}

	g_Console.DrawString(x, y, name, color);

	m_nLastItemX = x;
	m_nLastItemY = y + 1;
	return callback;
}

bool CMenu::InputCombo(const std::wstring &wszName, int &n, const std::vector<std::pair<std::wstring, int>> &List)
{
	auto FindCurItemName = [&]() -> const wchar_t *
	{
		for (const auto &Item : List) {
			if (Item.second == n)
				return Item.first.c_str();
		}

		return L"UNKNOWN_ITEM";
	};

	auto FindCurItemIndex = [&]() -> int
	{
		for (size_t i = 0; i < List.size(); i++) {
			if (List[i].second == n)
				return i;
		}

		return 0;
	};

	static std::map<int *, int> indexes = {};
	static std::map<int *, bool> inits = {};

	if (!inits[&n]) {
		indexes[&n] = FindCurItemIndex();
		inits[&n] = true;
	}

	bool callback = false;
	int x = m_nLastItemX;
	int y = m_nLastItemY;
	std::wstring name = std::wstring(wszName + L": " + FindCurItemName());

	short color = FG_WHITE;

	if (m_nMouseX >= x && m_nMouseX <= x + name.length() - 1 && m_nMouseY == y)
	{
		if (g_Input.IsPressed(VK_LBUTTON) && indexes[&n] > 0)
			n = List[--indexes[&n]].second; callback = true;

		if (g_Input.IsPressed(VK_RBUTTON) && indexes[&n] < int(List.size() - 1))
			n = List[++indexes[&n]].second; callback = true;

		color = FG_GREEN;
	}

	g_Console.DrawString(x, y, name, color);

	m_nLastItemX = x;
	m_nLastItemY = y + 1;
	return callback;
}

bool CMenu::Button(const std::wstring &wszName, bool bActive)
{
	bool callback = false;
	int x = m_nLastItemX;
	int y = m_nLastItemY;

	short color = FG_WHITE;

	if (m_nMouseX >= x && m_nMouseX <= x + wszName.length() - 1 && m_nMouseY == y)
	{
		if (g_Input.IsPressed(VK_LBUTTON))
			callback = true;

		color = FG_GREEN;
	}

	if (bActive)
		color = FG_GREEN;

	g_Console.DrawString(x, y, wszName, color);

	m_nLastItemX = x;
	m_nLastItemY = y + 1;
	return callback;
}

void CMenu::Run()
{
	static bool bInitConsole = false;

	if (!bInitConsole) {
		g_Console.Init(L"TF2-xtrnl", 40, 15, L"Verdana", 10, 16);
		bInitConsole = true;
	}

	if (!g_Console.IsInFocus())
		return;

	g_Console.ClearScreen();
	{
		g_Input.Update(); {
			POINT mouse = g_Console.GetMousePos();
			m_nMouseX = mouse.x;
			m_nMouseY = mouse.y;
		}

		m_nLastItemX = 1;
		m_nLastItemY = 1;

		enum struct ETabs { AIMBOT, GLOW, MISC };
		static ETabs Tab = ETabs::AIMBOT;

		if (Button(L"Aimbot", Tab == ETabs::AIMBOT))
			Tab = ETabs::AIMBOT;

		if (Button(L"Glow", Tab == ETabs::GLOW))
			Tab = ETabs::GLOW;

		if (Button(L"Misc", Tab == ETabs::MISC))
			Tab = ETabs::MISC;

		m_nLastItemX = 10;
		m_nLastItemY = 1;

		switch (Tab)
		{
			case ETabs::AIMBOT:
			{
				InputBool(L"Active", Vars::Aimbot::Active);
				InputBool(L"Auto Shoot", Vars::Aimbot::AutoShoot);
				InputBool(L"Aim Players", Vars::Aimbot::AimPlayers);
				InputBool(L"Aim Buildings", Vars::Aimbot::AimBuildings);
				InputCombo(L"Aim Key", Vars::Aimbot::AimKey, { { L"None", 0 }, { L"LShift", VK_LSHIFT }, { L"LButton", VK_LBUTTON } });
				InputCombo(L"Aim Method", Vars::Aimbot::AimMethod, { { L"Normal", 0 }, { L"Smooth", 1 } });
				InputCombo(L"Sort Method", Vars::Aimbot::SortMethod, { { L"FOV", 0 }, { L"Distance", 1 } });
				InputCombo(L"Aim Position", Vars::Aimbot::AimPosition, { { L"Body", 0 }, { L"Head", 1 } });
				InputFloat(L"Aim FOV", Vars::Aimbot::AimFOV, 1.0f, 180.0f);
				InputFloat(L"Aim Smoothing", Vars::Aimbot::Smoothing, 1.0f, 3.0f);
				break;
			}

			case ETabs::GLOW:
			{
				InputBool(L"Active", Vars::Glow::Active);
				InputBool(L"Glow Players", Vars::Glow::GlowPlayers);
				InputBool(L"Glow Buildings", Vars::Glow::GlowBuildings);
				break;
			}

			case ETabs::MISC:
			{
				InputBool(L"Auto Jump", Vars::Misc::AutoJump);
				break;
			}
		}
	}
	g_Console.DrawScreen();
}