#include "Application.h"
#include "Packet.h"

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
		std::queue<std::shared_ptr<Packet>> packets;
		GetPackets(packets);		
		Update(packets);
		//Render();

		Sleep(30);
	}

	Release();
}

void Application::Initialize()
{

}

void Application::GetPackets(std::queue<std::shared_ptr<Packet>>& packets)
{	
	while (mNetwork.IsRecvData())
	{
		auto packet = mNetwork.GetPacket();
		packets.push(packet);
	}
}

std::wstring Application::InputIpAddress()
{	
	/*std::wcout << L"Server IP : ";
	std::wstring ip;
	std::getline(std::wcin, ip);

	return ip;*/

	return L"127.0.0.1";
}

void Application::Update(std::queue<std::shared_ptr<Packet>>& packets)
{
	mGame.Update(packets);
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