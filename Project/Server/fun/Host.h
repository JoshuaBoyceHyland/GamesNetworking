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

/// <summary>
/// Packet for updating players throught the game
/// </summary>
struct UpdatePacket
{
	int player;
	float x;
	float y;
	float rotation;
	bool active;
};

struct CollisionPacket
{
	int player;
	std::string popUpString;

};

class Host
{
	public:
		Host();
		SOCKET m_client;

		void listenForClient();

		void initializeClient(GameInitPacket t_outGoingPacket);

		void initializeClientColor(std::vector<PlayerInitPacket> t_outGoingPackets);

		void updateClients(std::vector<UpdatePacket> t_outGoingPackets);

		std::vector<UpdatePacket> recieveClientData();

		std::vector<SOCKET> m_clients;

	private:
		WSADATA wsData;
		SOCKET m_socket;
		sockaddr_in m_hint;

		const int PORT = 54000;
		
};

