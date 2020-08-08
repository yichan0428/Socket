#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include "Communication.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
// #pragma comment (lib, "Mswsock.lib")

using namespace std;

Communication communication;
void sendMsg()
{
	string input;
	int n = 10000;
	int start = n + 1;
	while (n) {
		//cin >> input;
		input = "c" + to_string(start - n);
		strcpy_s(communication.message, input.c_str());
		communication.ClientSend();
		cout << "send!" << endl;
		n--;
	}
}
void recvMsg()
{
	while (1)
	{
		communication.ClientRecieve();
	}
}

int main(int argc, char *argv[])
{
	communication.CreateSocket();
	communication.Connect();

	//========== Add your code below ==========//
	thread sendthread(sendMsg);
	thread recvthread(recvMsg);
	sendthread.join();
	recvthread.join();


	//========== Add your code above ==========//

	communication.CloseSocket();
	return 0;
}