#pragma once
#include "CommonLibrary.h"

class ScreenBuffer
{
public:
	ScreenBuffer(HANDLE consoleHandle);

	void SetSprite(int x, int y, char sprite);
	void Print();
	void Clear();

private:
	void MoveCursor(short x, short y);
	void InvisibleCursor();

	char mScreenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	HANDLE mConsoleHandle;
};

