#pragma once
#include "CommonLibrary.h"

class Game;

class ICommand
{
public:
	virtual void Execute(Game& game) = 0;
};

class UpKeyCommand : public ICommand
{
public:
	void Execute(Game& game) override;
};

class DownKeyCommand : public ICommand
{
public:
	void Execute(Game& game) override;
};

class LeftKeyCommand : public ICommand
{
public:
	void Execute(Game& game) override;
};

class RightKeyCommand : public ICommand
{
public:
	void Execute(Game& game) override;
};

class Input
{
public:
	Input();
	~Input();

	void ProcessInput(Game& game);

private:	
	bool IsContainCommand(char key);
	std::unordered_map<char, ICommand*> mInputCommands;
};

