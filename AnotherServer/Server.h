#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

class Server
{
public:
	Server();
	SOCKET Socket;

private:
	std::vector<SOCKET> Sockets;
	WSADATA Data;
	void SendToClient();

};