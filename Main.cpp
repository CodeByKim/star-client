#include "CommonLibrary.h"
#include "Application.h"

int main()
{		
	if (Application::GetInstance().ConnectServer())
	{
		Application::GetInstance().Run();
	}
}