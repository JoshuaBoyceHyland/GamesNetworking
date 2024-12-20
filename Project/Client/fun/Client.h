#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

/// <summary>
/// initialeColor
/// </summary>
struct InitializePacket
{
	int color;
};


struct UpdatePacket
{
	float x;
	float y;
	float rotation;

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

