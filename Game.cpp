#include "Game.h"
#include "Player.h"
#include "Packet.h"

Game::Game()
{
	mMyPlayer = new Player(10, 10, 10);
}

void Game::Update(std::queue<std::shared_ptr<Packet>>& packets)
{
	while (!packets.empty())
	{
		auto packet = packets.front();
		packets.pop();

		std::cout << packet->protocol << std::endl;
	}

	// ��ǲ �ް�
	mInput.ProcessInput(*this);
	// ���� ó��
}

void Game::MovePlayer(char key)
{
	mMyPlayer->Move(key);
}

void Game::Draw(ScreenBuffer& screenBuffer)
{
	mMyPlayer->Draw(screenBuffer);

	//���߿��� ��� �÷��̾� �������� Draw ȣ���ؾ� ��
}