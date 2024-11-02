#define _WINSOCK_DEPRECATED_NO_WARNINGS // use as some functions in sampe code have deprecated
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

int main()
{
	SOCKET s;

	// Address for server and client 
	struct sockaddr_in server, si_other;

	int slen, recv_len; // lengths
	char buf[BUFLEN]; // buffer
	WSADATA wsa; // structure that stores info about the winsock implementation

	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");


	// Initialize Winsock
	// must be called before the use of any winsock functions ( creating sockets or connecting to servers)
	// MAKEWORD: macro that creats a version number for winsock to use
	// MAKEWORD: the paramets 2, 2 means its requesting 2.2
	// &wsa: points to the data thate will be filled in by the function
	// 0 will be returned if this fails
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	// and check it is valide
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET; // wil use  IPv4 addresses
	server.sin_addr.s_addr = INADDR_ANY; //  server will listen for packets sent to any of the computer's IP addresses
	server.sin_port = htons(PORT); // holds port number

	//Bindomh our socket to server and checking for errors
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	//keep listening for data
	while (1)
	{
		printf("Waiting for data...");
		// flushed output buffer
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n", buf);

		//now reply the client with the same data
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}