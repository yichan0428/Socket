#include "Communication.h"



Communication::Communication()
{
}

Communication::~Communication()
{
}

void Communication::CreateSocket()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "[Socket] Cannot initialize winsock with error: " << iResult << endl;
		exit(1);
	}

	ZeroMemory(&hints, sizeof(hints));	//equals to memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		//AF_INET : IPv4, AF_INET6 : IPv4, AF_UNSPEC : any
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;		//use my IP address, it will automatically become  INADDR_ANY ¡]IPv4¡^or in6addr_any¡]IPv6¡^

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &servinfo);		//get serverinfo
	if (iResult != 0) {
		cout << "[Socket] getaddrinfo failed with error: " << gai_strerror(iResult) << endl;
		freeaddrinfo(servinfo);
		freeaddrinfo(clientinfo);
		WSACleanup();
		exit(1);
	}

	// Create a SOCKET
	ServerSocket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (ServerSocket == INVALID_SOCKET) {
		cout << "[Socket] Cannot create a socket with error: " << WSAGetLastError() << endl;
		freeaddrinfo(servinfo);
		freeaddrinfo(clientinfo);
		WSACleanup();
		exit(1);
	}
}
void Communication::BindAndListen()
{
	// Socket binding
	iResult = bind(ServerSocket, servinfo->ai_addr, (int)servinfo->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		cout << "[Socket] Bind failed with error: " << WSAGetLastError() << endl;
		CloseSocket();
		exit(1);
	}
	// Socket listening
	iResult = listen(ServerSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		cout << "[Socket] listen failed with error: " << WSAGetLastError() << endl;
		CloseSocket();
		exit(1);
	}
	cout << "[Socket] listening for incoming connections." << endl;
}

void Communication::Accept()
{
	// Accept a client socket
	ClientSocket = accept(ServerSocket, NULL, NULL);
	//ClientSocket = accept(ServerSocket, (sockaddr*)clientinfo, &addr_len);
	if (ClientSocket == INVALID_SOCKET) {
		cout << "[Socket] Accept failed with error: " << WSAGetLastError() << endl;
		CloseSocket();
		exit(1);
	}
	cout << "[Socket] Client connected!" << endl;
}

void Communication::Connect()
{
	ClientSocket = connect(ServerSocket, (sockaddr *)clientinfo, addr_len);
	if (ClientSocket == INVALID_SOCKET) {
		cout << "[Socket] Connection error" << endl;
		//«Ý­×¥¿
	}
}

void Communication::CloseSocket()
{
	cout << "[Socket] Close socket communication" << endl;
	freeaddrinfo(servinfo);		//avoid memory leak
	freeaddrinfo(clientinfo);

	closesocket(ServerSocket);
	WSACleanup();
}

void Communication::ServerRecieve()
{
	iResult = recv(ClientSocket, recvbuf, sizeof(recvbuf), 0);
	if (iSendResult == SOCKET_ERROR) {
		cout << "[Socket] Send failed with error: " << WSAGetLastError() << endl;
		CloseSocket();
		return;
	}
	if (iResult > 0) {
		cout << "Bytes received: " << iResult << "\nMessage: " << recvbuf << endl;
	}
	memset(recvbuf, 0, sizeof(recvbuf));
}

void Communication::ServerSend()
{
	iSendResult = send(ClientSocket, message, sizeof(message), 0);
	if (iSendResult == SOCKET_ERROR) {
		cout << "[Socket] Send failed with error: " << WSAGetLastError() << endl;
		CloseSocket();
		return;
	}
	cout << "Send! " << endl;
	memset(message, 0, sizeof(message));
}

void Communication::ClientRecieve() 
{}
void Communication::ClientSend() 
{}