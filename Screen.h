#pragma once
#include "CommonLibrary.h"
#include "ScreenBuffer.h"
class Game;

class Screen
{
public:
	Screen(int width, int height);
	~Screen();
	void Render(Game& game);

private:	
	void InvisibleCursor();

	int mWidth;
	int mHeight;		
	ScreenBuffer mScreenBuffer;
	//HANDLE mConsoleHandle;
};

