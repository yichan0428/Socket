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

int main(int argc, char *argv[])

{
	WSADATA wsaData;

	SOCKET ServerSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	// ai_addr can be used in IPv4 and IPv6, better than sockaddr_in
	struct addrinfo *servinfo = NULL;
	struct addrinfo *clientinfo = NULL;
	struct addrinfo hints;

	int iResult;
	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	char sendbuf[DEFAULT_BUFLEN];


	char inputBuffer[256] = {};
	char message[300] = { "Hi,this is server.\n" };

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "WSAStartup failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));	//equals to memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		//AF_INET : IPv4, AF_INET6 : IPv4, AF_UNSPEC : any
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;		//use my IP address, it will automatically become  INADDR_ANY ¡]IPv4¡^or in6addr_any¡]IPv6¡^

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &servinfo);		//get serverinfo
	if (iResult != 0) {
		cout << "getaddrinfo failed with error: " << gai_strerror(iResult) << endl;
		WSACleanup();
		return 1;
	}

	// Create a SOCKET
	ServerSocket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (ServerSocket == INVALID_SOCKET) {
		cout << "socket failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(servinfo);
		WSACleanup();
		return 1;
	}

	// Socket binding
	iResult = bind(ServerSocket, servinfo->ai_addr, (int)servinfo->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(servinfo);
		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}

	// Socket listening
	iResult = listen(ServerSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "listen failed with error: " << WSAGetLastError() << endl;
		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	int addr_len = sizeof(clientinfo);
	ClientSocket = accept(ServerSocket, NULL, NULL);//ClientSocket = accept(ServerSocket, (sockaddr*)clientinfo, &addr_len);
	if (ClientSocket == INVALID_SOCKET) {
		cout << "accept failed with error: " << WSAGetLastError() << endl;
		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(servinfo);		//avoid memory leak
	freeaddrinfo(clientinfo);
	//closesocket(ServerSocket);	//no longer need server socket

	string input;
	cout << "C" << endl;
	while (1) {
		cout << "3" << endl;
		cin >> input;
		strcpy_s(message, input.c_str());
		iResult = recv(ClientSocket, recvbuf, sizeof(recvbuf), 0);
		cout << "d" << endl;
		if (iResult > 0) {
			cout << "Bytes received: " << iResult << endl;

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, message, sizeof(message), 0);
			cout << "x" << endl;
			if (iSendResult == SOCKET_ERROR) {
				cout << "send failed with error: " << WSAGetLastError() << endl;
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			cout << "Bytes sent: " << iSendResult << endl;
			cout << recvbuf << endl;
		}
		else if (iResult == 0)
			cout << "Connection closing...\n" << endl;
		else {
			cout << "recv failed with error: " << WSAGetLastError() << endl;
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
		cout << recvbuf << endl;
		memset(recvbuf, 0, size(recvbuf));
		Sleep(1000);
	}
	cout << "Finished " << endl;
	return 0;
}
