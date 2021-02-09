#include "Game.h"
#include "Player.h"

Game::Game()
{
	mMyPlayer = new Player(10, 10, 10);
}

void Game::Update()
{
	// �ϴ� ��Ʈ��ũ���� ��Ŷ �ް�	
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