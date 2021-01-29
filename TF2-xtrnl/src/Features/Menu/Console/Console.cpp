#include "Console.h"

//credits to Javidx9!

#pragma warning (disable : 4305)
#pragma warning (disable : 4309)

void CConsole::Init(const wchar_t *wszTitle, int nWidth, int nHeight, const wchar_t *wszFont, int nFontWidth, int nFontHeight)
{
	m_hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	m_nScreenWidth = nWidth;
	m_nScreenHeight = nHeight;

	m_nFontWidth = nFontWidth;
	m_nFontHeight = nFontHeight;

	HWND hwConsole = GetConsoleWindow();
	SetWindowLong(hwConsole, GWL_STYLE, GetWindowLong(hwConsole, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	CONSOLE_CURSOR_INFO CCI = {};
	GetConsoleCursorInfo(m_hConsoleOut, &CCI);
	CCI.bVisible = false;
	SetConsoleCursorInfo(m_hConsoleOut, &CCI);

	SetConsoleTitleW(wszTitle);

	SMALL_RECT m_Window = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(m_hConsoleOut, TRUE, &m_Window);

	SetConsoleScreenBufferSize(m_hConsoleOut, { static_cast<short>(nWidth), static_cast<short>(nHeight) });

	SetConsoleActiveScreenBuffer(m_hConsoleOut);

	CONSOLE_FONT_INFOEX CFI = {};
	CFI.cbSize = sizeof(CFI);
	CFI.nFont = 0;
	CFI.dwFontSize.X = nFontWidth;
	CFI.dwFontSize.Y = nFontHeight;
	CFI.FontFamily = FF_DONTCARE;
	CFI.FontWeight = 400;

	wcscpy_s(CFI.FaceName, wszFont);
	SetCurrentConsoleFontEx(m_hConsoleOut, false, &CFI);

	m_Window = { 0, 0, static_cast<short>(nWidth) - 1, static_cast<short>(nHeight) - 1 };
	SetConsoleWindowInfo(m_hConsoleOut, TRUE, &m_Window);

	SetConsoleMode(m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

	m_Screen = new CHAR_INFO[nWidth * nHeight];
	memset(m_Screen, 0, sizeof(CHAR_INFO) * nWidth * nHeight);
}

void CConsole::DrawScreen()
{
	SMALL_RECT WriteRegion = { 0, 0, static_cast<short>(m_nScreenWidth) - 1, static_cast<short>(m_nScreenHeight) - 1 };
	WriteConsoleOutputW(m_hConsoleOut, m_Screen, { static_cast<short>(m_nScreenWidth), static_cast<short>(m_nScreenHeight) }, { 0, 0 }, &WriteRegion);
}

void CConsole::ClearScreen()
{
	Fill(0, 0, m_nScreenWidth, m_nScreenHeight, 0);
}

void CConsole::DrawChar(int x, int y, char c, short col)
{
	if (x >= 0 && x < m_nScreenWidth && y >= 0 && y < m_nScreenHeight) {
		m_Screen[y * m_nScreenWidth + x].Char.UnicodeChar = c;
		m_Screen[y * m_nScreenWidth + x].Attributes = col;
	}
}

void CConsole::DrawString(int x, int y, const std::wstring &s, short col)
{
	for (size_t i = 0; i < s.size(); i++) {
		m_Screen[y * m_nScreenWidth + x + i].Char.UnicodeChar = s[i];
		m_Screen[y * m_nScreenWidth + x + i].Attributes = col;
	}
}

void CConsole::Fill(int x1, int y1, int x2, int y2, short col)
{
	auto Clip = [&](int &x, int &y) -> void {
		if (x < 0) x = 0;
		if (x >= m_nScreenWidth) x = m_nScreenWidth;
		if (y < 0) y = 0;
		if (y >= m_nScreenHeight) y = m_nScreenHeight;
	};

	Clip(x1, y1);
	Clip(x2, y2);

	for (int x = x1; x < x2; x++)
		for (int y = y1; y < y2; y++)
			DrawChar(x, y, (char)178, col);
}

POINT CConsole::GetMousePos()
{
	static HWND hwConsole = GetConsoleWindow();
	POINT p = {};
	GetCursorPos(&p);
	ScreenToClient(hwConsole, &p);
	p.x /= (m_nFontWidth - 1);
	p.y /= m_nFontHeight;
	return p;
}

bool CConsole::IsInFocus()
{
	return GetForegroundWindow() == GetConsoleWindow();
}