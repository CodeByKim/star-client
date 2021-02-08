#include "Screen.h"
#include "Game.h"

Screen::Screen(int width, int height)	
	: mWidth(width)
	, mHeight(height)
{
	ClearScreen();
	
	mConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	InvisibleCursor();
}

void Screen::Render(Game& game)
{
	//game.Draw(mScreenBuffer);

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		MoveCursor(0, i);
		printf(mScreenBuffer[i]);
	}

	ClearScreen();
}

void Screen::MoveCursor(short x, short y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(mConsoleHandle, pos);
}

void Screen::ClearScreen()
{
	memset(mScreenBuffer, '&', SCREEN_WIDTH * SCREEN_HEIGHT);

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		mScreenBuffer[i][SCREEN_WIDTH - 1] = '\0';
	}
}

void Screen::InvisibleCursor()
{
	CONSOLE_CURSOR_INFO stConsoleCursor;
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(mConsoleHandle, &stConsoleCursor);
}

Screen::~Screen()
{
	
}