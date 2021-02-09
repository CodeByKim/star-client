#pragma once
#include "CommonLibrary.h"

class Packet;

class Network
{
public:
	Network();
	~Network();

	bool IsRecvData();
	std::shared_ptr<Packet> GetPacket();
	bool ConnectServer(std::wstring_view ip, unsigned short port);
	//static Network& GetInstance();

private:
	SOCKET CreateSocket();
	void InitializeSocketAddress(std::wstring_view ip, unsigned short port, SOCKADDR_IN* addr);
	//void MakePacket(char* data);

	SOCKET mSocket;
	TIMEVAL mTimeout;
	FD_SET mReadSet;
	
	int mOffset;
	int mRemainRecvCount;
	char mRecvBuffer[PACKET_SIZE * 10];
	/*int mId;
	int mX;
	int mY;	*/
};