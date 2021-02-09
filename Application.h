#pragma once
#include "CommonLibrary.h"
#include "Network.h"
#include "Screen.h"
#include "Game.h"

class Application
{
public:
	Application();
	~Application();

	bool ConnectServer();
	void Run();	
	void Send(char* buffer);

	static Application& GetInstance();

private:
	void Initialize();
	std::wstring InputIpAddress();

	void GetPackets(std::queue<std::shared_ptr<Packet>>& packets);
	void Update(std::queue<std::shared_ptr<Packet>>& packets);
	void Render();
	void Release();

	Network mNetwork;
	Screen mScreen;	
	Game mGame;
	bool mIsRun;
};

