#pragma once
#include "../../../SDK/SDK.h"

class CInput
{
private:
	enum EKeyState { NONE, PRESSED, HELD };
	EKeyState keys[256];
	
public:
	void Update();
	bool IsPressed(int16_t key);
	bool IsHeld(int16_t key);
	bool IsPressedAndHeld(int16_t key);
};

inline CInput g_Input;