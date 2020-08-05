#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
// #pragma comment (lib, "Mswsock.lib")



int main(int argc, char *argv[])
{
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	//socket的建立
	int sockfd = 0;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) {
		printf("Fail to create a socket.");
	}

	//socket的連線

	struct sockaddr_in info;
	info.sin_family = PF_INET;

	//localhost test
	info.sin_addr.s_addr = inet_addr("192.168.50.46");
	info.sin_port = htons(27015);

	int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
	if (err == -1) {
		printf("Connection error");
	}


	//Send a message to server
	char message[] = { "Hi there" };
	char receiveMessage[100] = {};
	iResult = send(sockfd, message, sizeof(message), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(sockfd);
		WSACleanup();
		return 1;
	}

	closesocket(sockfd);
	return 0;
}