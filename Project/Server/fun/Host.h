#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#include <vector>
struct Packet
{
	float x;
	float y;

};

class Host
{
	public:
		Host();
		SOCKET m_client;
		void listenForClient();

		void updateClients();

		std::vector<SOCKET> m_clients;
	private:
		WSADATA wsData;
		SOCKET m_socket;
		sockaddr_in m_hint;

		const int PORT = 54000;
		
		
};

