#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#include <vector>
#include <string>
struct GameInitPacket
{
	int yourPlayer;
	int numOfPlayers;
};

/// <summary>
/// initialeColor
/// </summary>
struct PlayerInitPacket
{
	int player;
	int color;
	float x;
	float y;
	
};

struct CollisionPacket
{
	bool wasCollision = false;
	int player;
	int playerLifeSpan;
	float popUpTTL;

};

/// <summary>
/// Packet for updating players throught the game
/// </summary>
struct UpdatePacket
{
	int player;
	float x;
	float y;
	float rotation;
	CollisionPacket possibleCollision;
};



class Host
{
	public:
		Host();
		SOCKET m_client;

		void listenForClient();

		void initializeClient(int clientIndex, GameInitPacket t_outGoingPacket);

		void initializeClientColor(std::vector<PlayerInitPacket> t_outGoingPackets);

		void updateClients(std::vector<UpdatePacket> t_outGoingPackets);

		void notifyClientsOfCollision(CollisionPacket t_outGoingPacket);

		std::vector<UpdatePacket> recieveClientData();

		std::vector<SOCKET> m_clients;
		SOCKET m_socket;
	private:
		WSADATA wsData;
		
		sockaddr_in m_hint;

		const int PORT = 54000;
		
};

