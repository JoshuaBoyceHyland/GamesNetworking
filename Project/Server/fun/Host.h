#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#include <vector>

/// <summary>
/// initialeColor
/// </summary>
struct InitializePacket
{
	int color;
};

/// <summary>
/// Packet for updating players throught the game
/// </summary>
struct UpdatePacket
{
	float x;
	float y;
	float rotation;

};

class Host
{
	public:
		Host();
		SOCKET m_client;

		void listenForClient();

		void initializeClientColor( int t_clientIndex, int t_color);

		void updateClients(float t_x, float t_y, float t_rotation);

		std::vector<UpdatePacket> recieveClientData();

		std::vector<SOCKET> m_clients;

	private:
		WSADATA wsData;
		SOCKET m_socket;
		sockaddr_in m_hint;

		const int PORT = 54000;
		
};

