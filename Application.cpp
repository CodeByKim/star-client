#include "Application.h"

Application::Application()
	: mIsRun(true)
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
		//패킷을 만들어서 가져온 뒤
		//std::vector<Packet*>* packets = mNetwork.GetPackets();

		//로직에 만든 패킷을 넘겨준다.
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
	std::wcout << L"Server IP : ";
	std::wstring ip;
	std::getline(std::wcin, ip);

	return ip;
}

void Application::Update()
{
	
}

void Application::Render()
{
	//mScreen.Render(mGame);
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