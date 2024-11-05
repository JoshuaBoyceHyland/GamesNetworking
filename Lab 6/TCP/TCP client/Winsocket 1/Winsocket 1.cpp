#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512 // buffer length
#define DEFAULT_PORT "27015"

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData; // structure that stores info about the winsock implementation
    SOCKET ConnectSocket = INVALID_SOCKET; // default to an invalid socket (-1)

    // holds information about the networking address
    /*points to start of linked list of address infor structures*/
    struct addrinfo* result = NULL, 

    /*used to itereate throught the linked list*/
    * ptr = NULL, 

    // not pointer, used to specify criteria for address lookup, 
    // you ppulate this with address family, the socket type and protocol
    // and then call getAddressInfo to get this information
    // so it controls the typoes of address that this function will return
    hints;  
               

    const char* sendbuf = "this is a test";// being sent to server
    char recvbuf[DEFAULT_BUFLEN]; // char buffer array
    int iResult; // stores possible resulting errors of winsock functions, 
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    // expects 1 command line arguement
    // server name or IP address
    if (argc != 2) {
        printf("usage: %s joshuas server\n", argv[0]);
        return 1;
    }

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

    ZeroMemory(&hints, sizeof(hints)); // initialises hints to 0, preparing it for use by the getAddressinfo function
    hints.ai_family = AF_INET; // specifying that program can work with  IPv4 and IPv6 address
    hints.ai_socktype = SOCK_STREAM; // menas that a reliable TCP connection is going to be made
    hints.ai_protocol = IPPROTO_TCP; // narrows down that the search will only return TCP comp addresses

    // Resolve the server address and port
    // used to resolve a hostname and port number to a linked list in data
    // which provides the info which is necassry to creat a socket connection 
    // argv[1]: ip address/ host name
    // DEFAULT_PORT: port number that the server is listening to 
    // DEFAULT_PORT: combination of ip address and this allowss the function to find the right address
    // hints: contains the required info for address lookup, like the family, socket type and protocol as mentioned before
    // result: what will actually be filled in by the function, contains inofo about potential address that could be connected to
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);

    // if not zero means prior line has failed, returns a number which correspons with an error code
    // WSACleanup: clean up before program closure
    // WSACleanup: releasing any resources allocated by winsock
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    // going through the linked list of addresss 
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        // check if invalid, if, then clean up and exit
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        
        // check if error occurred when connecting
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    // deallocated memory that was allocated for the linked list of address information
    // dont need it any more, as we have searched through out list 
    freeaddrinfo(result);

    // loop can end with a socket that has an error occur so must be checked again and cleaned up if so
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    // transmitting our message
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);

    // check for any for error and clean up
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {

        // recieving the info into the recieving buffer
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

        // still have more to be reciveded
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}