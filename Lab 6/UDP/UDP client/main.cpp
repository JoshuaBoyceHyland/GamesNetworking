#define _WINSOCK_DEPRECATED_NO_WARNINGS // use as some functions in sampe code have deprecated
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

int main(void)
{
	struct sockaddr_in si_other;

	int s, slen = sizeof(si_other);// lengths
	char buf[BUFLEN];// buffer
	char message[BUFLEN]; // message buffer
	WSADATA wsa;// structure that stores info about the winsock implementation

	printf("\nInitialising Winsock...");


	// Initialize Winsock
	// must be called before the use of any winsock functions ( creating sockets or connecting to servers)
	// MAKEWORD: macro that creats a version number for winsock to use
	// MAKEWORD: the paramets 2, 2 means its requesting 2.2
	// &wsaData: points to the data thate will be filled in by the function
	// 0 will be returned if this fails
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	// and check it is valide
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	//fills memory of si_other
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;// wil use  IPv4 addresses
	si_other.sin_port = htons(PORT); // holds port number
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//start communication
	while (1)
	{
		printf("Enter message : ");

		fgets(message, sizeof(message), stdin);

		//send the message
		// send the data to the  the reciever and check if it is valid
		if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call and check if valid
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		puts(buf);
	}

	closesocket(s);
	WSACleanup();

	return 0;
}