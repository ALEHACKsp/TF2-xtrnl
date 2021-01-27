#include "Input.h"

#pragma warning (disable : 26812)

void CInput::Update()
{
	for (int n = 0; n < 256; n++)
	{
		if (GetKeyState(n) & 0x8000)
		{
			if (keys[n] == PRESSED)
				keys[n] = HELD;

			else if (keys[n] != HELD)
				keys[n] = PRESSED;
		}

		else keys[n] = NONE;
	}
}

bool CInput::IsPressed(int16_t key)
{
    return (keys[key] == PRESSED);
}

bool CInput::IsHeld(int16_t key)
{
    return (keys[key] == HELD);
}

bool CInput::IsPressedAndHeld(int16_t key)
{
	EKeyState key_state = keys[key];

	static std::chrono::time_point<std::chrono::steady_clock> start[256] = { std::chrono::steady_clock::now() };

	if (key_state == PRESSED)
	{
		start[key] = std::chrono::steady_clock::now();
		return true;
	}

	if (key_state == HELD && std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now() - start[key]).count() > 400)
		return true;

	return false;
}