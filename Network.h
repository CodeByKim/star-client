#pragma once
#include "CommonLibrary.h"

class Network
{
public:
	Network();
	~Network();

	void Process();
	bool ConnectServer(std::wstring_view ip, unsigned short port);
	static Network& GetInstance();

private:
	SOCKET CreateSocket();
	void InitializeSocketAddress(std::wstring_view ip, unsigned short port, SOCKADDR_IN* addr);
	void MakePacket(char* data);

	SOCKET mSocket;
	TIMEVAL mTimeout;
	FD_SET mReadSet;

	int mId;
	int mX;
	int mY;

	char mSendBuffer[PACKET_SIZE];
	char mRecvBuffer[PACKET_SIZE * 10];
};