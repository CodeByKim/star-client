#include "Network.h"

Network::Network()
	: mSocket(INVALID_SOCKET)
{
	WSADATA data;
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if (result != 0)
	{
		std::wcout << WSAGetLastError() << std::endl;
		return;
	}

	mId = -1;
	mSocket = CreateSocket();
	ZeroMemory(mSendBuffer, PACKET_SIZE);
	ZeroMemory(mRecvBuffer, PACKET_SIZE * 10);

	mTimeout.tv_sec = 0;
	mTimeout.tv_usec = 0;
	
	FD_ZERO(&mReadSet);
	FD_SET(mSocket, &mReadSet);
}

bool Network::ConnectServer(std::wstring_view ip, unsigned short port)
{
	SOCKADDR_IN addr;
	InitializeSocketAddress(ip, port, &addr);

	FD_SET writeSet;
	FD_SET exceptionSet;

	FD_ZERO(&writeSet);
	FD_ZERO(&exceptionSet);

	FD_SET(mSocket, &writeSet);
	FD_SET(mSocket, &exceptionSet);

	TIMEVAL time;
	time.tv_sec = 1;
	time.tv_usec = 0;

	for (int i = 0; i < 3; i++)
	{
		if (connect(mSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK && error != WSAEALREADY)
			{
				std::wcout << L"ERROR : " << error << std::endl;
				return false;
			}
		}

		if (select(0, NULL, &writeSet, &exceptionSet, &time) != SOCKET_ERROR)
		{
			if (FD_ISSET(mSocket, &writeSet))
			{
				std::wcout << L"Connect !" << std::endl;
				return true;
			}

			if (FD_ISSET(mSocket, &exceptionSet))
			{
				std::wcout << L"Select Exception" << std::endl;
				return false;
			}
		}

		FD_SET(mSocket, &writeSet);
	}

	return false;
}

/*
IDÇÒ´ç(0)		Type(4Byte) | ID(4Byte) | ¾È¾¸(4Byte) | ¾È¾¸(4Byte)
º°»ý¼º(1)		Type(4Byte) | ID(4Byte) | X(4Byte)     | Y(4Byte)
º°»èÁ¦(2)		Type(4Byte) | ID(4Byte) | ¾È¾¸(4Byte) | ¾È¾¸(4Byte)
ÀÌµ¿(3)			Type(4Byte) | ID(4Byte) | X(4Byte)     | Y(4Byte)
*/

void Network::MakePacket(char* data)
{
	int protocol = -1;
	CopyMemory(&protocol, data, sizeof(int));

	if (protocol == 0)
	{
		std::cout << "ASSIGN_ID" << std::endl;

		CopyMemory(&mId, data + 4, sizeof(int));

	}
	else if (protocol == 1)
	{
		std::cout << "CREATE_STAR" << std::endl;
		/*CopyMemory(&mId, data + 4, sizeof(int));
		CopyMemory(&mX, data + 8, sizeof(int));
		CopyMemory(&mY, data + 12, sizeof(int));*/
	}
	else if (protocol == 2)
	{

	}
	else if (protocol == 3)
	{
		std::cout << "MOVE_STAR" << std::endl;
		/*CopyMemory(&mId, data + 4, sizeof(int));
		CopyMemory(&mX, data + 8, sizeof(int));
		CopyMemory(&mY, data + 12, sizeof(int));*/
	}
}

int tick = 0;
int delay = 100;
int start = GetTickCount();

void Network::Process()
{
	while (true)
	{		
		select(0, &mReadSet, nullptr, nullptr, &mTimeout);

		if (FD_ISSET(mSocket, &mReadSet))
		{
			int recvCount = recv(mSocket, mRecvBuffer, PACKET_SIZE * 10, 0);
			if (recvCount > 0)
			{
				int packetCount = recvCount / PACKET_SIZE;
				
				for (int i = 0; i < packetCount; i++)
				{
					int offset = PACKET_SIZE * i;

					char data[PACKET_SIZE];
					CopyMemory(data, mRecvBuffer + offset, PACKET_SIZE);

					MakePacket(data);
				}
			}
		}

		auto end = GetTickCount();

		if (end - start > delay)
		{
			//send...
			int proto = 3;
			int id = mId;
			int x = rand() & 80;
			int y = rand() % 23;
			
			CopyMemory(mSendBuffer + 0, &proto, sizeof(int));
			CopyMemory(mSendBuffer + 4, &id, sizeof(int));
			CopyMemory(mSendBuffer + 8, &x, sizeof(int));
			CopyMemory(mSendBuffer + 12, &y, sizeof(int));

			send(mSocket, mSendBuffer, PACKET_SIZE, 0);

			start = GetTickCount();
		}

		ZeroMemory(mRecvBuffer, PACKET_SIZE * 10);
	}	
}

Network& Network::GetInstance()
{
	static Network instance;
	return instance;
}

SOCKET Network::CreateSocket()
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	return sock;
}

void Network::InitializeSocketAddress(std::wstring_view ip, unsigned short port, SOCKADDR_IN* addr)
{
	ZeroMemory(addr, sizeof(SOCKADDR_IN));
	addr->sin_family = AF_INET;
	InetPton(AF_INET, ip.data(), &(addr->sin_addr));
	addr->sin_port = htons(port);
}

Network::~Network()
{
	if (mSocket)
	{
		closesocket(mSocket);
	}

	WSACleanup();
}