#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>

enum Packet
{
	P_ChatMessage,
	P_Test
};

class Server
{
public:
	/// <summary>
	/// Initializes winsocka and sets adress info to port number and whether it should broadcast punlicly
	/// </summary>
	/// <param name="PORT">Port number</param>
	/// <param name="BroadcastPublically">Whether to broadcast publially</param>
	Server(int PORT, bool BroadcastPublically = false);

	/// <summary>
	/// Listen for connections to accept
	/// if their is connections it will creat a threat ans send a string of total connections
	/// </summary>
	/// <returns>WHther is got a new connection or not</returns>
	bool ListenForNewConnection();

private:

	//sending / recieving functions  
	bool sendall(int ID, char * data, int totalbytes);
	bool recvall(int ID, char * data, int totalbytes);

	// int sending/ recieving
	bool SendInt(int ID, int _int);
	bool GetInt(int ID, int & _int);

	//Packet type sending/ recieving
	bool SendPacketType(int ID, Packet _packettype);
	bool GetPacketType(int ID, Packet & _packettype);

	//string sending/ recieving
	bool SendString(int ID, std::string & _string);
	bool GetString(int ID, std::string & _string);

	/// <summary>
	/// Processes any new messages 
	/// </summary>
	/// <param name="ID"></param>
	/// <param name="_packettype"></param>
	/// <returns>Whether we recieved any messages</returns>
	bool ProcessPacket(int ID, Packet _packettype);

	/// <summary>
	/// Handles the our connectsion and if we need to close certain sockets
	/// </summary>
	/// <param name="ID"></param>
	static void ClientHandlerThread(int ID);

private:
	SOCKET Connections[100];
	int TotalConnections = 0;
	
	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr);
	SOCKET sListen;
};

static Server * serverptr; //Serverptr is necessary so the static ClientHandler method can access the server instance/functions.
