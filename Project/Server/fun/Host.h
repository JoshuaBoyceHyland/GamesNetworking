#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#include <vector>
#include <string>

/// <summary>
/// Packet to initialise the game, number of players and also which player the client is
/// </summary>
struct GameInitPacket
{
	int yourPlayer;
	int numOfPlayers;
	int chaser;
};

/// <summary>
/// initializes all the players color and start position
/// </summary>
struct PlayerInitPacket
{
	int player;
	int color;
	float x;
	float y;
	
};

/// <summary>
/// Packet to let clients know if there is a collision, who collided with the chaser and also how long they lasted with out being caught
/// </summary>
struct CollisionPacket
{
	bool wasCollision = false;
	bool gameOver = false;
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

};

/// <summary>
/// Packet client sends to host to let them know their input
/// </summary>
struct InputPacket
{
	int player;
	float xDirection;
	float yDirection;
};


class Host
{
	public:
		Host();
		SOCKET m_client;

		/// <summary>
		/// Listen for client
		/// </summary>
		void listenForClient();

		/// <summary>
		/// Sent client the game initilization packet
		/// </summary>
		/// <param name="clientIndex"> The index of the client which is offset by 1</param>
		/// <param name="t_outGoingPacket">Game initilization packet</param>
		void initializeClient(int clientIndex, GameInitPacket t_outGoingPacket);

		/// <summary>
		/// Initializes the players in every clients game with a color and position
		/// </summary>
		/// <param name="t_outGoingPackets">Intiialition packet</param>
		void initializeClientsPlayers(std::vector<PlayerInitPacket> t_outGoingPackets);

		/// <summary>
		/// This updates the clients with the position of players 
		/// </summary>
		/// <param name="t_outGoingPackets">Updating packet</param>
		void updateClients(std::vector<UpdatePacket> t_outGoingPackets);

		/// <summary>
		/// THis notifies clients of a collision event and whether it happened or not
		/// </summary>
		/// <param name="t_outGoingPacket">Collision packet</param>
		void notifyClientsOfCollision(CollisionPacket t_outGoingPacket);

		/// <summary>
		/// This function listends for clients inputs
		/// </summary>
		/// <returns> A vector of all the clients inptus</returns>
		std::vector<InputPacket> recieveClientData();

		/// <summary>
		/// Vector of clients
		/// </summary>
		std::vector<SOCKET> m_clients;

		/// <summary>
		/// Our socket
		/// </summary>
		SOCKET m_socket;
	private:

		WSADATA wsData;
		
		sockaddr_in m_hint;

		const int PORT = 54000;
		
};

