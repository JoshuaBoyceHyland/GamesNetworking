#include "Client.h"

Client::Client()
{

	WSAStartup(MAKEWORD(2, 2), &wsData);

	m_server = socket(AF_INET, SOCK_STREAM, 0);

	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(PORT);
	m_hint.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");



	connect(m_server, (sockaddr*)&m_hint, sizeof(m_hint));


}

GameInitPacket Client::recieveGameInitialisation()
{
	bool dataRecieved = false;
	GameInitPacket initPacket;

	while (!dataRecieved)
	{
		if (-1 != recv(m_server, (char*)&initPacket, sizeof(initPacket), 0))
		{
			dataRecieved = true;
		}
	}


	return initPacket;
}

PlayerInitPacket Client::recievePlayerInitialization()
{
	bool dataRecieved = false;
	PlayerInitPacket playerInitPacket;

	while (!dataRecieved)
	{
		if (-1 != recv(m_server, (char*)&playerInitPacket, sizeof(playerInitPacket), 0))
		{
			dataRecieved = true;
		}
	}

	return playerInitPacket;
}

void Client::sendClientInput(int playerIndex, float t_xDirection, float t_yDirection)
{
	InputPacket inputPacket = { playerIndex, t_xDirection, t_yDirection };

	send( m_server, (char*)&inputPacket, sizeof(inputPacket), 0);

}

UpdatePacket Client::recievePlayerUpdate()
{
	bool dataRecieved = false;
	UpdatePacket playerUpdatePacket;
	
	
	if (-1 != recv(m_server, (char*)&playerUpdatePacket, sizeof(playerUpdatePacket), 0))
	{
		dataRecieved = true;
	}


	return playerUpdatePacket;
}

CollisionPacket Client::recievePossibleCollisionEvent()
{
	bool dataRecieved = false;
	CollisionPacket possibleCollision;


	
	if (-1 != recv(m_server, (char*)&possibleCollision, sizeof(possibleCollision), 0))
	{
		dataRecieved = true;
	}
	

	return possibleCollision;
}
