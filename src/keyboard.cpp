/*
		THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
					http://dev-c.com
				(C) Alexander Blade 2015
*/

#include "keyboard.hpp"
#include <natives.h>

const int KEYS_SIZE = 255;

struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = (DWORD)GetTickCount64();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}

const int NOW_PERIOD = 100, MAX_DOWN = 5000; // ms

bool IsKeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? (((DWORD)GetTickCount64() < keyStates[key].time + (DWORD)MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool IsKeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? ((DWORD)GetTickCount64() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}

bool isControllerEnabled()
{
	return !CONTROLS::_IS_INPUT_DISABLED(2);;
}

bool isControllerDown(unsigned int key, bool disabled)
{
	return isControllerEnabled() ? (disabled ? CONTROLS::IS_DISABLED_CONTROL_PRESSED(2, key) : CONTROLS::IS_CONTROL_PRESSED(2, key)) : false;
}

bool isControllerJustDown(unsigned int key, bool disabled)
{
	return isControllerEnabled() ? (disabled ? CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, key) : CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, key)) : false;
}

void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}