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
	void ProcessPackets(std::queue<std::shared_ptr<Packet>>& packets);

	void OnConnect(std::shared_ptr<Packet> packet);
	void OnCreateStar(std::shared_ptr<Packet> packet);
	void OnMoveStar(std::shared_ptr<Packet> packet);
	void OnRemoveStar(std::shared_ptr<Packet> packet);

	Input mInput;
	Player* mMyPlayer;
	std::vector<Player*> mPlayers;
};