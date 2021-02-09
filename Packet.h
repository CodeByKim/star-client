#pragma once
#include "CommonLibrary.h"

class Packet
{
public:
	int protocol;
	virtual void Deserialize(char* buffer) = 0;
};

class GetIdPacket : public Packet
{
public:
	void Deserialize(char* buffer) override;

	int id;
};

class CreateStarPacket : public Packet
{
public:
	void Deserialize(char* buffer) override;

	int id;
	int x;
	int y;
};

class RemoveStarPacket : public Packet
{
public:
	void Deserialize(char* buffer) override;

	int id;
};

class MoveStarPacket : public Packet
{
public:
	void Deserialize(char* buffer) override;

	int id;
	int x;
	int y;
};