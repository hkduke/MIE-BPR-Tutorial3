#pragma once

#include "stdafx.h"
using namespace std;

#pragma comment(lib, "ws2_32.lib")

class Server{

	public:
		Server(int port);
		~Server();

		int create();
		int listenConnections();
		int sendData(string data);
		string receiveData();
		int close();

	private:
		int port;
		SOCKET theSocket;
		SOCKET clientSocket;
};

