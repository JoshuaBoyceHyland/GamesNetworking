#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> //For std::cout, std::endl, std::cin.getline

enum Packet
{
	P_ChatMessage,
	P_Test
};

class Client
{
public: //Public functions

	/// <summary>
	/// initializes winsock and sets up out address info to the given ip address and port
	/// </summary>
	/// <param name="IP">IP address as string</param>
	/// <param name="PORT">Port Num</param>
	Client(std::string IP, int PORT);

	/// <summary>
	/// Tries to connect to given address
	/// </summary>
	/// <returns> returns whether successfull</returns>
	bool Connect();

	/// <summary>
	/// Attempts to send string
	/// </summary>
	/// <param name="_string">String beign sent</param>
	/// <returns>Whether the Sending process was successful</returns>
	bool SendString(std::string & _string);

	/// <summary>
	/// Checks whether the connection has been closed due to an error
	/// </summary>
	/// <returns> If connection has closed</returns>
	bool CloseConnection();

private: //Private functions

	/// <summary>
	/// Processes the chat message in a packet if it is properly recieved 
	/// </summary>
	/// <param name="_packettype"></param>
	/// <returns>Whether it was properly recieved</returns>
	bool ProcessPacket(Packet _packettype);

	/// <summary>
	/// Processes the packet and their type
	/// </summary>
	static void ClientThread();

	//Sending Funcs
	bool sendall(char * data, int totalbytes);
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);
	

	//Getting Funcs
	bool recvall(char * data, int totalbytes);
	bool GetInt(int & _int);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);

private:
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
};

static Client * clientptr; //This client ptr is necessary so that the ClientThread method can access the Client instance/methods. Since the ClientThread method is static, this is the simplest workaround I could think of since there will only be one instance of the client.