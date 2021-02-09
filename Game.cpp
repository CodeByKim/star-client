#include "Game.h"
#include "Player.h"

Game::Game()
{
	mMyPlayer = new Player(10, 10, 10);
}

void Game::Update()
{
	// 일단 네트워크에서 패킷 받고	
	// 인풋 받고
	mInput.ProcessInput(*this);
	// 로직 처리
}

void Game::MovePlayer(char key)
{
	mMyPlayer->Move(key);
}

void Game::Draw(ScreenBuffer& screenBuffer)
{
	mMyPlayer->Draw(screenBuffer);

	//나중에는 모든 플레이어 루프돌며 Draw 호출해야 함
}