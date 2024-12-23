#include "Client.h"

Client::Client()
{

	WSAStartup(MAKEWORD(2, 2), &wsData);

	m_server = socket(AF_INET, SOCK_STREAM, 0);

	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(PORT);
	m_hint.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");



	connect(m_server, (sockaddr*)&m_hint, sizeof(m_hint));


}
