#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#include<string>

/// <summary>
/// Packet to initialise the game, number of players and also which player the client is
/// </summary>
struct GameInitPacket
{
	int yourPlayer;
	int numOfPlayers;
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
	int player;
	int playerLifeSpan;
	float popUpTTL; // how long the pop up stays on screen

};

/// <summary>
/// Packet client sends to host to let them know their input
/// </summary>
struct InputPacket
{
	int player;
	float xDirection;
	float yDiretion;
};

/// <summary>
/// Packet for host to send back to clients to let them know of their current position in world
/// </summary>
struct UpdatePacket
{
	int player;
	float x;
	float y;

};

enum class TransmitionStatus { Error = -1, Disconnect, Transmitted  };
class Client
{
	public:
		Client();
		SOCKET m_server;

		GameInitPacket recieveGameInitialisation();

		PlayerInitPacket recievePlayerInitialization();

		void sendClientInput(int playerIndex, float t_xDirection, float t_yDirection);

		UpdatePacket recievePlayerUpdate();

		CollisionPacket recievePossibleCollisionEvent();

	private:
		WSADATA wsData;
		sockaddr_in m_hint;
		const int PORT = 54000;

};

