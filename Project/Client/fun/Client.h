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

class Client
{
	public:
		Client();
		
		/// <summary>
		/// Recieves the Game initizialation packet
		/// </summary>
		/// <returns></returns>
		GameInitPacket recieveGameInitialisation();

		/// <summary>
		/// Recieves the players initizialation packet
		/// </summary>
		/// <returns></returns>
		PlayerInitPacket recievePlayerInitialization();

		/// <summary>
		/// Sends the client the input from the client player
		/// </summary>
		/// <param name="playerIndex"></param>
		/// <param name="t_xDirection"></param>
		/// <param name="t_yDirection"></param>
		void sendClientInput(int playerIndex, float t_xDirection, float t_yDirection);

		/// <summary>
		/// Recieves the update packet for a player
		/// </summary>
		/// <returns></returns>
		UpdatePacket recievePlayerUpdate();

		/// <summary>
		/// Recieves the a possible collision evemt
		/// </summary>
		/// <returns></returns>
		CollisionPacket recievePossibleCollisionEvent();

	private:

		SOCKET m_server;
		WSADATA wsData;
		sockaddr_in m_hint;
		const int PORT = 54000;

};

