#pragma once
using namespace std;

class Client
{
	public:
		Client(int port);
		~Client();
		int create();
		int sendData(string buffer);
		string receiveData();
		int close();

	private:
		int port;
		SOCKET theSocket;
};

