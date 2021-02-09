#include "Game.h"

void Game::Update()
{
	// 일단 네트워크에서 패킷 받고
	// 인풋 받고
	mInput.ProcessInput(*this);
	// 로직 처리
}
