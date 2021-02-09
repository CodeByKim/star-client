#pragma once
#include "CommonLibrary.h"
#include "Input.h"

class Player;
class ScreenBuffer;

class Game
{
public:
	Game();
	void Update();
	void Draw(ScreenBuffer& screenBuffer);
	void MovePlayer(char key);

private:
	Input mInput;
	Player* mMyPlayer;
};