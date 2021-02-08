#pragma once
#include "CommonLibrary.h"
#include "Network.h"
#include "Screen.h"

class Application
{
public:
	Application();
	~Application();

	bool ConnectServer();
	void Run();	

	static Application& GetInstance();

private:
	void Initialize();
	std::wstring InputIpAddress();
	void Update();
	void Render();
	void Release();

	Network mNetwork;
	Screen mScreen;	
	bool mIsRun;
};

