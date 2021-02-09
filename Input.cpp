#include "Input.h"
#include "Game.h"

void UpKeyCommand::Execute(Game& game)
{
	game.MovePlayer(UP_KEY);
}

void DownKeyCommand::Execute(Game& game)
{
	game.MovePlayer(DOWN_KEY);
}

void LeftKeyCommand::Execute(Game& game)
{
	game.MovePlayer(LEFT_KEY);
}

void RightKeyCommand::Execute(Game& game)
{
	game.MovePlayer(RIGHT_KEY);	
}

Input::Input()
{
	mInputCommands.insert(std::make_pair(UP_KEY, new UpKeyCommand()));
	mInputCommands.insert(std::make_pair(DOWN_KEY, new DownKeyCommand()));
	mInputCommands.insert(std::make_pair(LEFT_KEY, new LeftKeyCommand()));
	mInputCommands.insert(std::make_pair(RIGHT_KEY, new RightKeyCommand()));
}

Input::~Input()
{
	for (auto iter = mInputCommands.begin(); iter != mInputCommands.end(); ++iter)
	{
		delete iter->second;		
	}
}

void Input::ProcessInput(Game& game)
{
	if (GetAsyncKeyState(UP_KEY) & 0x8000)
	{
		if (IsContainCommand(UP_KEY))
			mInputCommands[UP_KEY]->Execute(game);
	}

	if (GetAsyncKeyState(DOWN_KEY) & 0x8000)
	{
		if (IsContainCommand(DOWN_KEY))
			mInputCommands[DOWN_KEY]->Execute(game);
	}

	if (GetAsyncKeyState(LEFT_KEY) & 0x8000)
	{
		if (IsContainCommand(LEFT_KEY))
			mInputCommands[LEFT_KEY]->Execute(game);
	}

	if (GetAsyncKeyState(RIGHT_KEY) & 0x8000)
	{
		if (IsContainCommand(RIGHT_KEY))
			mInputCommands[RIGHT_KEY]->Execute(game);
	}
}

bool Input::IsContainCommand(char key)
{
	auto iter = mInputCommands.find(key);
	return iter != mInputCommands.end();
}