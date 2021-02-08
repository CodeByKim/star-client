#include "CommonLibrary.h"
#include "Application.h"

int main()
{		
	/*std::wcout << L"Server IP : ";
	std::wstring ip;
	std::getline(std::wcin, ip);

	if (Network::GetInstance().ConnectServer(ip, SERVER_PORT))
	{
		Network::GetInstance().Process();
	}*/

	if (Application::GetInstance().ConnectServer())
	{
		Application::GetInstance().Run();
	}
}