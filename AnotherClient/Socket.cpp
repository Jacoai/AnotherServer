#include "Socket.h"
#include <thread>

Socket::Socket()
{
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}

// Receive until the peer closes the connection
int Socket::Connect()
{
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        
                // Create a SOCKET for connecting to server
                ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
                if (ConnectSocket == INVALID_SOCKET) {                 
                    WSACleanup();
                    return -1;
                }
        
                // Connect to server.
                iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
                if (iResult == SOCKET_ERROR) {
                    closesocket(ConnectSocket);
                    ConnectSocket = INVALID_SOCKET;
                    continue;
                }
                
                return 0;
    }   
    return -1;
}

int Socket::Setaddrinfo()
{
    freeaddrinfo(result);
    iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);

    return iResult;
}

const char* Socket::GetIP()
{
    return DEFAULT_IP;
}


const char* Socket::GetPort()
{
    return DEFAULT_PORT;
}

void Socket::SetIP(const char* ip)
{
    DEFAULT_IP = ip;
}

void Socket::SetHPort(const char* port)
{
    DEFAULT_PORT = port;
}


//int __cdecl main(int argc, char** argv)
//{
//   

//
//    // Validate the parameters
//  
//
//    // Initialize Winsock
//    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//    if (iResult != 0) {
//        printf("WSAStartup failed with error: %d\n", iResult);
//        return 1;
//    }
//
//    ZeroMemory(&hints, sizeof(hints));
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_protocol = IPPROTO_TCP;
//
//    // Resolve the server address and port
//    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
//    if (iResult != 0) {
//        printf("getaddrinfo failed with error: %d\n", iResult);
//        WSACleanup();
//        return 1;
//    }
//
//    // Attempt to connect to an address until one succeeds
//    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
//
//        // Create a SOCKET for connecting to server
//        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//        if (ConnectSocket == INVALID_SOCKET) {
//            printf("socket failed with error: %ld\n", WSAGetLastError());
//            WSACleanup();
//            return 1;
//        }
//
//        // Connect to server.
//        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//        if (iResult == SOCKET_ERROR) {
//            closesocket(ConnectSocket);
//            ConnectSocket = INVALID_SOCKET;
//            continue;
//        }
//        break;
//    }
//
//    freeaddrinfo(result);
//
//    if (ConnectSocket == INVALID_SOCKET) {
//        printf("Unable to connect to server!\n");
//        WSACleanup();
//        return 1;
//    }
//
//    
//    do {
//
//        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RecvMessage, (LPVOID)(recvbuf), NULL, NULL);
//        // Send an initial buffer
//
//        std::cin.getline(sendbuf, DEFAULT_BUFLEN);
// 
//        iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
// 
//        if (iResult == SOCKET_ERROR) {
//            printf("send failed with error: %d\n", WSAGetLastError());
//            closesocket(ConnectSocket);
//            WSACleanup();
//            return 1;
//        }
//        printf("Bytes Sent: %ld\n", iResult);
//
//    } while (true);
//
//
//    // shutdown the connection since no more data will be sent
//    iResult = shutdown(ConnectSocket, SD_SEND);
//    if (iResult == SOCKET_ERROR) {
//        printf("shutdown failed with error: %d\n", WSAGetLastError());
//        closesocket(ConnectSocket);
//        WSACleanup();
//        return 1;
//    }
//
//    system("pause");
//    // cleanup
//    closesocket(ConnectSocket);
//    WSACleanup();
//
//    return 0;
//}