#pragma once
#include "CommonLibrary.h"

class Game;

class Screen
{
public:
	Screen(int width, int height);
	~Screen();
	void Render(Game& game);

private:
	void MoveCursor(short x, short y);
	void ClearScreen();
	void InvisibleCursor();

	int mWidth;
	int mHeight;
	//char** mScreenBuffer;
	char mScreenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	HANDLE mConsoleHandle;
};

