#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#include<string>
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

struct UpdatePacket
{
	int player;
	float x;
	float y;
	float rotation;
	CollisionPacket possibleCollision;

};



class Client
{
	public:
		Client();
		SOCKET m_server;

	private:
		WSADATA wsData;
		sockaddr_in m_hint;
		const int PORT = 54000;

};

