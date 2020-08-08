#include <iostream>
#include <string>
#include <thread>
#include "Communication.h"

using namespace std;

Communication communication;
void sendMsg()
{
	string input;
	int n = 10000;
	int start = n + 1;
	while (n) {
		cin >> input;
		//input = "s" + to_string(start- n);
		strcpy_s(communication.message, input.c_str());
		communication.ServerSend();
		cout << "send!" << endl;
		n--;
	}
	
}
void recvMsg()
{
	while (1)
	{
		communication.ServerRecieve();
	}
	
}
int main(int argc, char *argv[])
{
	communication.CreateSocket();
	communication.Bind();
	communication.Listen();
	communication.Accept();

	//========== Add your code below ==========//
	thread sendthread(sendMsg);
	thread recvthread(recvMsg);
	sendthread.join();
	recvthread.join();

	
	//========== Add your code above ==========//

	communication.CloseSocket();
	return 0;
}