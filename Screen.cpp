#include "Screen.h"
#include "Game.h"

Screen::Screen(int width, int height)	
	: mWidth(width)
	, mHeight(height)
	, mScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE))
{
	
}

void Screen::Render(Game& game)
{
	game.Draw(mScreenBuffer);
	mScreenBuffer.Print();	
}

Screen::~Screen()
{
	
}