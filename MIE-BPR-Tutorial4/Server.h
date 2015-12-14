#pragma once

#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")

class Server{

	public:
		Server(int port);
		~Server();

		int create();
		int listenConnections();
		int sendData(char* data, int size);
		int receiveData(char* buffer, int size);
		int close();

	private:
		int port;
		SOCKET theSocket;
		SOCKET clientSocket;
};

