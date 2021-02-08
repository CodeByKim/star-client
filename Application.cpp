#include "Application.h"

Application::Application()
	: mIsRun(true)	
	, mScreen(SCREEN_WIDTH, SCREEN_HEIGHT)
{

}

bool Application::ConnectServer()
{
	std::wstring ip = InputIpAddress();
	bool isConnect = mNetwork.ConnectServer(ip, SERVER_PORT);

	return isConnect;
}

void Application::Run()
{
	Initialize();

	while (mIsRun)
	{		
		mNetwork.Process();
		Update();

		Render();
		Sleep(30);
	}

	Release();
}

void Application::Initialize()
{

}

std::wstring Application::InputIpAddress()
{	
	/*std::wcout << L"Server IP : ";
	std::wstring ip;
	std::getline(std::wcin, ip);

	return ip;*/

	return L"127.0.0.1";
}

void Application::Update()
{
	
}

void Application::Render()
{
	mScreen.Render(mGame);
}

void Application::Release()
{

}

Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}

Application::~Application()
{

}