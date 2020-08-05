#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <iostream>
#include <string>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
// #pragma comment (lib, "Mswsock.lib")

using namespace std;



int main(int argc, char *argv[])
{
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "WSAStartup failed with error:" << iResult << endl;
		return 1;
	}
	//socket的建立
	int sockfd = 0;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) {
		cout << "Fail to create a socket." << endl;
	}

	//socket的連線

	struct sockaddr_in info;
	info.sin_family = PF_INET;

	//localhost testR
	inet_pton(info.sin_family, "192.168.50.46", &info.sin_addr.s_addr);
	info.sin_port = htons(27015);

	int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
	if (err == -1) {
		cout << "Connection error" << endl;
	}

	int iSendResult;
	char message[300] = { "success" };
	char receiveMessage[300] = {};
	string input;

	//Send a message to server
	while (1) {
		iResult = send(sockfd, message, sizeof(message), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "send failed with error: " << WSAGetLastError() << endl;
			closesocket(sockfd);
			WSACleanup();
			return 1;
		}
		iSendResult = recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);
		cout << receiveMessage << endl;
	}
	cout << "Finished " << endl;
	closesocket(sockfd);
	return 0;
}