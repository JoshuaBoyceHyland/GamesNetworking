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
	//listen(m_socket, SOMAXCONN);

	m_clients.emplace_back( accept(m_socket, nullptr, nullptr) );

	//closesocket(m_socket);
}

void Host::initializeClient(int clientIndex, GameInitPacket t_outGoingPacket)
{
	send(m_clients[clientIndex], (char*)&t_outGoingPacket, sizeof(t_outGoingPacket), 0);
}

void Host::initializeClientColor(std::vector<PlayerInitPacket> t_outGoingPackets)
{
	for (int i = 0; i < m_clients.size(); i++)
	{
		for (int k = 0; k < t_outGoingPackets.size(); k++)
		{
			send(m_clients[i], (char*)&t_outGoingPackets[k], sizeof(t_outGoingPackets[k]), 0);
		}
	}
	
}

void Host::updateClients(std::vector<UpdatePacket> t_outGoingPackets)
{

	for (int i = 0; i < m_clients.size(); i++)
	{
		// sending out all the packets
		for (int k = 0; k < t_outGoingPackets.size(); k++)
		{
			send(m_clients[i], (char*)&t_outGoingPackets[k], sizeof(t_outGoingPackets[k]), 0);
		}
		
	}
}

void Host::notifyClientsOfCollision(CollisionPacket t_outGoingPacket)
{
	for (int i = 0; i < m_clients.size(); i++)
	{
		send(m_clients[i], (char*)&t_outGoingPacket, sizeof(t_outGoingPacket), 0);
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
