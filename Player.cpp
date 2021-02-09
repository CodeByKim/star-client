#include "Player.h"
#include "ScreenBuffer.h"

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
}

void Player::Draw(ScreenBuffer& screenBuffer)
{
	screenBuffer.SetSprite(mX, mY, '*');
}