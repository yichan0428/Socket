/* This is Communication API for Client side.
 * Editor : yichan 2020
 */

#include "Communication.h"



Communication::Communication()
{
}

Communication::~Communication()
{
}

void Communication::CreateSocket()
{
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "WSAStartup failed with error:" << iResult << endl;
		exit(1);
	}
	//socketªº«Ø¥ß
	ClientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSocket == -1) {
		cout << "Fail to create a socket." << endl;
		WSACleanup();
		exit(1);
	}
}

void Communication::Connect()
{
	
	clientinfo.sin_family = PF_INET;

	//localhost test
	inet_pton(clientinfo.sin_family, "192.168.50.46", &clientinfo.sin_addr.s_addr);
	clientinfo.sin_port = htons(27015);
	do {
		ServerSocket = connect(ClientSocket, (struct sockaddr *)&clientinfo, sizeof(clientinfo));
		if (ServerSocket == INVALID_SOCKET)
		{
			cout << "[Client] Server not found!" << endl;
			CreateSocket();
		}
			
	} while (ServerSocket == INVALID_SOCKET);
	cout << "[Client] Server connected!" << endl;
}

void Communication::CloseSocket()
{
	cout << "[Socket] Close socket communication" << endl;
	closesocket(ClientSocket);
	WSACleanup();
}

void Communication::ClientRecieve() 
{
	iResult = recv(ClientSocket, recvbuf, sizeof(recvbuf), 0);

	if (iResult > 0) {
		cout << "Server: " << recvbuf << endl;
	}
	else
	{
		//Connect();  //only sending fail should call it, or it will wrong when reconnect the server
	}
	memset(recvbuf, 0, sizeof(recvbuf));
}
void Communication::ClientSend() 
{
	iSendResult = send(ClientSocket, message, sizeof(message), 0);
	if (iSendResult == SOCKET_ERROR) {
		Connect();
	}
	memset(message, 0, sizeof(message));
}