#include "Packet.h"

void GetIdPacket::Deserialize(char* buffer)
{
	CopyMemory(&protocol, buffer + 0, sizeof(int));
	CopyMemory(&id, buffer + 4, sizeof(int));
}

void CreateStarPacket::Deserialize(char* buffer)
{
	CopyMemory(&protocol, buffer + 0, sizeof(int));
	CopyMemory(&id, buffer + 4, sizeof(int));
	CopyMemory(&x, buffer + 8, sizeof(int));
	CopyMemory(&y, buffer + 12, sizeof(int));
}

void RemoveStarPacket::Deserialize(char* buffer)
{
	CopyMemory(&protocol, buffer + 0, sizeof(int));
	CopyMemory(&id, buffer + 4, sizeof(int));
}

void MoveStarPacket::Deserialize(char* buffer)
{
	CopyMemory(&protocol, buffer + 0, sizeof(int));
	CopyMemory(&id, buffer + 4, sizeof(int));
	CopyMemory(&x, buffer + 8, sizeof(int));
	CopyMemory(&y, buffer + 12, sizeof(int));
}