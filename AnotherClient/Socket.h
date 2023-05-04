#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512

class Socket
{

private:
    const char* DEFAULT_PORT = "27016";
    const char* DEFAULT_IP = "127.0.0.1";    
    WSADATA wsaData;
    struct addrinfo* result = NULL, *ptr = NULL, hints;
public:

    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    SOCKET ConnectSocket = INVALID_SOCKET;
    int iResult = 0;
    bool changed = false;

    Socket();
    int Connect();  
    int Setaddrinfo();
    const char* GetIP();
    const char* GetPort();
    void SetIP(const char*);
    void SetHPort(const char*);
};