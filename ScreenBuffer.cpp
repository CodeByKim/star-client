#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(HANDLE consoleHandle)
	: mConsoleHandle(consoleHandle)
{
	InvisibleCursor();
	Clear();
}

void ScreenBuffer::SetSprite(int x, int y, char sprite)
{
	mScreenBuffer[y][x] = sprite;
}

void ScreenBuffer::Print()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		MoveCursor(0, i);
		printf(mScreenBuffer[i]);
	}

	Clear();
}

void ScreenBuffer::Clear()
{
	memset(mScreenBuffer, ' ', SCREEN_WIDTH * SCREEN_HEIGHT);

	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		mScreenBuffer[i][SCREEN_WIDTH - 1] = '\0';
	}
}

void ScreenBuffer::MoveCursor(short x, short y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(mConsoleHandle, pos);
}

void ScreenBuffer::InvisibleCursor()
{
	CONSOLE_CURSOR_INFO stConsoleCursor;
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(mConsoleHandle, &stConsoleCursor);
}