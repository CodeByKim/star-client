#pragma once
#include "CommonLibrary.h"
#include "Input.h"

class Player;
class ScreenBuffer;
class Packet;

class Game
{
public:
	Game();
	void Update(std::queue<std::shared_ptr<Packet>>& packets);
	void Draw(ScreenBuffer& screenBuffer);
	void MovePlayer(char key);

private:
	Input mInput;
	Player* mMyPlayer;
};