#include <iostream>
#include <string>
#include "Communication.h"

using namespace std;

Communication communication;

int main(int argc, char *argv[])
{
	communication.CreateSocket();
	communication.BindAndListen();
	communication.Accept();

	//========== Add your code below ==========//
	string input;
	while (1) {
		cin >> input;
		strcpy_s(communication.message, input.c_str());
		communication.ServerSend();
	}
	//========== Add your code above ==========//

	communication.CloseSocket();
	return 0;
}