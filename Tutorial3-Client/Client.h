#pragma once
using namespace std;

class Client
{
	public:
		Client(char* port);
		~Client();

		int create();
		int sendData(string buffer);
		string receiveData();
		int close();

	private:
		char* port;
		SOCKET theSocket;
};

