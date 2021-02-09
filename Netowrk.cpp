#include "Network.h"
#include "Packet.h"

Network::Network()
	: mSocket(INVALID_SOCKET)
	, mOffset(0)
	, mRemainRecvCount(0)
{
	WSADATA data;
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if (result != 0)
	{
		std::wcout << WSAGetLastError() << std::endl;
		return;
	}
	
	mSocket = CreateSocket();

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

bool Network::IsRecvData()
{
	if (mRemainRecvCount > 0)
	{
		return true;
	}

	if (select(0, &mReadSet, nullptr, nullptr, &mTimeout) != 0)
	{		
		if (FD_ISSET(mSocket, &mReadSet))
		{
			int recvCount = recv(mSocket, mRecvBuffer, PACKET_SIZE * 10, 0);
			mRemainRecvCount += recvCount;
			mOffset = 0;
			return true;
		}
	}

	return false;
}

std::shared_ptr<Packet> Network::GetPacket()
{
	int protocol = -1;
	std::shared_ptr<Packet> packet;
	CopyMemory(&protocol, mRecvBuffer, sizeof(int));

	switch (protocol)
	{
	case 0:
		packet = std::make_shared<GetIdPacket>();
		packet->Deserialize(mRecvBuffer + mOffset);
		break;
	case 1:
		packet = std::make_shared<CreateStarPacket>();
		packet->Deserialize(mRecvBuffer + mOffset);
		break;
	case 2:
		packet = std::make_shared<RemoveStarPacket>();
		packet->Deserialize(mRecvBuffer + mOffset);
		break;
	case 3:
		packet = std::make_shared<MoveStarPacket>();
		packet->Deserialize(mRecvBuffer + mOffset);
		break;
	}

	mRemainRecvCount -= PACKET_SIZE;
	mOffset += PACKET_SIZE;
	return packet;
}

//Network& Network::GetInstance()
//{
//	static Network instance;
//	return instance;
//}

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