#include "Host.h"

Host::Host()
{

	WSAStartup(MAKEWORD(2, 2), &wsData);

	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(PORT);
	m_hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(m_socket, (sockaddr*)&m_hint, sizeof(m_hint));


}

void Host::listenForClient()
{
	listen(m_socket, SOMAXCONN);

	m_clients.emplace_back( accept(m_socket, nullptr, nullptr) );

	closesocket(m_socket);
}

void Host::initializeClientColor(int t_clientIndex, int t_color)
{
	InitializePacket outgoingPacket = { t_color };

	send(m_clients[t_clientIndex], (char*)&outgoingPacket, sizeof(outgoingPacket), 0);
}

void Host::updateClients(float t_x, float t_y, float t_rotation)
{
	UpdatePacket outGoingPacket = { t_x, t_y, t_rotation };

	for (int i = 0; i < m_clients.size(); i++)
	{
		send(m_clients[i], (char*)&outGoingPacket, sizeof(outGoingPacket), 0);
	}
}

std::vector<UpdatePacket> Host::recieveClientData()
{
	UpdatePacket currentPacket;
	std::vector<UpdatePacket> incomingPackets;

	for (int i = 0; i < m_clients.size(); i++)
	{
		recv(m_clients[i], (char*)&currentPacket, sizeof(currentPacket), 0);
		incomingPackets.push_back(currentPacket);
	}

	return incomingPackets;
}
