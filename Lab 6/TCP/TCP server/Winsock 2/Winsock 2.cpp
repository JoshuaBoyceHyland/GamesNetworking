#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512 // our buffer length
#define DEFAULT_PORT "27015"

int __cdecl main(void)
{
    WSADATA wsaData; // structure that stores info about the winsock implementation
    int iResult; // stores possible resulting errors of winsock functions, 

    // socket that will be used to listen for incoming requets
    SOCKET ListenSocket = INVALID_SOCKET;

    // our connection the client
    SOCKET ClientSocket = INVALID_SOCKET;

    // holds information about the networking address
   // points to start of linked list of address infor structures
    struct addrinfo* result = NULL;

    // you ppulate this with address family, the socket type and protocol
    // and then call getAddressInfo to get this information
    // so it controls the typoes of address that this function will return
    struct addrinfo hints;

    int iSendResult; // checking if send was successful
    char recvbuf[DEFAULT_BUFLEN]; // recieving buffer
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    // must be called before the use of any winsock functions ( creating sockets or connecting to servers)
    // MAKEWORD: macro that creats a version number for winsock to use
    // MAKEWORD: the paramets 2, 2 means its requesting 2.2
    // &wsaData: points to the data thate will be filled in by the function
    // 0 will be returned if this fails
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));// initialises hints to 0, preparing it for use by the getAddressinfo function
    hints.ai_family = AF_INET; // specifying that program can work with  IPv4  address
    hints.ai_socktype = SOCK_STREAM;// menas that a reliable TCP connection is going to be made
    hints.ai_protocol = IPPROTO_TCP; // narrows down that the search will only return TCP comp addresses
    hints.ai_flags = AI_PASSIVE;// indicates that the addresses returned will be used for the server socket that will then be accpeting incoming connections

    // Resolve the server address and port
    // used to resolve a hostname and port number to a linked list in data
    // which provides the info which is necassry to creat a socket connection 
    // NULL: because its null it treats the request  to get information for a socket that will accept connection
    // NULL: means that the function will return a list of addresses that can be used for binding.
    // DEFAULT_PORT: port number that the server is listening to 
    // DEFAULT_PORT: combination of ip address and this allowss the function to find the right address
    // hints: contains the required info for address lookup, like the family, socket type and protocol as mentioned before
    // result: what will actually be filled in by the function, contains inofo about potential address that could be connected to
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);


    // if not zero means prior line has failed, returns a number which correspons with an error code
    // WSACleanup: clean up before program closure
    // WSACleanup: releasing any resources allocated by winsock
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // check if out listening socket is valid
    // if not free up resources and clean up
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    // binds the socket with the specific address and port number
    // so it can listen to incoming connections
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    // check for error and clean up if so 
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // freeing up resources 
    freeaddrinfo(result);

    // marks as passive socket ( a socket that is being used to listen)
    // prepars socket to accept connects from clients
    // SOMAXCONN: the maximium lenght of the queue of pending connections
    iResult = listen(ListenSocket, SOMAXCONN);

    // check for error and clean up if so
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    // called on the listening socket to accept incoming connection requests from client
    // acceps create new socket specifically for  thjat client, which allows the servcer to communicate with it
    // NULL 1: would be used to recive the clients addres, so where it would go, but here we are saying we dont want it stored any where
    // NULL 2: size of clients address, once again null as we dont want 
    ClientSocket = accept(ListenSocket, NULL, NULL);

    // check if its valid an clean up if not
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {

        // recieving data from client 
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);

        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    // if error shit down and clean up
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}