#include "Host.h"

Host::Host()
{

	WSAStartup(MAKEWORD(2, 2), &wsData);

	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(PORT);
	m_hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(m_socket, (sockaddr*)&m_hint, sizeof(m_hint));

	listen(m_socket, SOMAXCONN);

	m_client = accept(m_socket, nullptr, nullptr);

	closesocket(m_socket);
}

void Host::listenForClient()
{


}

void Host::updateClients()
{
}
