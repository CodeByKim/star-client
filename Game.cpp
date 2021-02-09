#include "Game.h"
#include "Player.h"
#include "Packet.h"

Game::Game()
	: mMyPlayer(nullptr)
{	
}

void Game::Update(std::queue<std::shared_ptr<Packet>>& packets)
{
	// ��Ŷ ó���ϰ�
	ProcessPackets(packets);

	// ��ǲ �ް�
	mInput.ProcessInput(*this);

	// ���� ó��
}

void Game::ProcessPackets(std::queue<std::shared_ptr<Packet>>& packets)
{
	while (!packets.empty())
	{
		auto packet = packets.front();
		packets.pop();

		switch (packet->protocol)
		{
		case 0:
			OnConnect(packet);
			break;
		case 1:
			OnCreateStar(packet);
			break;
		case 2:
			OnMoveStar(packet);
			break;
		case 3:
			OnRemoveStar(packet);
			break;
		}
	}
}

void Game::MovePlayer(char key)
{
	if (mMyPlayer != nullptr)
	{
		mMyPlayer->Move(key);
	}	
}

void Game::Draw(ScreenBuffer& screenBuffer)
{
	/*if (mMyPlayer != nullptr)
	{
		mMyPlayer->Draw(screenBuffer);
	}*/
	
	for(int i = 0 ; i < mPlayers.size() ; i++)
	{
		mPlayers[i]->Draw(screenBuffer);
	}

	//���߿��� ��� �÷��̾� �������� Draw ȣ���ؾ� ��
}

void Game::OnConnect(std::shared_ptr<Packet> packet)
{
	std::cout << "OnConnect" << std::endl;

	GetIdPacket* pack = (GetIdPacket*)packet.get();
	mMyPlayer = new Player(pack->id);
	mPlayers.push_back(mMyPlayer);	
}

void Game::OnCreateStar(std::shared_ptr<Packet> packet)
{
	std::cout << "OnCreateStar" << std::endl;

	CreateStarPacket* pack = (CreateStarPacket*)packet.get();

	for (int i = 0; i < mPlayers.size(); i++)
	{
		if (mPlayers[i]->GetId() == pack->id)
		{
			mPlayers[i]->SetPos(pack->x, pack->y);
			return;
		}
	}

	Player* player = new Player(pack->id, pack->x, pack->y);
	mPlayers.push_back(player);
}

void Game::OnMoveStar(std::shared_ptr<Packet> packet)
{
	MoveStarPacket* pack = (MoveStarPacket*)packet.get();
}

void Game::OnRemoveStar(std::shared_ptr<Packet> packet)
{
	RemoveStarPacket* pack = (RemoveStarPacket*)packet.get();
}