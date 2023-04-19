#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define port "1287"

class Socket
{
public:

    WSADATA wsaData;
    struct addrinfo* result = NULL,*ptr = NULL, hints;
    char sendbuf[DEFAULT_BUFLEN] = "";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    SOCKET ConnectSocket = INVALID_SOCKET;
    bool flagRecv = false;
    //const char* DEFAULT_PORT = "27015";
    int DEFAULT_PORT = 27015;
    

public:
    Socket();
    int Connect();

//private:
    


};