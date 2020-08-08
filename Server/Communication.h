/* This is Communication API header file for Server side.
* Editor : yichan 2020
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <cstdlib>
#include <iostream>
#include <string>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 300
#define DEFAULT_PORT "27015"

using namespace std;


class Communication
{
public:
	Communication();
	~Communication();

	char recvbuf[DEFAULT_BUFLEN];
	char message[DEFAULT_BUFLEN];

	void CreateSocket();
	void Bind();
	void Listen();
	void Accept();
	void CloseSocket();
	void ServerRecieve();
	void ServerSend();

private:
	WSADATA wsaData;

	SOCKET ServerSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	// ai_addr can be used in IPv4 and IPv6, better than sockaddr_in
	struct addrinfo *servinfo = NULL;
	struct addrinfo *clientinfo = NULL;
	struct addrinfo hints;
	int addr_len = sizeof(clientinfo);

	int iResult;
	int iSendResult;

};

#endif // !COMMUNICATION_H

