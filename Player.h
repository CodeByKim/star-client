#pragma once
#include "CommonLibrary.h"

class ScreenBuffer;

class Player
{
public:
	Player(int id);
	Player(int id, int x, int y);
	~Player();

	void Move(char key);
	void Draw(ScreenBuffer& screenBuffer);
private:
	int mId;
	int mX;
	int mY;
};

