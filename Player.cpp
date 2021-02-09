#include "Player.h"
#include "ScreenBuffer.h"
#include "Application.h"

Player::Player(int id)
	: mId(id)
	, mX(-1)
	, mY(-1)
{	
}

Player::Player(int id, int x, int y)
	: mId(id)
	, mX(x)
	, mY(y)
{

}

Player::~Player()
{

}

void Player::Move(char key)
{
	if (key == UP_KEY)
	{
		mY -= 1;
	}
	else if (key == DOWN_KEY)
	{
		mY += 1;
	}
	else if (key == LEFT_KEY)
	{
		mX -= 1;
	}
	else if (key == RIGHT_KEY)
	{
		mX += 1;
	}

	int proto = 3;
	char buffer[PACKET_SIZE];
	CopyMemory(buffer, &proto, sizeof(int));
	CopyMemory(buffer + 4, &mId, sizeof(int));
	CopyMemory(buffer + 8, &mX, sizeof(int));
	CopyMemory(buffer + 12, &mY, sizeof(int));

	Application::GetInstance().Send(buffer);
}

void Player::Draw(ScreenBuffer& screenBuffer)
{
	screenBuffer.SetSprite(mX, mY, '*');
}